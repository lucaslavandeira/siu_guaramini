#ifndef TP3TALLER_COURSE_H
#define TP3TALLER_COURSE_H

#include <string>
#include <set>
#include <mutex>

/* Represents a course where students can subscribe to. Courses have a limited
 * quota, once filled the course is full and students can't be subcribed
 * anymore. */
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

    /* Subs a new student. Returns true on success, false if it fails. */
    bool subscribe(int student_id);

    /* Unsubs a student. Returns true on sucesss, false if the student was not
     * subscribed. */
    bool unsubscribe(int student_id);

    bool is_subscribed(int student_id) const;
    int get_subject() const;
    int get_course() const;
    std::string get_name() const;
    int get_teacher() const;

    // Returns the quota - the amount of currently subbed students
    int get_remaining_spots() const;
    const std::set<int>& get_students() const;
};


#endif //TP3TALLER_COURSE_H
