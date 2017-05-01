#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include "server_Course.h"
#include "server_Database.h"
#include "server_TSVParser.h"
#include "server_Lock.h"



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
            throw DatabaseError("Incorrect students file format\n");
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

        Course course(subject_id, course_id, name, teacher_id, quota);

        // Create if it doesn't already exist
        if (this->subjects.find(subject_id) == this->subjects.end()) {
            std::vector<Course> subject;
            this->subjects[subject_id] = subject;
        }

        this->subjects[subject_id].push_back(course);
    }
}

std::string Database::subscribe(int subject_id, int course_id, int student_id) {
    std::stringstream result;
    for (auto it = subjects.begin();
         it != subjects.end();
         it ++) {
        if (it->first == subject_id) {
            for (auto jt = it->second.begin(); jt != it->second.end(); jt ++) {
                if (jt->get_course() == course_id) {
                    if (!jt->get_remaining_spots()) {
                        result << "El curso " << course_id <<
                               " de la materia " << subject_id <<
                               " no posee mas vacantes." << std::endl;
                        return result.str();
                    }
                    Lock(this->m);

                    bool subbed = jt->subscribe(student_id);
                    if (!subbed) {
                        result << "Inscripción ya realizada." << std::endl;
                        return result.str();
                    }
                    result << "Inscripción exitosa." << std::endl;

                    return result.str();
                }
            }
            result << "El curso " << course_id << " en la materia " <<
                   subject_id << " no es válido." << std::endl;
            return result.str();
        }
    }
    result << "La materia " << subject_id << " no es válida." << std::endl;

    return result.str();
}

DatabaseError::DatabaseError(const char *msg, ...) noexcept  {
    strncpy(buf, msg, strlen(msg));
}

const char *DatabaseError::what() const noexcept {
    return buf;
}

