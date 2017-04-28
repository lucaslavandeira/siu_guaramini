#ifndef TP3TALLER_COMMON_SOCKET_H
#define TP3TALLER_COMMON_SOCKET_H

#include <cstdio>
#include <string>

class Socket {
    int fd;
public:
    explicit Socket(int port);
    Socket(const char *addr, int port);
    ~Socket();

    Socket accept_client();

    ssize_t send(const char *msg, unsigned int len);
    ssize_t receive(char *dest, size_t len);

    Socket(Socket&& other);
private:
    Socket();

    Socket(Socket&) = delete;
    void operator=(Socket&) = delete;
};


#endif //TP3TALLER_COMMON_SOCKET_H
