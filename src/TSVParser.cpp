#include <iostream>
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

