#ifndef TP3TALLER_STUDENT_H
#define TP3TALLER_STUDENT_H

#include <string>
#include <list>
#include <vector>
#include "server_Database.h"
#include "server_User.h"
#include "server_Teacher.h"

class Student : public User {
    int id;
    std::list<Course*> subbed_courses;

public:
    Student(Database& database, int id);

    std::string process_command(std::vector<std::string>& args);
    std::string get_identifier();
    std::string listSubs();
    std::string subscribe(int subject_id, int course_id);
    std::string unsubscribe(int subject_id, int course_id);
    ~Student();
};


#endif //TP3TALLER_STUDENT_H
