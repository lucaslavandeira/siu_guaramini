#include <vector>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include "common_socket.h"
#include "common_split.h"
#include "common_protocol_socket.h"
#include "server_Database.h"
#include "server_Student.h"

int main(int argc, char** argv) {
    Socket s(std::stoi(argv[1]));
    Database d(argv[2], argv[3]);

    Socket client = s.accept_client();

    std::string first_msg = protocol_receive(client);


    std::vector<std::string> args = split(first_msg, '-');
    std::cerr << args[0] << " " << args[1] << " conectado." << std::endl;

    Student user(d, std::stoi(args[1]));

    while (1) {
        std::string command = protocol_receive(client);
        if (command == "quit") {
            break;
        }
        std::vector<std::string> cmds = split(command, '-');
        std::cerr << args[0] << " " << args[1] <<
                  " ejecuta " << cmds[0] << std::endl;

        std::string response;
        if (command == "lm") {
            response = user.listSubjects();
        } else if (command == "li") {
            response = user.listSubs();
        } else if (command == "in") {
            response = "Not implemented yet!\n";
        } else if (command == "de") {
            response = "Not implemented yet!\n";
        } else {
            response = "Should never happen";
        }

        protocol_send(client, response.c_str(),
                      (unsigned int) response.length() + 1); // len + '\0' char
    }
    return 0;
}
