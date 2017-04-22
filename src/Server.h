#ifndef TP3TALLER_SERVER_H
#define TP3TALLER_SERVER_H

#include <string>
#include "Socket.h"
#include "TSVParser.h"

class Server {
    Socket s;
public:
    explicit Server(int port);
    ~Server();

    std::string receive(const std::string &msg);
};


#endif //TP3TALLER_SERVER_H
