#include <sstream>
#include <string>
#include <vector>
#include "server_Admin.h"
#include "server_Teacher.h"
#include "server_Student.h"

#define COMANDO 0
#define ALUMNO 1
#define MATERIA 2
#define CURSO 3

Admin::Admin(Database &database) : User(database) {
}

Admin::~Admin() {
}

std::string Admin::process_command(std::vector<std::string>& args) {
    std::string response;
    if (args[COMANDO] == "lm") {
        response = listSubjects();
    } else if (args[COMANDO] == "li") {
        response = listSubs();
    } else if (args[COMANDO] == "in") {
        if (args.size() < 4) {
            return "Cantidad de argumentos insuficientes.\n";
        }
        response = subscribe(std::stoi(args[ALUMNO]),
                             std::stoi(args[MATERIA]),
                             std::stoi(args[CURSO]));
    } else if (args[COMANDO] == "de") {
        if (args.size() < 4) {
            return "Cantidad de argumentos insuficientes.\n";
        }
        response = unsubscribe(std::stoi(args[ALUMNO]),
                               std::stoi(args[MATERIA]),
                               std::stoi(args[CURSO]));
    } else {
        response = "Should never happen\n";
    }
    return response;
}

std::string Admin::listSubs() {
    std::stringstream result;
    for (auto it = database.subjects.begin();
         it != database.subjects.end();
         it ++) {
        for (Course &c : it->second) {
            result << Teacher(database, c).listSubs();
        }
    }
    return result.str();
}

std::string Admin::subscribe(int student_id, int subject_id, int course_id) {
    std::stringstream result;
    auto student = database.students.find(student_id);
    if (student == database.students.end()) {
        result << "El alumno " << student_id << " es inválido." << std::endl;
        return result.str();
    }

    return Student(database, student_id).subscribe(subject_id, course_id);
}

std::string Admin::unsubscribe(int student_id, int subject_id, int course_id) {
    return Student(database, student_id).unsubscribe(subject_id, course_id);
}

std::string Admin::get_identifier() {
    return "admin";
}
