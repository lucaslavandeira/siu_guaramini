#ifndef TP3TALLER_CLIENTACCEPTER_H
#define TP3TALLER_CLIENTACCEPTER_H

#include <string>
#include "server_Thread.h"
#include "common_socket.h"

class ClientAccepter : public Thread {
    Socket& s;
    bool running = false;

    explicit ClientAccepter(Socket s);

    void run();
    void terminate();
    ~ClientAccepter();
};

#endif //TP3TALLER_CLIENTACCEPTER_H
