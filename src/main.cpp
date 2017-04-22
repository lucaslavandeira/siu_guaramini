#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "common_split.h"
#include "Socket.h"
#include "Client.h"
#include "Server.h"

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
        std::cout << "Wrong command!" << std::endl;
        return "";
    }

    std::string result;
    result += cmd;

    for (auto it = params.begin()+1; it != params.end(); it ++) {
        result += "-" + *it;
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        return 0;
    }

    int port = atoi(argv[2]);
    std::string user_type = argv[3];
    char* user_id = argv[4];
    if (user_type != "admin") {
        user_type += "-";
        user_type += user_id;  // 4 = user id
    }

    std::string input;
    Client c(argv[1], port, argv[3]);
    Server s(port);
    while (1) {
        getline(std::cin, input);
        std::string result = parse_command(input);
        c.send(result);
        std::string response = s.receive(result);
        if (response == "quit") {
            break;
        }
        std::cout << response;
    }

    return 0;
}
