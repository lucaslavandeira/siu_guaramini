#ifndef TP3TALLER_LOCK_H
#define TP3TALLER_LOCK_H

#include <mutex>

// Generic Lock class for easier locking and unlocking of mutexes
class Lock {
    std::mutex& m;

public:
    explicit Lock(std::mutex &m);
    ~Lock();
};

#endif //TP3TALLER_LOCK_H
