#include "roundrobin.hh"
#include "task.hh"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <csignal>
#include <sys/time.h>
#include <ucontext.h>
#include <unistd.h>

namespace schedulers
{
    namespace roundrobin
    {
        // list of tasks
        std::vector<Task> tasks;

        // Used to create a new task
        std::mutex mutex;

        // Current process index
        int current_process;

        // system-wide signal mask
        sigset_t set;

        // Interval
        struct itimerval interval;

        // "Kernel" stack, for interrupt management
        void *signal_stack;

        // The interrupt context. not kernel stack
        ucontext_t signal_context;

        // The "current" context
        ucontext_t* cur_context;


        static void timer_interrupt(int j, siginfo_t* si, void* oldcontext);
        static void setup_signals();

        void add_task(Task&& task)
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.push_back(std::move(task));
        }

        void setup(int milliseconds)
        {
            setup_signals();

            interval.it_interval.tv_sec = 0;
            interval.it_interval.tv_usec = milliseconds * 1000;
            interval.it_value = interval.it_interval;

            signal_stack = new char[Task::STACKSIZE];
        }

        void setup_signals()
        {
            struct sigaction act;

            act.sa_sigaction = timer_interrupt;
            sigemptyset(&act.sa_mask);
            act.sa_flags = SA_RESTART | SA_SIGINFO;

            sigemptyset(&set);
            sigaddset(&set, SIGALRM);

            if(sigaction(SIGALRM, &act, NULL) != 0)
            {
                perror("Signal handler");
            }
        }
        [[noreturn]] void start()
        {
            if (setitimer(ITIMER_REAL, &interval, NULL))
#ifdef VERBOSE
                perror("settimer")
#endif;
            // force a context switch to the first task
            current_process = 0;
            cur_context = &tasks[0].context;
            tasks[0].run();
        }
        //start next process that is in the queue
        [[noreturn]] static void next_process()
        {
#if VERBOSE
            printf("scheduling out process %d\n", tasks[current_process].pid);
#endif
            current_process = (current_process + 1) % tasks.size();
#if VERBOSE
            printf("scheduling in process %d\n", tasks[current_process].pid);
#endif
            cur_context = &tasks[current_process].context;
            tasks[current_process].run();
        }
        void timer_interrupt(int j, siginfo_t* si, void* oldcontext)
        {
            // when switching back to the kernel, make sure to create a new context just
            // for switching
            getcontext(&signal_context);
            signal_context.uc_stack.ss_sp = signal_stack;
            signal_context.uc_stack.ss_size = Task::STACKSIZE;
            signal_context.uc_stack.ss_flags = 0;
            sigemptyset(&signal_context.uc_sigmask);
            makecontext(&signal_context, next_process, 1);

            // Save running thread, jump to scheduler
            swapcontext(cur_context, &signal_context);
        }
    }
}