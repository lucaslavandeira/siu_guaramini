#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
#include <unordered_set>
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

    bool subscribe(int student_id);

    int get_course();
    std::string get_name();
    std::string get_teacher();
    int get_remaining_spots();
};


#endif //TP3TALLER_COURSE_H
