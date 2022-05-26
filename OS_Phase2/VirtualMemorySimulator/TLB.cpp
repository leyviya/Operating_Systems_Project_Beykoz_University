#include "TLB.h"
//TRANSLATION LOOKASIDE BUFFER
//STORES TRAMSLATIONS OF VIRTUAL MEMORY TO PHYSICAL ADDRESSES FOR FASTER RETRIEVAL
// initializes the tlb with appropriate entries 0
void TLB::initTLB() {

    tlb_entry entry;
    entry.pageNumber = 0;
    entry.frameNumber = 0;
    entry.isValid = false;

    for (int i = 0; i < TLB_SIZE; i++) {
        tlb_t[i] = entry;
    }
}

// checks the TLB for a hit
int TLB::checkTLB(unsigned char pageNumber) {

    for (int i = 0; i < TLB_SIZE; i++) {
        if (pageNumber == tlb_t[i].pageNumber && tlb_t[i].isValid) {
            return tlb_t[i].frameNumber;
        }
    }
    return -99;
}

// checks for empty entries
bool TLB::isFull() {
    if (nextEntryIndex >= 16) {
        return true;
    }
    else {
        return false;
    }
}

// uses a FIFO implementation to update the TLB
void TLB::replaceFIFO(unsigned char pageNumber, unsigned char frameNumber) {
    tlb_entry entry;
    entry.pageNumber = pageNumber;
    entry.frameNumber = frameNumber;
    entry.isValid = true;

    if (isFull()) {
        nextEntryIndex = 0;
    }
    tlb_t[nextEntryIndex] = entry;
    nextEntryIndex++;
}

// uses an LRU implementation to update the TLB
void TLB::replaceLRU(unsigned char pageNumber, unsigned char frameNumber) {
    bool found = false;
    tlb_entry entry;


    // find oldest entry
    for (int i = 0; i < nextEntryIndex; i++) {
        assert(tlb_t[i].isValid);
        if (tlb_t[i].pageNumber == pageNumber) {
            assert(tlb_t[i].frameNumber == frameNumber);
            found = true;
            tlb_t[i].age = 0;
        }
        else {
            tlb_t[i].age++;
            if (tlb_t[i].age > oldestAge) {
                oldestAge = tlb_t[i].age;
                indexOfOldest = i;
            }
        }
    }

    // if oldest entry not found, either replace the oldest entry or insert a new one
    if (!found) {
        if (!isFull()) {
            assert(nextEntryIndex >= 0 && nextEntryIndex < TLB_SIZE);
            entry.pageNumber = pageNumber;
            entry.frameNumber = frameNumber;
            entry.age = 0;
            entry.isValid = true;
            tlb_t[nextEntryIndex] = entry;
            nextEntryIndex++;
        }
        else {
            entry.pageNumber = pageNumber;
            entry.frameNumber = frameNumber;
            entry.age = 0;
            entry.isValid = true;
            tlb_t[indexOfOldest] = entry;
        }
    }
}