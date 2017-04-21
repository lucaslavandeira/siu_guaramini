#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "common_split.h"

int main(int argc, char** argv) {
    std::fstream f;
    f.open("materias.txt");
    char line[256];
    f.getline(line, 256);
    std::string input(line);
    std::cout << input << std::endl;
    std::vector<std::string> a = split(input, '\t');

    for (std::string s : a) {
        std::cout << s << std::endl;
    }

    getline(std::cin, input);
    std::cout << "input was: " << input << std::endl;
    return 0;
}


