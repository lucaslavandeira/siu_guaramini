#ifndef TP3TALLER_TSVPARSER_H
#define TP3TALLER_TSVPARSER_H

#include <string>
#include <vector>
#include <fstream>


/* Parses the .txt TSV (tab separated values) files into C++ STL structures. */
class TSVParser {
    std::ifstream f;
    std::vector<std::string> rows;

public:
    explicit TSVParser(const char* path);
    ~TSVParser();

    // Returns an STL vector of strings made up from a row of TSV.
    std::vector<std::string> parse_row();
    bool eof();
};


#endif //TP3TALLER_TSVPARSER_H
