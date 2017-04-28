#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <utility>
#include <iostream>
#include <string>
#include "common_socket.h"

#define BUF_SIZE 100

class ConnectionError : public std::exception {
    char buf[256];
public:
    explicit ConnectionError(const char* msg, ...) noexcept {
        strncpy(buf, msg, strlen(msg));
        perror("perror");
    }

    virtual const char* what() const noexcept {
        return buf;
    }
};

Socket::Socket(int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("");
        throw 0;
    }

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl(INADDR_ANY);
    srv.sin_port = htons((uint16_t) port);

    int error = bind(fd, (struct sockaddr *) &srv, sizeof(srv));
    if (error) {
        throw ConnectionError("Error binding socket on creation! "
                                      "Most likely port already in use");
    }

    listen(fd, 10);
}

Socket::Socket(const char *addr, int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons((uint16_t)port);
    srv.sin_addr.s_addr = inet_addr(addr);

    socklen_t len = (socklen_t)sizeof(struct sockaddr);
    int error = connect(fd, (struct sockaddr *) &srv, len);

    if (error) {
        throw ConnectionError("Error connecting to server!");
    }
}


Socket Socket::accept_client() {
    struct sockaddr_in client;
    socklen_t clilen = (socklen_t) sizeof(struct sockaddr_in);

    int client_fd = accept(fd, (struct sockaddr *) &client, &clilen);

    if (client_fd < 0) {
        throw 0;
    }

    Socket client_socket;
    client_socket.fd = client_fd;
    return client_socket;
}

Socket::Socket() {
}

Socket::Socket(Socket&& other) {
    fd = std::move(other.fd);
}

ssize_t Socket::send(const char *msg, unsigned int len) {
    size_t total_bytes = 0;
    ssize_t sent = 1;

    // Sends msg until it's complete OR socket_send returns 0 (connection
    // closed)
    while (total_bytes < len && sent) {
        sent = ::send(fd, msg + total_bytes, len - total_bytes,
                      MSG_NOSIGNAL);
        if (sent < 0) {
            throw ConnectionError("Error sending msg %s", msg);
        }
        total_bytes += sent;
    }

    return total_bytes;
}

ssize_t Socket::receive(char *dest, size_t len) {
    ssize_t received = 1;
    size_t total_bytes = 0;

    // Writes to dest until it's complete OR socket_recv returns 0 (connection
    // closed)
    while (total_bytes < len && received) {
        received = recv(fd, dest + total_bytes, len - total_bytes,
                        MSG_NOSIGNAL);
        if (received < 0) {
            throw ConnectionError("Error receiving message!");
        }
        total_bytes += received;
    }
    return total_bytes;
}


Socket::~Socket() {
    close(fd);
}

