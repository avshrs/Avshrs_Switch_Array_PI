#include "MCP_Manager.h"
#include <iostream>
#include <thread>
#include "MCP_Mosquitto.h"
#include "MCP_rw_config.h"


MCP_rw_config mcp_rw_cfg;
MCP_Manager mcp;

void keep_alive_message(mqtt_client *mqtt){
    std::string msg = mcp_rw_cfg.get_mqtt_keepAliveMsg();
    std::cout<<7<<std::endl;
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
    mqtt->client_loop_forever();
}
void th3(mqtt_client *mqtt){
    keep_alive_message(mqtt);
}

int main(){ 
    mcp.MCP_Init();
    std::cout<<1<<std::endl;
    mcp_rw_cfg.read_config();
    std::cout<<2<<std::endl;
    mqtt_client mqtt(mcp_rw_cfg.get_mqtt_ClientId().c_str(), mcp_rw_cfg.get_mqtt_ip().c_str(), mcp_rw_cfg.get_mqtt_port());
    std::cout<<3<<std::endl;
    mqtt.register_mcp_manager(&mcp);
    mqtt.register_mcp_config(&mcp_rw_cfg);
    mcp.register_mcp_mqtt(&mqtt);
    mcp.register_mcp_config(&mcp_rw_cfg);
    
    std::cout<<4<<std::endl;
    std::thread t2(th2, &mqtt);
    std::cout<<5<<std::endl;
    std::thread t3(th3, &mqtt);
    std::cout<<6<<std::endl;
    while(true){
        mcp.scan_all_inputs();
    }
} 

