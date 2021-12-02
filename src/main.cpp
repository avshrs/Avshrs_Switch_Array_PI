#include "MCP_Manager.h"
#include "Settings_server.h"
#include "socket_server.h"
#include "MCP_Settings.h"
#include <iostream>
#include <thread>
#include "MCP_Mosquitto.h"
MCP_Mosquitto mcp_mosq;
MCP_Manager mcp;
SettingsServer settingsserver;
SocketServer socketserver;
MCP_Settings mcpsettings;

void th(bool t){
    socketserver.receive_packets();
}
void th1(bool t){
    mcp_mosq.mos_connect();
}

int main(void){ 
    mcp_mosq.register_mcp_manager(&mcp);
    mcpsettings.read_settings();
    settingsserver.register_mcp_settings(&mcpsettings);
    mcp.register_mcp_settings(&mcpsettings);
    socketserver.open_socket(5656);
    socketserver.register_settingsserver(&settingsserver);
    std::thread t1(th, true);
    std::thread t2(th1, true);
    mcp.MCP_Init();
    
    while(true){
        mcp.scan_all_io();
    }
            
} 

