#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <netinet/in.h>
#include "common_socket.h"
#include "common_split.h"
#include "common_protocol_socket.h"
const std::map<std::string, std::string> commands {
        {std::string("listarMaterias"), std::string("lm")},
        {std::string("listarInscripciones"), std::string("li")},
        {std::string("inscribir"), std::string("in")},
        {std::string("desinscribir"), std::string("de")}
};

std::string parse_command(std::string& input) {
    std::vector<std::string> params = split(input, ' ');
    std::string cmd;
    try {
        cmd = commands.at(params.at(0));
    } catch (std::out_of_range) {
        return "";
    }

    std::string result;
    result += cmd;

    for (auto it = params.begin()+1; it != params.end(); it ++) {
        result += "-" + *it;
    }

    // Not enough arguments for the specified commands
    if ((cmd == "in" || cmd == "de") && params.size() < 3) {
        return "";
    }
    return result;
}

int main(int argc, char** argv) {
    Socket s("127.0.0.1", atoi(argv[2]));

    std::string first_msg;
    first_msg += argv[3];
    if (argv[4]) {
        first_msg += "-";
        first_msg += argv[4];
    }


    protocol_send(s, first_msg.c_str(), (unsigned int) first_msg.length() + 1);

    std::string input;
    while (getline(std::cin, input)) {
        std::string result = parse_command(input);
        if (result == "") {
            std::cout << "Comando inválido." << std::endl;
            continue;
        }
        protocol_send(s, result.c_str(), (unsigned int) result.length() + 1);
        std::string response = protocol_receive(s);
        std::cout << response;
    }

    protocol_send(s, "quit", 5);
    return 0;
}
