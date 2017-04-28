#ifndef TP3TALLER_PROTOCOL_SOCKET_H
#define TP3TALLER_PROTOCOL_SOCKET_H

#include <string>
#include "common_socket.h"


/* Sends (receives) 'len' bytes of data to (from) socket s, taken from (sent to)
 * the char* buffer. Complies with the assignment protocol of sending (receving)
 * the message length through the socket first, then the actual message. */

void protocol_send(Socket& s, const char* msg, unsigned int len);
std::string protocol_receive(Socket& s);

#endif //TP3TALLER_PROTOCOL_SOCKET_H
