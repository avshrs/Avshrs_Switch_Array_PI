#include "socket_server.h"


void SocketServer::open_socket(int port_){
    server_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( port_ );
    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_fd, 3);
    std::cout<<"Socket server Configured"<<std::endl;
}

void SocketServer::receive_packages(){
    std::cout<<"Packets Listener Start"<<std::endl;
    int server_address_len = sizeof(server_address);
    while(true){
        char buffer[500] = {0};
        
        new_socket = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t*)&sizeof(server_address));
        int n = read(new_socket , buffer, 500);
        if (n<0) {
            std::cout<<"error reading"<<std::endl;
        }
        analyze_packet(buffer);
    }
}

void SocketServer::send_packlage(char* buffer[500], sockaddr_in address){
    cliend_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    send(new_socket , buffer , sizeof(buffer) , 0 );
}


void SocketServer::analyze_packet(char* buffer){

}