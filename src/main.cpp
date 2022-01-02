#include "MCP_Manager.h"
#include "Settings_server.h"
#include "socket_server.h"
#include "MCP_Settings.h"
#include <iostream>
#include <thread>
#include "MCP_Mosquitto.h"
#include "MCP_rw_config.h"



MCP_rw_config mcp_rw_cfg;
mcp_rw_cfg.read_config();
mqtt_client mqtt(mcp_rw_cfg.get_mqqt_ClientId().c_str(), mcp_rw_cfg.get_mqtt_ip().c_str(), mcp_rw_cfg.get_mqqt_port().c_str());

MCP_Manager mcp;
SettingsServer settingsserver;
SocketServer socketserver;
MCP_Settings mcpsettings;

void keep_alive_message(){
    std::string msg = "Online";
    while (true){
        mqtt.publish(NULL, "MCP_Array", msg.length(), msg.c_str());
        for(int i = 0; i < 64; i++){
            bool value = mcp.read_output_buffer(i);
            std::string msg; 
            std::string pu = "MCP_OUT_P_"; 
            if(value){
                msg = "ON";
            }
            else{
                msg = "OFF";
            }
            pu += std::to_string(i);
            mqtt.publish(NULL, pu.c_str(), msg.length(), msg.c_str());
            usleep(1000);
        }
        sleep(60); 
    }
}

void th1(){
    socketserver.receive_packets();
}

void th2(){
    mqtt.client_loop_forever();
}
void th3(){
    keep_alive_message();
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
    std::thread t3(th3);
    while(true){
        mcp.scan_all_inputs();
    }
} 