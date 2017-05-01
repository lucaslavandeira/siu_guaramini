#ifndef TP3TALLER_SERVER_PRINTMONITOR_H
#define TP3TALLER_SERVER_PRINTMONITOR_H

#include <string>
#include <mutex>


/* Monitor for the stderr stream. Protects the stderr output so only one thread
 * can write it at a time.
 */
class PrintMonitor {
    std::mutex m;

public:
    void print(std::string msg);
};


#endif //TP3TALLER_SERVER_PRINTMONITOR_H
