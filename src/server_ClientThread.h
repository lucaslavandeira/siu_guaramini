#ifndef TP3TALLER_CLIENTTHREAD_H
#define TP3TALLER_CLIENTTHREAD_H


#include "server_Thread.h"
#include "common_socket.h"
#include "server_User.h"

class ClientThread : public Thread {
    Socket s;
    User* user;
public:
    ClientThread(Socket& s, User* user);
    ~ClientThread();

protected:
    void run();
};


#endif //TP3TALLER_CLIENTTHREAD_H
