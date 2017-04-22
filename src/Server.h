#ifndef TP3TALLER_SERVER_H
#define TP3TALLER_SERVER_H

#include <string>
#include <vector>
#include <map>
#include "Socket.h"
#include "TSVParser.h"
#include "Course.h"

class Server {
    Socket s;
    std::vector<Course> courses;
    std::map<int, std::string> students;
    std::map<int, std::string> teachers;
public:
    explicit Server(int port);
    ~Server();

    std::string receive(const std::string &msg);
};


#endif //TP3TALLER_SERVER_H
