#ifndef TP3TALLER_ADMIN_H
#define TP3TALLER_ADMIN_H

#include <string>
#include <vector>
#include "server_User.h"

/* Admin user type: Able to (un)subscribe any student to any course. */
class Admin : public User {
public:
    explicit Admin(Database& database);
    ~Admin();

    std::string process_command(std::vector<std::string>& args);
    /* returns "admin", there's no uniqueness for this user type */
    std::string get_identifier();

    /* Lists every subscribed student to every course loaded in the server */
    std::string listSubs();

    /* (un)subscribes any student to the specified subject/course combination */
    std::string subscribe(int student_id, int subject_id, int course_id);
    std::string unsubscribe(int student_id, int subject_id, int course_id);
};


#endif //TP3TALLER_ADMIN_H
