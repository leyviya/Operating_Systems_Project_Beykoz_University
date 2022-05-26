

#ifndef DARINAKARIMOVA_WORKSTATION_PHYSICALMEMORY_H
#define DARINAKARIMOVA_WORKSTATION_PHYSICALMEMORY_H

#include <bitset>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class PhysicalMemory {
public:
    PhysicalMemory() : nextEmptyEntryIndex(0) {}

    char lookUp(unsigned char frameNumber,unsigned char offset);
    unsigned char loadFrame(unsigned char pageNumber);

private:
    const static int PHYS_MEM_SIZE = 256;
    const static long FRAME_SIZE = 256;
    char physical_memory_t[256][256];
    long nextEmptyEntryIndex;
};

#endif //DARINAKARIMOVA_WORKSTATION_PHYSICALMEMORY_H
