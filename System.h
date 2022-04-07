#include <vector>
#include <list>
#include <string>
using namespace std;
#ifndef SYSTEM_H
#define SYSTEM_H


class System {
	private:
		int CPU;
		int numberOfProcesses;
		int numberHardDisks;
		unsigned int pageSize;
		unsigned int RAM;
		list<int> ready_queue;
		
	public:
		System(unsigned int & RAM_, unsigned int & pageSize_, int & numberHardDisks_):
			CPU(1),
			numberOfProcesses(1),
			numberHardDisks(numberHardDisks_),
			pageSize(pageSize_),
			RAM(RAM_),
			ready_queue(0)
			{
				//to create initial process
				//..
				
				//to initialize hard disks
			}
		
		
//		~System() {
//			//distructor to delete disks, and PCBs
//		};
		
		void createProcess(){
			//function body
			//..
		}
		
		void fork(){
			//fucntion body
			//..
			
			if (CPU == 1){
				cout<<"There is no process in the CPU to fork" << endl;
			}
			else {
				//creation of new process
			}
		}
		
		//to add the given process to the ready queue.
		// if the CPU is idle, the process goes there instead.
		void AddToReqdyQueue(const int pid) {
			//first process goes to CPU
			if (CPU == 1)
			{
				CPU = pid;
			}
			//otherwise, the process added to back of queue
			else {
				ready_queue.push_back(pid);
			}
		}
		//to show which process is using CPU
		void showCurrentProcess(){
			//function body
			//..
			cout<<"Process using CPU: "<< CPU << endl;
			cout << "Ready Queue: ";
//			for (auto i = ready_queue.begin(); i != ready_queue.end(); ++i){
//				//cout << " <- "<< *i;
//			}
			cout << endl;
		}
		
		//to move the current process in CPU to the end of the ready queue
		//plus, places a new process into the CPU
		void fromCPUtoReadyQ() {
			ready_queue.push_back(CPU);
			CPU = ready_queue.front();
			ready_queue.pop_front();
		}
		
		//void remove_from_ready_queue(){}
		
		void displayMemory(){
			//function body
			//..
		}
		
		void getNextFromReadyQueue() {
			if (ready_queue.empty()){
				CPU = 1;
			}
			else {
				CPU = ready_queue.front();
				ready_queue.pop_front();
			}
		}

	
};

#endif
