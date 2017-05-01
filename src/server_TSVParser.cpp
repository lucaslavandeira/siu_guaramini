#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "common_split.h"
#include "server_TSVParser.h"

TSVParser::TSVParser(const char *path) :
    f(std::ifstream(path))
{
    if (!f.good()) {
        throw IOError("hehe");
    }
}

TSVParser::~TSVParser() {
    f.close();
}

std::vector<std::string> TSVParser::parse_row() {
    char line[256];
    f.getline(line, 256);
    std::string input(line);
    if (f.eof()) {
        std::vector<std::string> a;
        return a;
    }

    std::vector<std::string> row = split(input, '\t');
    return row;
}

bool TSVParser::eof() {
    return f.peek() == EOF;
}

IOError::IOError(const char *msg, ...) noexcept {
    strncpy(buf, msg, strlen(msg));
}

const char *IOError::what() const noexcept {
    return buf;
}
