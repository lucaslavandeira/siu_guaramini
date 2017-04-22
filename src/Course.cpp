#include <iostream>
#include <string>
#include <utility>
#include <set>

#include "Course.h"

Course::Course(int course_id, std::string name,
               std::string teacher, int quota) :
    course_id(course_id),
    name(name),
    teacher(teacher),
    quota(quota)
{
}

int Course::get_course() {
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

std::string Course::get_name() {
    return name;
}

std::string Course::get_teacher() {
    return teacher;
}

int Course::get_remaining_spots() {
    return (int) (quota - students.size());
}

bool Course::is_subscribed(int student_id) {
    return students.find(student_id) != students.end();
}

