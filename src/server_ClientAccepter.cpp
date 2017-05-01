#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "server_ClientAccepter.h"
#include "common_protocol_socket.h"
#include "common_split.h"
#include "server_Student.h"
#include "server_Admin.h"
#include "server_PrintMonitor.h"

#define TIPO 0
#define ID 1

ClientAccepter::ClientAccepter(Socket& server, Database& d, int port) :
    s(std::move(server)),
    d(d),
    port(port)
{
}

ClientAccepter::~ClientAccepter() {
}

User* ClientAccepter::validate_client(std::string first_msg) {
    std::vector<std::string> args = split(first_msg, '-');
    User* user = nullptr;
    std::stringstream msg;
    if (args[TIPO] == "alumno") {
        if (d.students.find(stoi(args[ID])) == d.students.end()) {
            msg << args[ID] << " es un tipo de usuario alumno inválido\n";
            printer.print(msg.str());
            return nullptr;
        }
        user = new Student(d, std::stoi(args[ID]));
        msg << "alumno " << args[ID] << " conectado."
                  << std::endl;
    } else if (args[TIPO] == "docente") {
        bool found = false;
        int teacher_id = d.teachers.find(std::stoi(args[ID]))->first;
        for (auto subject = d.subjects.begin();
             subject != d.subjects.end(); subject++) {
            for (Course &c : subject->second) {
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
            msg << args[ID] << " es un tipo de usuario docente inválido";
            printer.print(msg.str());
            return nullptr;
        }
        msg << "docente " << args[ID] << " conectado."
                  << std::endl;
    } else if (args[TIPO] == "admin") {
        args.push_back("");
        user = new Admin(d);
        msg << "admin conectado.\n";
    } else {
        msg << args[ID] << " es un tipo de usuario inválido.\n";
        printer.print(msg.str());
        return nullptr;
    }
    printer.print(msg.str());
    return user;
}

void ClientAccepter::run() {
    running = true;
    try {
        while (running) {
            Socket new_client = s.accept_client();

            std::string first_msg = protocol_receive(new_client);
            if (first_msg == "") {
                break;
            }
            User *user = validate_client(first_msg);

            if (!user) { // Bad arguments, wait for another connection
                new_client.shutdown();
                continue;
            }

            clients.emplace_back(new_client, user, printer);
            clients.back().start();

            // Clean up done threads
            for (auto client_it = clients.begin();
                 client_it != clients.end();
                 client_it++) {
                if (client_it->is_done()) {
                    client_it->join();

                    // Update iterator pointer
                    client_it = clients.erase(client_it);
                }
            }
        }
    } catch (SocketError e) {
        return;
    }
}

void ClientAccepter::kill() {
    s.shutdown();
    running = false;

    for (auto it = clients.begin(); it != clients.end(); it++) {
        it->terminate();
        it->join();
    }
}

