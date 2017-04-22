#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
class Course {
    int subject_id;
    int course_id;
    std::string name;
    int teacher_id;
    int quota;
    int subs = 0;
public:
    Course(int subject_id, int course_id, std::string name,
           int teacher_id, int quota);

    std::string print();
};


#endif //TP3TALLER_COURSE_H
