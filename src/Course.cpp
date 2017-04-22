#include <iostream>
#include <string>
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

// Debug method
void Course::print() {
    std::cout << name << ": Subject " << subject_id << ", Course " <<
              course_id << ", Teacher " << teacher_id << std::endl;
}

