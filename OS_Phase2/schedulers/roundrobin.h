
#ifndef DARINAKARIMOVA_WORKSTATION_ROUNDROBIN_H
#define DARINAKARIMOVA_WORKSTATION_ROUNDROBIN_H


#pragma once

#include "task.hh"

namespace schedulers {
    namespace roundrobin {
        void setup(int milliseconds);
        void add_task(Task&& task);

        [[noreturn]] void start();
    }
}


#endif //DARINAKARIMOVA_WORKSTATION_ROUNDROBIN_H
