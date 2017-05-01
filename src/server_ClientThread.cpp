#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "server_ClientThread.h"
#include "common_protocol_socket.h"
#include "common_split.h"

#define COMANDO 0
const std::map<std::string, std::string> commands {
        {std::string("lm"), std::string("listarMaterias")},
        {std::string("li"), std::string("listarInscripciones")},
        {std::string("in"), std::string("inscribir")},
        {std::string("de"), std::string("desinscribir")}
};

ClientThread::ClientThread(Socket& s, User* user, PrintMonitor& printer) :
        s(std::move(s)),
        user(user),
        printer(printer)
{
    done = false;
}


void ClientThread::run() {
    std::string command = protocol_receive(s);
    while (command != "quit" && !done) {
        std::vector<std::string> cmds = split(command, '-');
        std::stringstream msg;
        msg << user->get_identifier() <<
                  " ejecuta " << commands.at(cmds[COMANDO]) << ".\n";

        printer.print(msg.str());

        // Generate a response
        std::string response = user->process_command(cmds);

        protocol_send(s, response.c_str(),
                      (unsigned int) response.length() + 1); // len + '\0' char
        command = protocol_receive(s);
    }
    std::cerr << user->get_identifier() << " desconectado." << std::endl;
    done = true;
}


ClientThread::~ClientThread() {
    delete user;
}

bool ClientThread::is_done() {
    return done;
}

void ClientThread::terminate() {
    s.shutdown();
    done = true;
}

