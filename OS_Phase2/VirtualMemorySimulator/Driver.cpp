
#include "Driver.h"

vector<unsigned int> Driver::loadAddresses(string filename) {
    ifstream readStream;
    string currentAddressStr;
    unsigned int currentAddressInt = 0;

    readStream.open(filename);
    if (readStream.good()) {
        // do WORK
        while (!readStream.eof()) {
            getline(readStream, currentAddressStr);
            string str(currentAddressStr);
            currentAddressInt = atoi(currentAddressStr.c_str());
            logicalAddresses.push_back(currentAddressInt);
        }
        readStream.close();
    }
    else {
        cout << endl << "*** INVALID FILE ***" << endl;
    }

    return logicalAddresses;
}

unsigned char Driver::extractPageNumber(unsigned int logicalAddress) {
    bitset<16> value(logicalAddress);
    unsigned int pageNumber;

    string pageNumberString = value.to_string();
    pageNumberString = pageNumberString.substr(0, 8);

    pageNumber = stoi(pageNumberString, nullptr, 2);

    return pageNumber;
}

unsigned char Driver::extractOffset(unsigned int logicalAddress) {
    bitset<16> value(logicalAddress);
    unsigned int offset;

    string offsetString = value.to_string();
    offsetString = offsetString.substr(8, 16);

    offset = stoi(offsetString, nullptr, 2);

    return offset;
}
