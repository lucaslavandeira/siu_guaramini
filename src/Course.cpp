#include <iostream>
#include <string>
#include <utility>

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
    std::cout << students.size();
    if (!get_remaining_spots()) {
        throw 0;
    }

    for (int student : students) {
        if (student == student_id) {
            return false;
        }
    }
    students.push_back(student_id);
    std::cout << students.size();
    return true;
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
