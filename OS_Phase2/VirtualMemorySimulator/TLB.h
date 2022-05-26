
#ifndef DARINAKARIMOVA_WORKSTATION_TLB_H
#define DARINAKARIMOVA_WORKSTATION_TLB_H

#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class TLB {
public:
    TLB() : nextEntryIndex(0), indexOfOldest(-1), oldestAge(0){}

    typedef struct {
        unsigned char pageNumber;
        unsigned char frameNumber;
        unsigned long age;
        bool isValid;
    } tlb_entry;

    int checkTLB(unsigned char pageNumber);
    void initTLB();
    bool isFull();
    void replaceLRU(unsigned char pageNumber, unsigned char frameNumber);
    void replaceFIFO(unsigned char pageNumber, unsigned char frameNumber);

private:
    const static char TLB_SIZE = 16;
    tlb_entry tlb_t[TLB_SIZE];
    unsigned char nextEntryIndex;
    char indexOfOldest;
    unsigned long oldestAge;
};
#endif //DARINAKARIMOVA_WORKSTATION_TLB_H
