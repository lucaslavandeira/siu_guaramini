#include <iostream>
#include <string>
#include <vector>
#include "server_ClientThread.h"
#include "common_protocol_socket.h"
#include "common_split.h"

#define COMANDO 0

ClientThread::ClientThread(Socket& s, User* user) :
        s(std::move(s)),
        user(user)
{
}

void ClientThread::run() {
    std::string command = protocol_receive(s);
    while (command != "quit") {
        std::vector<std::string> cmds = split(command, '-');
        std::cerr << user->get_identifier() <<
                  " ejecuta " << cmds[COMANDO] << std::endl;


        // Generate a response
        std::string response = user->process_command(cmds);

        protocol_send(s, response.c_str(),
                      (unsigned int) response.length() + 1); // len + '\0' char
        command = protocol_receive(s);
    }
    std::cerr << user->get_identifier() << " desconectado." << std::endl;
}


ClientThread::~ClientThread() {
    delete user;
}

