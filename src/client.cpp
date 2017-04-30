#include <iostream>
#include <vector>
#include <string>
#include <map>
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
    /* Parses a command and its arguments into a single string of the format
     * [command_id]-[arg1]-...-[argN], that the server can understand.
     * If the passed command is not valid, returns "" (empty string). */
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
    /* Runs a client for the subscription system. Reads the following arguments
     * from the command line:
     * argv[1]: server address
     * argv[2]: server port
     * argv[3]: user mode, one of the following: 'alumno', 'docente', 'admin'
     * argv[4]: ID if the user mode is 'alumno' or 'docente', none for admin.
     *
     * The program always returns 0.
     */
    if (argc < 3) {
        return 1;
    }
    Socket s(argv[1], atoi(argv[2]));

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
