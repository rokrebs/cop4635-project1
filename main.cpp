//
//  main.cpp
//  Project1
//
//  Created by Rocio Krebs on 2/10/22.
//

#include "paketHandler.hpp"
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// read a file into memory
#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#define PORT 60060

using namespace std;

int main(int argc, const char *argv[]) {

  int server_fd;
  int new_socket;
  long valread;
  int waitSize = 16;
  struct sockaddr_in address;
  int addressLen = sizeof(address);

  // creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error: Listen socked failed!");
    exit(1);
  } else {
    printf("Server started.");
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  memset(address.sin_zero, '\0', sizeof address.sin_zero);
        printf("Bind:\n");
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Error: binding failed!");
    exit(1);
  } else {
    printf("Server ready.");
  }
printf("Listen:\n");
  if (listen(server_fd, waitSize) < 0) {
    perror("Error: listetning failed!");
    exit(1);
  } else {
    printf("Server listening and waiting for client request...");
  }
printf("Go long\n");
  // handle the connection
  for (;;) { // run forever
        printf("New Conn Made:\n");
    // accept connections from client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addressLen)) < 0) {
      perror("Error: accepting failed");
      exit(1);
    }

    // Data transfer section

    char buffer[30000];
    while ((valread = read(new_socket, buffer, 30000)) > 0) {
      // create string and return that string in write.
      paketHandler paket(buffer);
	   printf("%s\n",buffer);
      std::string msg = paket.printMsg();
        printf("%s\n",(char*)msg.c_str());  
      write(new_socket, (char *)msg.c_str(),(int)msg.size());
      //  printf("\n-------------Hello message sent--------------");
    }

    close(new_socket);
  }

  return 0;
}
