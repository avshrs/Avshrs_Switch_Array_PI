#include "socket_server.h"

void SocketServer::set_port(int port_){
    port = port_;
}

void SocketServer::open_socket(){
    server_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    std::cout<<"Socket server Configured"<<std::endl;

}

void SocketServer::receive_package(SettingsServer *settingsserver_){
    std::cout<<"Packets Listener Start"<<std::endl;
    while(true){
        SERIALMCPFRAME frame;
        char buffer[500] = {0};
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        int n = read(new_socket , buffer, 500);
        if (n<0) {
            std::cout<<"error reading"<<std::endl;
        }
        frame.INSTRUCTIONS = buffer[0];
        frame.CONFIG = buffer[1];
        frame.IONUMBER = buffer[2];
        frame.VALUE = buffer[3];
        settingsserver_->analyze_packet(frame);
    }
}

void SocketServer::send_packlage(SERIALMCPFRAME data){
    uint8_t dat[4] = {data.INSTRUCTIONS,data.CONFIG, data.IONUMBER,data.VALUE};
    send(new_socket , dat , sizeof(dat) , 0 );
}

void SocketServer::register_listener(SettingsServer *settingsserver_){
    
}