/*
 * @autor Rocio Krebs
 *
 */

#include "paketHandler.hpp"
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// read a file into memory
//#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#include <sys/wait.h>
#include <unistd.h>

#define PORT 60060

using namespace std;

int server_fd;
int new_socket;
long valread;
int waitSize = 16;
struct sockaddr_in address;
int addressLen = sizeof(address);

void server();
void server() {
    // creating socket file descriptor
    cout << "Server started." << endl;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error: Listen socked failed!");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    printf("Bind:\n");
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Error: binding failed!");
        exit(1);
    }
    cout << "Server is listening" << endl;
    if (listen(server_fd, waitSize) < 0) {
        perror("Error: listetning failed!");
        exit(1);
    }
    cout << "Server listening and waiting for client request..." << endl;
}


int main() {
    server();
    // handle the connection
    while (1) { // run forever

        // accept connections from client
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
                                 (socklen_t * ) & addressLen)) < 0) {
            perror("Error: accepting failed");
            exit(1);
        }
        if (fork() == 0) {
            cout << "New client is connected" << endl;
            // Data transfer section
            char buffer[30000];
            while ((valread = read(new_socket, buffer, 30000)) > 0) {
                // create string and return that string in write.
                paketHandler paket(buffer);
                std::string msg = paket.printMsg();
                write(new_socket, (char *) msg.c_str(), (int) msg.size());
            }
            close(new_socket);
            exit(0);
        } else {
            cout << "waiting for more clients" << endl;
        }
    }
}
