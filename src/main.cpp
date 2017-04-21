#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "common_split.h"

const std::map<std::string, std::string> commands {
    {std::string("listarMaterias"), std::string("lm")},
    {std::string("listarInscripciones"), std::string("li")},
    {std::string("inscribir"), std::string("in")},
    {std::string("desinscribir"), std::string("de")}
};


void parse_command(std::string& input) {
    std::vector<std::string> params = split(input, ' ');
    std::string cmd;
    try {
        cmd = commands.at(params.at(0));
    } catch (std::out_of_range) {
        std::cout << "Wrong command!" << std::endl;
        return;
    }

    std::string result;
    result += cmd;

    for (auto it = params.begin()+1; it != params.end(); it ++) {
        result += "-" + *it;
    }
    std::cout << result;
}

int main(int argc, char** argv) {
   /*std::fstream f;
    f.open("materias.txt");
    char line[256];
    f.getline(line, 256);
    std::string input(line);*/
    std::string input;
    getline(std::cin, input);

    parse_command(input);
    return 0;
}
