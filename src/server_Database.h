#ifndef TP3TALLER_DATABASE_H
#define TP3TALLER_DATABASE_H

#include <vector>
#include <map>
#include <string>
#include <mutex>
#include "server_Course.h"


/* Struct that packs the loaded courses and users of the server database.
 * Thread safe on (un)subscribing students to courses. */
struct Database {
    std::mutex m;
    std::map<int, std::vector<Course>> subjects;
    std::map<int, std::string> students;
    std::map<int, std::string> teachers;

public:
    Database(char* users, char* subjects);

    // Adds a student to the database
    std::string subscribe(int subject_id, int course_id, int student_id);
};

class DatabaseError : std::exception {
    char buf[256];
public:
    explicit DatabaseError(const char* msg, ...) noexcept;

    virtual const char* what() const noexcept;
};


#endif //TP3TALLER_DATABASE_H
