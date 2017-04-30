#ifndef TP3TALLER_STUDENT_H
#define TP3TALLER_STUDENT_H

#include <string>
#include <list>
#include <vector>
#include "server_Database.h"
#include "server_User.h"
#include "server_Teacher.h"

/* User type that can only sub itself into any course. */
class Student : public User {
    int id;
public:
    Student(Database& database, int id);

    std::string process_command(std::vector<std::string>& args);

    // Returns "alumno [id]"
    std::string get_identifier();

    // Commands: Read the User class header for details on the return type

    // Lists only the courses this student is subscribed to.
    std::string listSubs();

    // (un)subscribes to the specified course.
    std::string subscribe(int subject_id, int course_id);
    std::string unsubscribe(int subject_id, int course_id);

    ~Student();
};


#endif //TP3TALLER_STUDENT_H
