#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
#include <unordered_set>
#include <set>

class Course {
    int subject_id;
    int course_id;
    std::string name;
    std::string teacher;
    int quota;

    std::set<int> students;
public:
    Course(int subject, int course_id, std::string name,
           std::string teacher, int quota);

    bool subscribe(int student_id);
    bool desubscribe(int student_id);
    bool is_subscribed(int student_id) const;
    int get_subject() const;
    int get_course() const;
    std::string get_name() const;
    std::string get_teacher() const;
    int get_remaining_spots() const;
};


#endif //TP3TALLER_COURSE_H
