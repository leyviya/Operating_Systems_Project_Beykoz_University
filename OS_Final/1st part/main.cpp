#include <string>
#include <sstream>
#include <iostream>

#include "PCB.h"
#include "disk.h"
#include "OS.h"

using namespace std;

int main() {

    unsigned int RAM = 0;
    unsigned int page_size = 0;
    int number_of_hard_disks = 0;

    std::cout << "How much RAM is there?" << std::endl;
    std::cin >> RAM;

    std::cout << "What is the size of a page/frame?" << std::endl;
    std::cin >> page_size;

    std::cout << "How many hard disks does the simulated computer have?" << std::endl;
    std::cin >> number_of_hard_disks;


    OperatingSystem OS(number_of_hard_disks, RAM, page_size);

    std::string input;
    std::getline(std::cin, input);

    while (1) {
    
        if (input == "S r") {
            OS.Snapshot();
        }
        
        else if (input == "S i") {
            OS.IOSnapshot();
        }
        
        else if (input == "S m") {
            OS.MemorySnapshot();
        }
        
        else if (input == "A") {
            OS.CreateProcess();
        }
        
        else if (input == "Q") {
            OS.CPUToReadyQueue();
        }
        
        else if (input == "fork") {
            OS.Fork();
        }
        
        else if (input == "exit") {
            OS.Exit();
        }
        
        else if (input == "wait") {
            OS.Wait();
        }
        
       
        std::stringstream in_stream(input);
        string first_word;
        in_stream >> first_word;

        if (first_word == "d" || first_word == "D" || first_word == "m") {
            int second_word;
            in_stream >> second_word;
            
            if (first_word == "d") {
                string third_word;
                in_stream >> third_word;
                OS.RequestDisk(second_word, third_word);
            }
            else if (first_word == "D") { // "D number") {
                
                OS.RemoveProcessFromDisk(second_word);
            }
            
            else if (first_word == "m") { // == "m address") {
                OS.RequestMemoryOperation(second_word);
            }
        }       

        std::cout << endl;
        std::getline(std::cin, input);
    }
}