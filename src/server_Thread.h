#ifndef IDS_THREAD_H
#define IDS_THREAD_H

#include <thread>

// Abstract thread class, implemented in this project by IDSThread
class Thread {
    std::thread thread;

public:
    void start();
    void join();
    virtual ~Thread();

protected:
    virtual void run() = 0;
};


#endif //IDS_THREAD_H
