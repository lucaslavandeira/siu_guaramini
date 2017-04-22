#ifndef TP3TALLER_TSVPARSER_H
#define TP3TALLER_TSVPARSER_H

#include <string>
#include <vector>
#include <fstream>

class TSVParser {
    std::ifstream f;
    std::vector<std::string> rows;
public:
    explicit TSVParser(const char* path);
    ~TSVParser();
};


#endif //TP3TALLER_TSVPARSER_H
