#include <iostream>
#include "server_ClientAccepter.h"
#include "common_socket.h"

ClientAccepter::ClientAccepter(Socket s) :
    s(s)
{
}

ClientAccepter::~ClientAccepter() {
}

void ClientAccepter::run() {
    while (running) {
        Socket new_client = s.accept_client();
        break;
    }
}

void ClientAccepter::terminate() {
    running = false;
}

