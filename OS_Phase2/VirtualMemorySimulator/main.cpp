#include <bitset>
#include <iostream>
#include "Driver.h"
#include "PageTable.h"
#include "PhysicalMemory.h"
#include "TLB.h"

// loads frame into main memory, updates page table, and updates TLB
void pageFaultHandler(unsigned char pageNumber, unsigned char &frameNumber, PhysicalMemory &mm, PageTable &pt, TLB &tlb) {
    frameNumber = mm.loadFrame(pageNumber);
    pt.updatePageTable(pageNumber, frameNumber);
}

// connects a frameNumber and offset to form a physical address
unsigned int createPhysicalAddress(unsigned char frameNumber, unsigned char offset) {
    bitset<8> frameNumberBits (frameNumber);
    bitset<8> offsetBits (offset);
    string frameNumberStr = frameNumberBits.to_string();
    string offsetStr = offsetBits.to_string();
    string physicalAddressStr = frameNumberStr + offsetStr;

    unsigned int physicalAddress = stoi(physicalAddressStr, nullptr, 2);

    return physicalAddress;
}

void writeToFile(string filename, vector<Driver::address_value_pair> address_value_list, float pageFaultRate, float tlbHitRate) {
    ofstream writeStream;

    writeStream.open(filename);

    if (writeStream.good()) {
        // do work
        for (int i = 0; i < address_value_list.size(); i++) {
            writeStream << "Virtual address: " << address_value_list[i].logicalAddress
                        << "; Physical address: " << address_value_list[i].physicalAddress
                        << "; Value: " << (int) address_value_list[i].value << "\n";
        }
        // write the page fault rate
        writeStream << "Page fault rate: " << pageFaultRate * 100 << "%\n";
        writeStream << "TLB hit rate: " << tlbHitRate * 100 << "%\n";

        // write the TLB hit rate
        writeStream.close();
    }
    else {
        cout << "**** Something is wrong with the wright stream ***" << endl;
    }
}

float calculatePageFaultRate(float numberOfAddresses, float pageFaultCount) {
    return pageFaultCount / numberOfAddresses;
}

float calculateTlbHitRate(float numberOfAddresses, float tlbHitCount) {
    return tlbHitCount / numberOfAddresses;
}


int main(int argc, const char * argv[]) {
    // User choice
    int choice;

    // Vars: page number, frame number and offset
    unsigned char pageNumber;
    unsigned char frameNumber;
    unsigned char offset;

    //Addresses
    unsigned int physicalAddress;
    unsigned int logicalAddress;

    // The TLB and page table
    TLB tlb;
    PageTable pt;

    // Simulated Main Memory
    Driver driver;
    PhysicalMemory mm;

    // value and address-value list
    int value;
    vector<Driver::address_value_pair> address_value_list;

    // number of page faults and tlb hits
    int pageFaultCount = 0;
    int pageTableHitCount = 0;
    int tlbHitCount = 0;
    int errors = 0;

    // Initialize the system
    tlb.initTLB();

    // Create a logical address list from the file
    // loads input addresses into vector
    vector<unsigned int> logicalAddresses = driver.loadAddresses("InputFile.txt");
    int numOfAddresses = logicalAddresses.size();

    cout << "Welcome to Tanner's VM Simulator Version 1.0" << endl << endl;
    cout << "Number of logical pages: 256" << endl;
    cout << "Page size: 256 bytes" << endl;
    cout << "Page table size: 256" << endl;
    cout << "TLB size: 16 entries" << endl;
    cout << "Number of physical frames: 256" << endl;
    cout << "Physical memory size: 65,536 bytes" << endl << endl;
    cout << "Choose TLB Replacement Strategy [1: FIFO, 2: LRU] ";

    while (!(cin >> choice) || choice <= 0 || choice >= 3) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Try again: ";
    }

    for (int i = 0; i < logicalAddresses.size(); i++) {
        // Get a logical address, its page number and offset
        pageNumber = driver.extractPageNumber(logicalAddresses[i]);
        offset = driver.extractOffset(logicalAddresses[i]);

        // Search the TLB
        // If a TLB hit occurs, return the frame number
        // else, go to the page table
        if (tlb.checkTLB(pageNumber) != -99) {

            // create physical address
            frameNumber = tlb.checkTLB(pageNumber);
            physicalAddress = createPhysicalAddress(frameNumber, offset);
            tlbHitCount++;
        }
            // go to page table
        else {
            // found in page table
            if (pt.returnFrameNumber(pageNumber) != -99) {
                pageTableHitCount++;
                frameNumber = (unsigned char)(pt.returnFrameNumber(pageNumber));
                physicalAddress = createPhysicalAddress(frameNumber, offset);
                if (choice == 1) {
                    tlb.replaceFIFO(pageNumber, frameNumber);
                }
                else {
                    tlb.replaceLRU(pageNumber, frameNumber);
                }
                // assert(pageNumber != frameNumber);
            }
            else {
                // handles a page fault,
                pageFaultCount++;
                pageFaultHandler(pageNumber, frameNumber, mm, pt, tlb);
                if (choice == 1) {
                    tlb.replaceFIFO(pageNumber, frameNumber);
                }
                else {
                    tlb.replaceLRU(pageNumber, frameNumber);
                }
                physicalAddress = createPhysicalAddress(frameNumber, offset);

            }
        }
        // read one byte value from main memory
        value = mm.lookUp(frameNumber, offset);

        if (pageNumber == frameNumber) {
            errors++;
        }
        // Update the addres-value list
        Driver::address_value_pair pair;
        pair.logicalAddress = logicalAddresses[i];
        pair.physicalAddress = physicalAddress;
        pair.value = mm.lookUp(frameNumber, offset);
        address_value_list.push_back(pair);
    }

    float pageFaultRate = calculatePageFaultRate(numOfAddresses, pageFaultCount);
    cout << "Number of page faults: " << to_string(pageFaultCount) << endl;
    cout << "Number of tlb hits: " << to_string(tlbHitCount) << endl;
    cout << "Number of page table hits: " << to_string(pageTableHitCount) << endl;
    cout << "Number of potential instances: " << to_string(errors) << endl << endl;
    cout << "*** Results printed to output.txt ***" << endl;

    float tlbHitRate = calculateTlbHitRate(numOfAddresses, tlbHitCount);
    // Output the address-value list into an output file
    writeToFile("output.txt", address_value_list, pageFaultRate, tlbHitRate);
    // end of main

    return 0;
}