#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include "server_User.h"

User::User(Database &database) :
        database(database)
{
}

std::string User::listSubjects() {
    std::stringstream result;
    for (std::pair<const int, std::vector<Course>>& pair: database.subjects) {
        for (const Course& c: pair.second) {
            result << pair.first << " - " << c.get_name() <<
                   ", Curso " << c.get_course() <<
                   ", " << c.get_teacher() << ", "
                   << c.get_remaining_spots() << " vacantes." << std::endl;
        }
    }
    return result.str();
}


User::~User() {
}
