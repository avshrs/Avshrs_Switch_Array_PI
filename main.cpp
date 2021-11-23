#include "MCP_Manager.h"
#include "Settings_server.h"
#include "socket_server.h"
#include "MCP_Settings.h"
#include <iostream>
#include <thread>

MCP_Manager mcp;
SettingsServer settingsserver;
SocketServer socketserver;
MCP_Settings mcpsettings;

void th(bool t){
    socketserver.receive_package(&settingsserver);
}

int main(void){ 
    settingsserver.register_mcp_settings(&mcpsettings);
    mcp.register_mcp_settings(&mcpsettings);
    socketserver.open_socket();
    std::thread t1(th, true);
    mcp.MCP_Init();

    while(true){
        mcp.scan_io();
    }
            
} 

