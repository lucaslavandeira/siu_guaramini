#ifndef TP3TALLER_SERVER_TEACHER_H
#define TP3TALLER_SERVER_TEACHER_H

#include <string>
#include <vector>
#include "server_User.h"

/* Teacher user type. Can subscribe / unsubscribe any student to the course they
 * are assigned to. */
class Teacher : public User {
    Course& course;

public:
    Teacher(Database& database, Course& course);
    std::string process_command(std::vector<std::string>& args);
    std::string get_identifier();
    ~Teacher();


    // Commands: see User class header for details on the return type

    /* Lists only the subscribed students to the course the teacher is assigned
     * to */
    std::string listSubs();

    /* (un)subscribes any student to the class they're in. subject_id and
     * course_id must match the ids assigned to 'course'. */
    std::string subscribe(int student_id, int subject_id, int course_id);
    std::string unsubscribe(int student_id, int subject_id, int course_id);
};


#endif //TP3TALLER_SERVER_TEACHER_H
