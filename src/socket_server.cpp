#include "socket_server.h"
#include <array>


void SocketServer::open_socket(int port_){
    server_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    set_socket_options(server_fd);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( port_ );
    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_fd, 3);
    std::cout<<"Socket server Configured"<<std::endl;
}

void SocketServer::receive_packets(){
    std::cout<<"Packets Listener Start"<<std::endl;
    int server_address_len = sizeof(server_address);
    Buffer buffer;
    while(true){
        buffer.fill(0);
        new_socket = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t*)&server_address_len);
        int n = read(new_socket , buffer.data(), 500);
        if (n<0) {
            std::cout<<"error reading"<<std::endl;
        }
        analyze_packet(buffer);
    }
}

void SocketServer::send_packets(Buffer buffer, sockaddr_in address){
    cliend_fd = socket(AF_INET, SOCK_STREAM, 0) ;

    set_socket_options(server_fd);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    send(new_socket , buffer.data() , buffer.size() , 0 );
}


void SocketServer::analyze_packet(Buffer buffer){
        SERIALMCPFRAME frame;
        frame.INSTRUCTIONS = buffer.at(0);
        frame.CONFIG = buffer.at(1);
        frame.IONUMBER = buffer.at(2);
        frame.VALUE = buffer.at(3);
        for( int i =4 ; i < 34; i++)
            frame.NAME[i-4] = buffer.at(i);
        settingsserver->analyze_packet(frame);    
    

}

void SocketServer::register_settingsserver(SettingsServer *settingsserver_){
    settingsserver = settingsserver_;

}

void SocketServer::set_socket_options(int socket) const
{
    int opt = 1;
    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
}
