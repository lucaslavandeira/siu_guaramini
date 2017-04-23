#ifndef TP3TALLER_SERVER_H
#define TP3TALLER_SERVER_H

#include <string>
#include <vector>
#include <map>
#include "common_socket.h"
#include "server_TSVParser.h"
#include "server_Course.h"

class Server {
    Socket s;
    std::map<int, std::vector<Course>> subjects;
    std::map<int, std::string> students;
    std::map<int, std::string> teachers;
public:
    explicit Server(int port);
    ~Server();

    std::string receive(const std::string &msg);

private:
    std::string listSubjects();
    std::string listSubs();
    std::string subscribe(int subject_id, int course_id);
    std::string desubscribe(int subject_id, int course_id);
};


#endif //TP3TALLER_SERVER_H
