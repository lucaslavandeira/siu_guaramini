#include <iostream>
#include <string>
#include <sstream>
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

void Course::subscribe(int student_id) {
    students.push_back(student_id);
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
