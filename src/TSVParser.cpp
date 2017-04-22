#include <iostream>
#include "common_split.h"
#include "TSVParser.h"

TSVParser::TSVParser(const char *path) :
    f(std::ifstream(path))
{
    if (!f.good()) {
        std::cout << "Error opening file " << path << std::endl;
        throw 0;
    }
}

TSVParser::~TSVParser() {
    f.close();
}

std::vector<std::string> TSVParser::parse_row() {
    char line[256];
    f.getline(line, 256);
    std::string input(line);
    if(f.eof()) {
        throw 1;
    }

    std::vector<std::string> row = split(input, '\t');
    return row;
}

bool TSVParser::eof() {
    return f.peek() == EOF;
}

