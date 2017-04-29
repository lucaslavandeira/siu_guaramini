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
    for (const Course* c : subbed_courses) {
        result << c->get_subject() << " - " << c->get_name() <<
               ", Curso " << c->get_course() << ", " <<
               c->get_teacher() << "." << std::endl;
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
                    subbed_courses.push_back(&(*jt));
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
    for (auto c = subbed_courses.begin(); c != subbed_courses.end(); c++) {
        if ((*c)->get_course() == course_id &&
                (*c)->get_subject() == subject_id) {
            bool done = (*c)->desubscribe(this->id);
            if (done) {
                subbed_courses.erase(c);
                return "Desinscripción exitosa\n";
            }
        }
    }
    return "Desinscripción inválida\n";
}

Student::~Student() {
}
