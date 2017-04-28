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

    Student student(d, std::stoi(args[1]));

    while (1) {
        std::string command = protocol_receive(client);
        if (command == "") {
            break;
        }
        std::vector<std::string> cmds = split(command, '-');
        std::cerr << args[0] << " " << args[1] <<
                  " ejecuta " << cmds[0] << std::endl;

        protocol_send(client, "Hola\n", 6);
        continue;
        if (command == "lm") {
            client.send(student.listSubjects().c_str(), 0);
        } else if (command == "li") {
            client.send(student.listSubs().c_str(), 0);
        } else if (command == "in") {
            client.send("", 0);
        }
    }
    return 0;
}
