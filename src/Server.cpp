#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include "Server.h"
#include "common_split.h"

const int student = 1; // Temporary until sockets introduced

Server::~Server() {
}

Server::Server(int port) :
    s("localhost", port)
{
    TSVParser user_parser("usuarios.txt");
    while (!user_parser.eof()) {
        std::vector<std::string> row = user_parser.parse_row();
        int id = atoi(row.at(1).c_str());

        if (row.at(0) == "docente") {
            teachers[id] = row.at(2);
        } else if (row.at(0) == "alumno") {
            students[id] = row.at(2);
        } else {
            throw 0;
        }
    }

    TSVParser subject_parser("materias.txt");
    while (!subject_parser.eof()) {
        std::vector<std::string> row = subject_parser.parse_row();

        int subject_id = std::stoi(row.at(0));
        int course_id = std::stoi(row.at(1));
        std::string name = std::move(row.at(2));
        int teacher_id = std::stoi(row.at(3));
        std::string teacher = teachers.at(teacher_id).c_str();
        int quota = std::stoi(row.at(4));

        Course course(course_id, name, teacher, quota);

        // Create if it doesn't already exist
        if (subjects.find(subject_id) == subjects.end()) {
            std::vector<Course> subject;
            subjects[subject_id] = subject;
        }

        subjects[subject_id].push_back(course);
    }
}

std::string Server::receive(const std::string &msg) {
    std::vector<std::string> args = split(msg, '-');
    if (args.at(0) == "lm") {
        return listSubjects();
    } else if (args.at(0) == "in") {
        int subject_id = std::stoi(args.at(1));
        int course_id = std::stoi(args.at(2));
        return subscribe(subject_id, course_id);
    } else {
        return "quit";
    }
}

std::string Server::listSubjects() {
    std::stringstream result;
    for (std::pair<const int, std::vector<Course>> pair: subjects) {
        for (Course c: pair.second) {
            result << pair.first << " - " << c.get_name() <<
                   ", Curso " << c.get_course() <<
                   ", " << c.get_teacher() << ", "
                   << c.get_remaining_spots() << " vacantes." << std::endl;
        }
    }
    return result.str();
}

std::string Server::subscribe(int subject_id, int course_id) {
    std::stringstream result;
    for (auto it = subjects.begin(); it != subjects.end(); it ++) {
        if (it->first == subject_id) {
            for (auto jt = it->second.begin(); jt != it->second.end(); jt ++) {
                if (jt->get_course() == course_id) {
                    if (!jt->get_remaining_spots()) {
                        result << "El curso " << course_id <<
                               " de la materia " << subject_id <<
                               " no posee más vacantes." << std::endl;
                        return result.str();
                    }

                    bool subbed = jt->subscribe(student);
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
