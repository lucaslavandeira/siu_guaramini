#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include "server_Student.h"

#define COMANDO 0
#define MATERIA 1
#define CURSO 2

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
               database.teachers.find(c->get_teacher())->second << "." <<
               std::endl;
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
    auto subject = database.subjects.find(subject_id);
    if (subject == database.subjects.end()) {
        return "Desinscripción inválida.\n";
    }

    for (Course& c : subject->second) {
        if (c.get_course() == course_id) {
            if (c.is_subscribed(id)) {
                c.desubscribe(id);
                return "Desinscripción exitosa.\n";
            }
        }
    }
    return "Desinscripción inválida.\n";
}


std::string Student::process_command(std::vector<std::string>& args) {
    std::string response;
    if (args[COMANDO] == "lm") {
        response = listSubjects();
    } else if (args[COMANDO] == "li") {
        response = listSubs();
    } else if (args[COMANDO] == "in") {
        response = subscribe(std::stoi(args[MATERIA]),
                                     std::stoi(args[CURSO]));
    } else if (args[COMANDO] == "de") {
        response = unsubscribe(std::stoi(args[MATERIA]),
                                       std::stoi(args[CURSO]));
    } else {
        response = "Should never happen\n";
    }
    return response;
}

Student::~Student() {
}

std::string Student::get_identifier() {
    std::stringstream result;
    result << "alumno " << id;
    return result.str();
}
