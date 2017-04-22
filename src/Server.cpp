#include <iostream>
#include <vector>
#include <string>
#include "Server.h"
#include "common_split.h"

Server::~Server() {
}

Server::Server(int port) :
    s("localhost", port)
{
    TSVParser parser("materias.txt");

    while (!parser.eof()) {
        std::vector<std::string> row = parser.parse_row();
        for(std::string arg : row) {
            std::cout << "Server prints: " << arg << std::endl;
        }
    }

}

std::string Server::receive(const std::string &msg) {
    std::vector<std::string> args = split(msg, '-');
    return "quit";
}
