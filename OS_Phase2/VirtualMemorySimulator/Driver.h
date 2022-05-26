
#ifndef DARINAKARIMOVA_WORKSTATION_DRIVER_H
#define DARINAKARIMOVA_WORKSTATION_DRIVER_H

#include <algorithm>
#include <bitset>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Driver {
public:
    vector<unsigned int> loadAddresses(string filename);
    unsigned char extractPageNumber(unsigned int logicalAddress);
    unsigned char extractOffset(unsigned int logicalAddress);

    typedef struct {
        unsigned int logicalAddress;
        unsigned int physicalAddress;
        unsigned char value;
    } address_value_pair;

private:
    vector<unsigned int> logicalAddresses;
    int tlbHitCount;
};

#endif //DARINAKARIMOVA_WORKSTATION_DRIVER_H
