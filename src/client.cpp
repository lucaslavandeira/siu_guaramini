#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "common_socket.h"
#include "common_split.h"

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
    Socket s("127.0.0.1", 8000);

    std::string first_msg;
    first_msg += argv[2];
    first_msg += "-";
    first_msg += argv[3];
    s.send(first_msg);

    std::string input;
    while (1) {
        getline(std::cin, input);
        std::string result = parse_command(input);
        s.send(result);
        std::string response = s.receive();
        std::cout << response;
        if (!response.size()) {
            break;
        }
    }
    return 1;
}
