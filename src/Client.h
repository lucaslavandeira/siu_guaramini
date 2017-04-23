#ifndef TP3TALLER_CLIENT_H
#define TP3TALLER_CLIENT_H


#include "common_socket.h"
#include <string>

class Client {
    Socket s;
public:
    Client(const char* addr, int port, const char* mode);
    ~Client();

    std::string send(std::string msg);
};


#endif //TP3TALLER_CLIENT_H
