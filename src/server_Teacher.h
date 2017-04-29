#ifndef TP3TALLER_SERVER_TEACHER_H
#define TP3TALLER_SERVER_TEACHER_H

#include <string>
#include <vector>
#include "server_User.h"

class Teacher : public User {
    Course& course;

public:
    Teacher(Database& database, Course& course);
    std::string process_command(std::vector<std::string>& args);
    std::string get_identifier();
    ~Teacher();

    std::string listSubs();
    std::string subscribe(int student_id, int subject_id, int course_id);
    std::string unsubscribe(int student_id, int subject_id, int course_id);
};


#endif //TP3TALLER_SERVER_TEACHER_H