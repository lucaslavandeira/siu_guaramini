#include <iostream>
#include <string>
#include <utility>
#include <set>

#include "server_Course.h"


Course::Course(int subject_id, int course_id, std::string name,
               std::string teacher, int quota) :
    subject_id(subject_id),
    course_id(course_id),
    name(name),
    teacher(teacher),
    quota(quota)
{
}

int Course::get_course() const {
    return course_id;
}

bool Course::subscribe(int student_id) {
    if (get_remaining_spots() == 0) {
        throw 0;
    }

    if (students.find(student_id) != students.end()) {
        return false;
    }

    students.insert(student_id);
    return true;
}

bool Course::desubscribe(int student_id) {
    if (get_remaining_spots() == 0) {
        throw 0;
    }

    unsigned long erased = students.erase(student_id);
    return erased != 0;
}

std::string Course::get_name() const {
    return name;
}

std::string Course::get_teacher() const {
    return teacher;
}

int Course::get_remaining_spots() const {
    return (int) (quota - students.size());
}

bool Course::is_subscribed(int student_id) const {
    return students.find(student_id) != students.end();
}

int Course::get_subject() const  {
    return subject_id;
}

