#ifndef TP3TALLER_CLIENTACCEPTER_H
#define TP3TALLER_CLIENTACCEPTER_H

#include <string>
#include <list>
#include "server_Thread.h"
#include "common_socket.h"
#include "server_Database.h"
#include "server_User.h"
#include "server_ClientThread.h"
#include "server_PrintMonitor.h"

/* Thread that accepts incoming client connections, and creates new threads for
 * their command processing. Once running, it'll continuously wait to accept
 * clients from the server socket. */
class ClientAccepter : public Thread {
    Socket s;
    Database& d;
    PrintMonitor printer;

    int port;
    std::list<ClientThread> clients;
    bool running;

public:
    explicit ClientAccepter(Socket& server, Database& d, int port);


    // Stops the server socket, to be used when the server is shutting down
    void kill();
    ~ClientAccepter();

private:
    // Starts the thread, runs a while loop until the socket shuts down
    void run();
    User* validate_client(std::string first_msg);
};

#endif //TP3TALLER_CLIENTACCEPTER_H
