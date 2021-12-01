#ifndef SSERVER_H
#define SSERVER_H
#include <vars.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "Settings_server.h"
#include <cstring>


class SocketServer{
    public:

        int server_fd;
        int cliend_fd;
        int new_socket;
        int valread;
        struct sockaddr_in server_address;
        int opt = 1;
        int addrlen = sizeof(address);
        
        void open_socket(int port_);
        void receive_packages();
        void send_packlage(char* buffer[500], sockaddr_in address);
        void analyze_packet(char* buffer);
};

#endif //SSERVER_H