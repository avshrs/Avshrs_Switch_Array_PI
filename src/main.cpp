#include "MCP_Manager.h"
#include "Settings_server.h"
#include "socket_server.h"
#include "MCP_Settings.h"
#include <iostream>
#include <thread>
#include "MCP_Mosquitto.h"

char client_id[] = "SwitchMatrix";
char host[] = "192.168.1.96";
int port = 1883;
mqtt_client mqtt(client_id, host, port);

MCP_Manager mcp;
SettingsServer settingsserver;
SocketServer socketserver;
MCP_Settings mcpsettings;


void th1(){
    socketserver.receive_packets();
}

void th2(){
    mqtt.client_loop_forever();
}

int main(){ 
    mqtt.register_mcp_manager(&mcp);
    mcp.register_mcp_mqtt(&mqtt);
    mcpsettings.read_settings();
    settingsserver.register_mcp_settings(&mcpsettings);
    mcp.register_mcp_settings(&mcpsettings);
    socketserver.open_socket(5656);
    socketserver.register_settingsserver(&settingsserver);
    mcp.MCP_Init();
    std::thread t1(th1);
    std::thread t2(th2);
    while(true){
        mcp.scan_all_inputs();
    }
} 