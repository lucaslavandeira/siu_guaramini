#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include "server_Student.h"

Student::Student(Database &database, int id) :
        User(database)
{
    this->id = id;
}


std::string Student::listSubs() {
    std::stringstream result;
    for (std::pair<const int, std::vector<Course>> pair: database.subjects) {
        for (Course c: pair.second) {
            if (c.is_subscribed(id)) {
                result << pair.first << " - " << c.get_name() << ", Curso " <<
                       c.get_course() << ", " << c.get_teacher() <<
                       "." << std::endl;
            }
        }
    }
    return result.str();
}
