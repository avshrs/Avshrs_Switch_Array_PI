#pragma once
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

class SocketServer{
    public:

        int server_fd;
        int cliend_fd;
        int new_socket;
        int valread;
        SettingsServer *settingsserver;
        struct sockaddr_in server_address;
        int opt = 1;
        int addrlen = sizeof(server_address);
        void register_settingsserver(SettingsServer *settingsserver_);
        void open_socket(int port_);
        void receive_packets();
        void send_packets(char* buffer[500], sockaddr_in address);
        void analyze_packet(std::array<char, 500> buffer);
};

