#ifndef TP3TALLER_USER_H
#define TP3TALLER_USER_H

#include <string>
#include "server_Database.h"

class User {
protected:
    Database& database;

public:
    explicit User(Database& database);
    std::string listSubjects();
    virtual std::string listSubs() = 0;
    //virtual std::string subscribe() = 0;
    //virtual std::string desubscribe() = 0;
    virtual ~User();
};


#endif //TP3TALLER_USER_H
