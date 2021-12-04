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
#include <array>

using Buffer = std::array<char, 500>;

class SocketServer{
    public:
        int server_fd;
        int cliend_fd;
        int new_socket;
        int valread;
        SettingsServer *settingsserver;
        struct sockaddr_in server_address;
        int addrlen = sizeof(server_address);

    public:
        void register_settingsserver(SettingsServer *settingsserver_);
        void open_socket(int port_);
        void receive_packets();
        void send_packets(Buffer buffer, sockaddr_in address);
        void analyze_packet(Buffer buffer);

    private:
        void set_socket_options(int socket) const;
};

#endif //SSERVER_H