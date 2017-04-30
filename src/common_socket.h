#ifndef TP3TALLER_COMMON_SOCKET_H
#define TP3TALLER_COMMON_SOCKET_H

#include <string>

#define LISTEN_BACKLOG 10 // Amt. of connections to have in the accept backlog

// Socket class. Wraps functionality of glibc's socket functions.
class Socket {
    int fd;

public:
    /* Server constructor. Creates a socket, binds and listens to the specified
     * port. */
    explicit Socket(int port);

    /* Client constructor. Creates a socket and attempts to connect to the
     * specified address/port. Raises exception if the connection fails. */
    Socket(const char *addr, int port);

    ~Socket();

    // Returns a new client.
    Socket accept_client();

    // Sends/recieves len bytes of data
    ssize_t send(const char *msg, unsigned int len);
    ssize_t receive(char *dest, size_t len);

    // Wrapper for socket shutdown/close
    void shutdown();
    void close();
    // Move constructor
    Socket(Socket&& other);

private:
    Socket();

    Socket(Socket&) = delete;
    void operator=(Socket&) = delete;
};

class SocketError : public std::exception {
    char buf[256];

public:
    explicit SocketError(const char* msg, ...) noexcept;

    virtual const char* what() const noexcept;
};

#endif //TP3TALLER_COMMON_SOCKET_H
