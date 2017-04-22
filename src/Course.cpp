#include <iostream>
#include <string>
#include <sstream>
#include "Course.h"

Course::Course(int subject_id, int course_id, std::string name, int teacher_id,
               int quota) :
    subject_id(subject_id),
    course_id(course_id),
    name(name),
    teacher_id(teacher_id),
    quota(quota)
{
}

std::string Course::print() {
    std::ostringstream a;
    a << subject_id << " - " << name << ", Curso " << course_id << ", " <<
         teacher_id << ", " << quota - subs << " vacantes." << std::endl;

    return a.str();
}


