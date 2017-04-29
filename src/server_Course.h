#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
#include <set>

class Course {
    int subject_id;
    int course_id;
    std::string name;
    int teacher_id;
    int quota;

    std::set<int> students;
public:
    Course(int subject, int course_id, std::string name,
           int teacher_id, int quota);

    bool subscribe(int student_id);
    bool desubscribe(int student_id);
    bool is_subscribed(int student_id) const;
    int get_subject() const;
    int get_course() const;
    std::string get_name() const;
    int get_teacher() const;
    int get_remaining_spots() const;
    const std::set<int>& get_students() const;
};


#endif //TP3TALLER_COURSE_H
