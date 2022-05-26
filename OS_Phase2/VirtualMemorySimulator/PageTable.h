
#ifndef DARINAKARIMOVA_WORKSTATION_PAGETABLE_H
#define DARINAKARIMOVA_WORKSTATION_PAGETABLE_H

#include <bitset>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class PageTable {
public:
    PageTable() : page_table_t(PAGE_TABLE_SIZE, -99), nextEmptyEntryIndex(0) {}
    bool isFull();
    int returnFrameNumber(unsigned char pageNumber);
    void updatePageTable(unsigned char pageNumber, unsigned char frameNumber);

private:
    const static int PAGE_TABLE_SIZE = 256;
    vector<int> page_table_t;
    unsigned int nextEmptyEntryIndex;
};

#endif //DARINAKARIMOVA_WORKSTATION_PAGETABLE_H
