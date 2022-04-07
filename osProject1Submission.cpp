#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>
#include <vector>
#include <list>
#include "System.h"

using namespace std;



int main() {
	 
	unsigned int RAM = 0;
	int numberHardDisks = 0;
	unsigned int pageSize = 0;
	
	cout << "How much RAM is there?" << endl;
    std::cin >> RAM;

    cout << "What is the size of a page/frame?" << endl;
    cin >> pageSize;

    cout << "How many hard disks does the simulated computer have?" << endl;
    cin >> numberHardDisks;
    
    System os(RAM, pageSize, numberHardDisks);
    
    string input;
    cin>>input;
    
    //while(1) {
    	//to display which process is using the CPU and which is waiting in the ready queue
    	if (input == "S r") {
    		os.showCurrentProcess();
		}
		
		//the process using the CPU forks a child. 
		//the child is places in the end of the ready queue
		else if (input == "fork") {
			//os.fork();
		}
		
		//to move the current process in CPU to the end of the ready queue
		//plus, places a new process into the CPU
		else if  (input == "toQueue"){
			os.fromCPUtoReadyQ();
		}
		
		//to create a process and places at the end of ready queue
		// if the ready queue is empty it places the process in the CPU
		else if (input == "A"){
			os.createProcess();
		}
	//}
	
}
