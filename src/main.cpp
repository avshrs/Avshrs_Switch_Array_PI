#include "MCP_Manager.h"
#include <iostream>
#include <thread>
#include "MCP_Mosquitto.h"
#include "MCP_rw_config.h"


MCP_rw_config mcp_rw_cfg;
MCP_Manager mcp;

void keep_alive_message(mqtt_client *mqtt){
    std::string msg = mcp_rw_cfg.get_mqtt_keepAliveMsg();
    while (true){
        sleep(60); 
        mqtt->publish(NULL, mcp_rw_cfg.get_mqtt_keepAliveTopic().c_str(), msg.length(), msg.c_str());
        for(int i = 0; i < 64; i++){
            bool value = mcp.read_output_buffer(i);
            std::string msg; 
            std::string pu = mcp_rw_cfg.get_mqtt_outPubsring();
            if(value){
                msg = mcp_rw_cfg.get_mqtt_outONMsg();
            }
            else{
                msg = mcp_rw_cfg.get_mqtt_outOFFMsg();
            }
            pu += std::to_string(i);
            mqtt->publish(NULL, pu.c_str(), msg.length(), msg.c_str());
            usleep(1000);
        }
        
    }
}

void th2(mqtt_client *mqtt){
    sleep(50);
    mqtt->client_loop_forever();
}
void th3(mqtt_client *mqtt){
    keep_alive_message(mqtt);
}

int main(){ 
    mcp_rw_cfg.read_config();
    mqtt_client mqtt(mcp_rw_cfg.get_mqtt_ClientId().c_str(), mcp_rw_cfg.get_mqtt_ip().c_str(), mcp_rw_cfg.get_mqtt_port());
    mqtt.register_mcp_manager(&mcp);
    mqtt.register_mcp_config(&mcp_rw_cfg);
    mcp.register_mcp_mqtt(&mqtt);
    mcp.register_mcp_config(&mcp_rw_cfg);
    mcp.MCP_Init();
    std::thread t2(th2, &mqtt);
    std::thread t3(th3, &mqtt);
    while(true){
        mcp.scan_all_inputs();
    }
} 

