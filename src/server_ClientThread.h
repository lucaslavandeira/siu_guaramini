#ifndef TP3TALLER_CLIENTTHREAD_H
#define TP3TALLER_CLIENTTHREAD_H


#include "server_Thread.h"
#include "common_socket.h"
#include "server_User.h"
#include "server_PrintMonitor.h"

/* Thread that receives messages from the socket in a while loop and
 * processes them until the client disconnects or the terminate order is
 * issued. */
class ClientThread : public Thread {
    Socket s;
    User* user;
    PrintMonitor& printer;
    bool done;
public:
    ClientThread(Socket& s, User* user, PrintMonitor& printer);
    ~ClientThread();

    // True if the client has disconnected, false otherwise.
    bool is_done();

    // Shuts the socket down, used when the server shuts down
    void terminate();
protected:
    void run();
};


#endif //TP3TALLER_CLIENTTHREAD_H
