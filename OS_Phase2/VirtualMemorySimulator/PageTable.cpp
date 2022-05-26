
#include "PageTable.h"

bool PageTable::isFull() {
    if (nextEmptyEntryIndex >= 256) {
        return true;
    }
    else {
        return false;
    }
}

void PageTable::updatePageTable(unsigned char pageNumber, unsigned char frameNumber) {
    page_table_t[pageNumber] = frameNumber;
}

int PageTable::returnFrameNumber(unsigned char pageNumber) {
    int frameNumber = page_table_t[pageNumber];

    return frameNumber;
}
