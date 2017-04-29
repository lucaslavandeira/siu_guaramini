#include <vector>
#include <string>
#include <iostream>
#include <bits/unique_ptr.h>
#include "common_socket.h"
#include "common_split.h"
#include "common_protocol_socket.h"
#include "server_Database.h"
#include "server_Student.h"
#include "server_Teacher.h"

#define COMANDO 0
#define MATERIA 1
#define CURSO 2

#define TIPO 0
#define ID 1

int main(int argc, char** argv) {
    Socket s(std::stoi(argv[1]));
    Database d(argv[2], argv[3]);

    Socket client = s.accept_client();

    std::string first_msg = protocol_receive(client);


    std::vector<std::string> args = split(first_msg, '-');
    std::cerr << args[TIPO] << " " << args[ID] << " conectado." << std::endl;
    User* user;
    if (args[TIPO] == "alumno") {
        user = new Student(d, std::stoi(args[ID]));
    } else if (args[TIPO] == "docente") {
        bool found = false;
        int teacher_id = d.teachers.find(std::stoi(args[ID]))->first;
        for (auto subject = d.subjects.begin();
             subject != d.subjects.end(); subject++) {
            for (Course& c : subject->second) {
                if (c.get_teacher() == teacher_id) {
                    found = true;
                    user = new Teacher(d, c);
                    break;
                }
            }

            if (found) {
                break;
            }
        }

        if (!found) {
            std::cerr << args[ID] << " es un tipo de usuario docente inválido";
            return 1;
        }
    } else {
        std::cerr << args[ID] << " es un tipo de usuario inválido.\n";
        return 1;
    }

    std::string command = protocol_receive(client);
    while (command != "quit") {
        std::vector<std::string> cmds = split(command, '-');
        std::cerr << args[TIPO] << " " << args[ID] <<
                  " ejecuta " << cmds[COMANDO] << std::endl;


        // Generate a response
        std::string response = user->process_command(cmds);

        protocol_send(client, response.c_str(),
                      (unsigned int) response.length() + 1); // len + '\0' char
        command = protocol_receive(client);
    }

    std::cerr << args[TIPO] << " " << args[ID] << " desconectado." << std::endl;
    return 0;
}
