#ifndef TP3TALLER_USER_H
#define TP3TALLER_USER_H

#include <string>
#include <vector>
#include "server_Database.h"


/* Abstract user class, used to manage the incoming commands and the outgoing
 * responses. Works with IDs loaded into the passed Database struct only */
class User {
protected:
    Database& database;

public:
    explicit User(Database& database);

    /* Common function among any type: lists every loaded subject into the
     * database, with their courses and available slots left */
    std::string listSubjects();

    /* Command processor to be implemented in the inherited classes. Reads
     * the vector of args, then returns a response to send to the client.
     * the arguments have to be validated and every command must return
     * a valid message. */
    virtual std::string process_command(std::vector<std::string>& args) = 0;

    // Returns an identifier string for the object type, for instance "admin" or
    // "teacher 5".
    virtual std::string get_identifier() = 0;
    virtual ~User();
};


#endif //TP3TALLER_USER_H
