#ifndef TP3TALLER_ADMIN_H
#define TP3TALLER_ADMIN_H

#include <string>
#include <vector>
#include "server_User.h"

class Admin : public User {
public:
    explicit Admin(Database& database);
    ~Admin();

    std::string process_command(std::vector<std::string>& args);
    std::string get_identifier();
    std::string listSubs();
    std::string subscribe(int student_id, int subject_id, int course_id);
    std::string unsubscribe(int student_id, int subject_id, int course_id);
};


#endif //TP3TALLER_ADMIN_H
