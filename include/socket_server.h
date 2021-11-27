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



class SocketServer{
    public:
        int port=5656;
        int server_fd;
        int new_socket;
        int valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        SettingsServer *settingsserver_;
        void set_port(int port_);
        void open_socket();
        void register_listener(SettingsServer *settingsserver_);
        void receive_package(SettingsServer *settingsserver_);
        void send_packlage(SERIALMCPFRAME data);
   
};

#endif //SSERVER_H