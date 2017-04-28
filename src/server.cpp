#include <vector>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include "common_socket.h"
#include "common_split.h"
#include "common_protocol_socket.h"
#include "server_Database.h"
#include "server_Student.h"

#define COMANDO 0
#define MATERIA 1
#define CURSO 2

#define TIPO 0
#define ID 1

int main(int argc, char** argv) {
    Socket s(std::stoi(argv[1]));
    Database d(argv[2], argv[3]);

    Socket client = s.accept_client();

    std::string first_msg = protocol_receive(client);


    std::vector<std::string> args = split(first_msg, '-');
    std::cerr << args[TIPO] << " " << args[ID] << " conectado." << std::endl;

    User* user = new Student(d, std::stoi(args[ID]));

    std::string command = protocol_receive(client);
    while (command != "quit") {
        std::vector<std::string> cmds = split(command, '-');
        std::cerr << args[TIPO] << " " << args[ID] <<
                  " ejecuta " << cmds[COMANDO] << std::endl;


        // Generate a response
        std::string response;
        if (cmds[COMANDO] == "lm") {
            response = user->listSubjects();
        } else if (cmds[COMANDO] == "li") {
            response = user->listSubs();
        } else if (cmds[COMANDO] == "in") {
            response = user->subscribe(std::stoi(cmds[MATERIA]),
                                       std::stoi(cmds[CURSO]));
        } else if (cmds[COMANDO] == "de") {
            response = user->unsubscribe(std::stoi(cmds[MATERIA]),
                                         std::stoi(cmds[CURSO]));
        } else {
            response = "Should never happen\n";
        }

        protocol_send(client, response.c_str(),
                      (unsigned int) response.length() + 1); // len + '\0' char
        command = protocol_receive(client);
    }

    std::cerr << args[TIPO] << " " << args[ID] << " desconectado." << std::endl;
    return 0;
}
