#include <vector>
#include <map>
#include <string>
#include <cstring>
#include "server_Course.h"
#include "server_Database.h"
#include "server_TSVParser.h"


class DatabaseError : std::exception {
    char buf[256];
public:
    explicit DatabaseError(const char* msg, ...) noexcept {
        strncpy(buf, msg, strlen(msg));
    }

    virtual const char* what() const noexcept {
        return buf;
    }
};

Database::Database(char *users, char *subjects)
{
    TSVParser user_parser(users);
    while (!user_parser.eof()) {
        std::vector<std::string> row = user_parser.parse_row();
        int id = atoi(row.at(1).c_str());

        if (row.at(0) == "docente") {
            teachers[id] = row.at(2);
        } else if (row.at(0) == "alumno") {
            students[id] = row.at(2);
        } else {
            throw DatabaseError("Incorrect students file format");
        }
    }

    TSVParser subject_parser(subjects);
    while (!subject_parser.eof()) {
        std::vector<std::string> row = subject_parser.parse_row();

        int subject_id = std::stoi(row.at(0));
        int course_id = std::stoi(row.at(1));
        std::string name = std::move(row.at(2));
        int teacher_id = std::stoi(row.at(3));
        std::string teacher = teachers.at(teacher_id).c_str();
        int quota = std::stoi(row.at(4));

        Course course(subject_id, course_id, name, teacher, quota);

        // Create if it doesn't already exist
        if (this->subjects.find(subject_id) == this->subjects.end()) {
            std::vector<Course> subject;
            this->subjects[subject_id] = subject;
        }

        this->subjects[subject_id].push_back(course);
    }
}
