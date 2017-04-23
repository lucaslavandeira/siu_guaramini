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

ssize_t Socket::send(const std::string msg) {
    if (!msg.size()) {
        throw ConnectionError("Can't send empty messages through socket");
    }
    size_t total_bytes = 0;
    ssize_t sent = 1;

    int len = htonl((int) msg.size());
    while (total_bytes < 4 && sent) {
        sent = ::send(fd, &len + total_bytes, sizeof(len), MSG_NOSIGNAL);
        if (sent < 0) {
            throw ConnectionError("Error sending msg len");
        }
        total_bytes += sent;
    }
    total_bytes = 0;
    while (total_bytes < msg.size() && sent) {
        sent = ::send(fd, msg.c_str() + total_bytes, msg.size() - total_bytes,
                      MSG_NOSIGNAL);
        if (sent < 0) {
            throw ConnectionError("Error sending msg %s", msg);
        }
        total_bytes += sent;
    }

    return total_bytes;
}

std::string Socket::receive() {
    ssize_t received = 1;
    size_t total_bytes = 0;

    uint32_t len = 0;
    while (total_bytes < 4 && received) {
        received = recv(fd, &len + total_bytes, sizeof(len), MSG_NOSIGNAL);
        if (received < 0) {
            throw ConnectionError("Error receiving message len!");
        }
        total_bytes += received;
    }

    len = ntohl(len);

    std::string result;
    char buf[BUF_SIZE] = "";
    while (result.size() < len && received) {
        // Clear buffer from prev read to ensure '\0' is in the correct place
        memset(buf, 0, BUF_SIZE);

        size_t read = BUF_SIZE;
        if (read > len - result.size()) {
            read = len - result.size();
        }
        received = recv(fd, buf, read, MSG_NOSIGNAL);
        if (received < 0) {
        }
        result += buf;
    }
    return result;
}


Socket::~Socket() {
    close(fd);
}
