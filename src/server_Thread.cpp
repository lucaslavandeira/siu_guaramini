#include <iostream>
#include "server_Thread.h"

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {
}

bool Thread::joinable() {
    return thread.joinable();
}
