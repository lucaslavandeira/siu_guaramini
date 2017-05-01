#include <iostream>
#include <string>
#include "server_PrintMonitor.h"
#include "server_Lock.h"

void PrintMonitor::print(std::string msg) {
    Lock(this->m);
    std::cerr << msg;
}
