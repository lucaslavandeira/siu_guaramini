#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
#include <vector>

class Course {
    int course_id;
    std::string name;
    std::string teacher;
    int quota;

    std::vector<int> students;
public:
    Course(int course_id, std::string name,
           std::string teacher, int quota);

    void subscribe(int student_id);

    int get_course();
    std::string get_name();
    std::string get_teacher();
    int get_remaining_spots();
};


#endif //TP3TALLER_COURSE_H
