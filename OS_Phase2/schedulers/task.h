
#ifndef DARINAKARIMOVA_WORKSTATION_TASK_H
#define DARINAKARIMOVA_WORKSTATION_TASK_H

#pragma once

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ucontext.h>
#include <utility>

namespace schedulers {
    struct Task {
        // process pid
        int pid;
        static int max_pid;

        // priority used internally by the scheduler
        int priority;

        // The entry point of the task.
        void (*entry_point)(void);

        // The context of the process.
        ucontext_t context;

        enum class State
        {
            READY,          // ready to run
            RUNNING,        // currently being run by the CPU
            WAITING,        // waiting for IO to conclude
            DONE            // This thread is done
        } state;

        int io_wait {0};    // how many milliseconds to wait


        constexpr static size_t STACKSIZE = 4096;

        Task(void (*entry_point)(void))
                : entry_point { entry_point }
        {
            this->pid = max_pid++;
            printf("Created task %d\n", pid);
            void* stack = new char[STACKSIZE];
            getcontext(&context);

            context.uc_stack.ss_sp = stack;
            context.uc_stack.ss_size = STACKSIZE;
            context.uc_stack.ss_flags = 0;
            if (sigemptyset(&context.uc_sigmask) < 0) {
                perror("sigemptyset");
                exit(EXIT_FAILURE);
            }

            state = State::READY;

            makecontext(&context, entry_point, 1);
        }

        Task(Task&& o) = default;

        //start or resume the task
        [[noreturn]] void run()
        {
            while (state != State::DONE) {
                state = State::RUNNING;
                setcontext(&context);
            }
        }
        //to avoid context sharing
        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;
    };
}


#endif //DARINAKARIMOVA_WORKSTATION_TASK_H
