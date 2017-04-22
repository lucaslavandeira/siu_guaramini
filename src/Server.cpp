#include <iostream>
#include <vector>
#include <string>
#include "Server.h"
#include "common_split.h"

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

        int subject = atoi(row.at(0).c_str());
        int course = atoi(row.at(1).c_str());
        std::string name = std::move(row.at(2));
        std::string teacher = teachers.at(atoi(row.at(3).c_str())).c_str();
        int quota = atoi(row.at(4).c_str());

        courses.push_back(Course(subject, course, name, teacher, quota));
    }
}

std::string Server::receive(const std::string &msg) {
    std::vector<std::string> args = split(msg, '-');

    if (args.at(0) == "lm") {
        return listSubjects();
    } else {
        return "quit";
    }
}

std::string Server::listSubjects() {
    std::string result;
    for (Course c: courses) {
        result += c.print();
    }
    return result;
}
