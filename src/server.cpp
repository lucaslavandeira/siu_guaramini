#include <vector>
#include <string>
#include <iostream>
#include "common_socket.h"
#include "server_Database.h"
#include "server_ClientAccepter.h"

#define QUIT_CHAR 'q'


int main(int argc, char** argv) {
    /* Runs a subscription system server. Reads the following arguments from
     * the command line:
     * argv[1]: port to start the server on
     * argv[2]: text file to read the users from
     * argv[3]: text file to read the subjects from
     * Consult the assigment for the text files' format.
     */

    int port = std::stoi(argv[1]);
    Socket s(port);
    Database d(argv[2], argv[3]);

    // Run a thread to accepts new clients from
    ClientAccepter accepter(s, d, port);

    accepter.start();

    std::string input;
    char in = 0;
    // Stop running as soon as we get a QUIT_CHAR in the standard input
    while (in != QUIT_CHAR) {
        std::cin >> in;
    }
    accepter.kill(); // Signal the accepter to stop running
    accepter.join();
    return 0;
}
