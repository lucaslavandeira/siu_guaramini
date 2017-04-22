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
}

std::string Server::receive(const std::string &msg) {
    std::vector<std::string> args = split(msg, '-');
    return "quit";
}
