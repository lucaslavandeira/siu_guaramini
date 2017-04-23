#ifndef TP3TALLER_DATABASE_H
#define TP3TALLER_DATABASE_H

#include <vector>
#include <map>
#include <string>
#include "server_Course.h"

struct Database {
    std::map<int, std::vector<Course>> subjects;
    std::map<int, std::string> students;
    std::map<int, std::string> teachers;


    Database(char* users, char* subjects);
};

#endif //TP3TALLER_DATABASE_H
