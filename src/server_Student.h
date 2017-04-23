#ifndef TP3TALLER_STUDENT_H
#define TP3TALLER_STUDENT_H

#include <string>
#include "server_Database.h"
#include "server_User.h"

class Student : public User {
    int id;
public:
    Student(Database& database, int id);
    std::string listSubs();
    //std::string subscribe(int subject_id, int course_id);
    //std::string desubscribe(int subject_id, int course_id);
};


#endif //TP3TALLER_STUDENT_H
