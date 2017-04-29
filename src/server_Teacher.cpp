#include "server_Teacher.h"
#include "server_Student.h"
#include <string>
#include <vector>
#include <sstream>

#define COMANDO 0
#define ALUMNO 1
#define MATERIA 2
#define CURSO 3
Teacher::Teacher(Database &database, Course& course) :
    User(database),
    course(course)
{
}

std::string Teacher::listSubs() {
    std::stringstream result;

    result << course.get_subject() << " - " << course.get_name() <<
           ", Curso " << course.get_course() << ", " << course.get_teacher() <<
           ":\n";

    for (int student_id : course.get_students()) {
        result << student_id << " " <<
               database.students.find(student_id)->second << "\n";
    }
    return result.str();
}

Teacher::~Teacher() {
}

std::string
Teacher::unsubscribe(int student_id, int subject_id, int course_id) {
    auto student = database.students.find(student_id);
    if (student == database.students.end()) {
        return "Desinscripción inválida\n";
    }

    if (subject_id != course.get_subject() ||
        course_id != course.get_course()) {
        std::stringstream result;
        result << "No tiene permisos para operar sobre " << subject_id <<
               ", curso " << course_id << "." << std::endl;
        return result.str();
    }
    return Student(database, student_id).unsubscribe(subject_id, course_id);
}

std::string Teacher::subscribe(int student_id, int subject_id, int course_id) {
    std::stringstream result;
    auto student = database.students.find(student_id);
    if (student == database.students.end()) {
        result << "El alumno " << student_id << " es inválido." << std::endl;
        return result.str();
    }

    if (subject_id != course.get_subject() ||
        course_id != course.get_course()) {
        result << "No tiene permisos para operar sobre " << subject_id <<
               ", curso " << course_id << "." << std::endl;
        return result.str();
    }

    return Student(database, student_id).subscribe(subject_id, course_id);
}

std::string Teacher::process_command(std::vector<std::string>& args) {
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

std::string Teacher::get_identifier() {
    std::stringstream result;
    result << "docente " << course.get_teacher();
    return result.str();
}
