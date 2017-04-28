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


std::string Student::subscribe(int subject_id, int course_id) {
    std::stringstream result;
    for (auto it = database.subjects.begin();
         it != database.subjects.end();
         it ++) {
        if (it->first == subject_id) {
            for (auto jt = it->second.begin(); jt != it->second.end(); jt ++) {
                if (jt->get_course() == course_id) {
                    if (!jt->get_remaining_spots()) {
                        result << "El curso " << course_id <<
                               " de la materia " << subject_id <<
                               " no posee más vacantes." << std::endl;
                        return result.str();
                    }

                    bool subbed = jt->subscribe(this->id);
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

std::string Student::unsubscribe(int subject_id, int course_id) {
    std::stringstream result;
    for (auto it = database.subjects.begin();
         it != database.subjects.end();
         it ++) {
        if (it->first == subject_id) {
            for (auto jt = it->second.begin(); jt != it->second.end(); jt++) {
                if (jt->get_course() == course_id) {
                    bool done = jt->desubscribe(this->id);
                    if (done) {
                        return "Desinscripción exitosa\n";
                    }
                    break;
                }
            }
        }
    }
    return "Desinscripción inválida\n";
}

Student::~Student() {
}
