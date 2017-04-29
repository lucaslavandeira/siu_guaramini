#ifndef TP3TALLER_USER_H
#define TP3TALLER_USER_H

#include <string>
#include <vector>
#include "server_Database.h"

class User {
protected:
    Database& database;

public:
    explicit User(Database& database);
    std::string listSubjects();
    virtual std::string process_command(std::vector<std::string>& args) = 0;
    virtual std::string get_identifier() = 0;
    virtual ~User();
};


#endif //TP3TALLER_USER_H
