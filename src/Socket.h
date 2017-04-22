#ifndef TP3TALLER_SOCKET_H
#define TP3TALLER_SOCKET_H

#include <string>


// FAKE SOCKET CLASS
class Socket {
public:
    Socket(const char* addr, int port);
    ~Socket();
    void send(const std::string& msg);
    void recv(std::string& msg);
};


#endif //TP3TALLER_SOCKET_H
