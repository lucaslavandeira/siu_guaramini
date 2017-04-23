#include <vector>
#include <string>
#include <iostream>
#include "common_socket.h"
#include "common_split.h"
#include "server_Database.h"
#include "server_Student.h"

int main(int argc, char** argv) {
    Socket s(std::stoi(argv[1]));
    Database d(argv[2], argv[3]);

    Socket client = s.accept_client();

    std::string first_msg = client.receive();
    std::vector<std::string> args = split(first_msg, '-');

    for (std::string arg : args) {
        std::cout << arg << std::endl;
    }


    Student student(d, std::stoi(args[1]));

    while (1) {
        std::string command = client.receive();
        if (!command.size()) {
            break;
        }
        std::cout << "Message receieved " << command << std::endl;
        if (command == "lm") {
            client.send(student.listSubjects());
        } else if (command == "li") {
            client.send(student.listSubs());
        } else if (command == "in") {
            client.send("");
        }
    }
    return 0;
}
