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
        mqtt->publish(NULL, mcp_rw_cfg.get_mqtt_keepAliveTopic().c_str(), msg.length(), msg.c_str());
        for(int i = 0; i < 64; i++){
            if(mcp_rw_cfg.get_out_enabled(i)){
                bool value = mcp.read_output_buffer(i);
                std::string msg; 
                std::string pu = mcp_rw_cfg.get_mqtt_outPubstring();
    
                if(value){
                    msg = mcp_rw_cfg.get_mqtt_ONMsg();
                }
                else{
                    msg = mcp_rw_cfg.get_mqtt_OFFMsg();
                }
                pu += std::to_string(i);
                mqtt->publish(NULL, pu.c_str(), msg.length(), msg.c_str());
                
                usleep(1000);
            }
        }
        for(int i = 0; i < 64; i++){
            if(mcp_rw_cfg.get_in_enabled(i)){
                bool value = mcp.read_input_buffer(i);
                std::string msg; 
                std::string pu = mcp_rw_cfg.get_mqtt_inPubstring();
                if(value){
                    msg = mcp_rw_cfg.get_mqtt_ONMsg();
                }
                else{
                    msg = mcp_rw_cfg.get_mqtt_OFFMsg();
                }
                pu += std::to_string(i);
                mqtt->publish(NULL, pu.c_str(), msg.length(), msg.c_str());
                usleep(1000);
            }
        }
        sleep(60); 
    }
}

void th2(mqtt_client *mqtt){
    mqtt->client_loop_forever();
}
void th3(mqtt_client *mqtt){
    keep_alive_message(mqtt);
}

int main(){ 
    std::cout<<"main started" << std::endl;
    mcp_rw_cfg.read_config();
    std::cout<<"read config started" << std::endl;
    std::cout<<"mcp init starting" << std::endl;
    mcp.MCP_Init();
    std::cout<<"mcp init started" << std::endl;
    
    
    mqtt_client mqtt(mcp_rw_cfg.get_mqtt_ClientId().c_str(), mcp_rw_cfg.get_mqtt_ip().c_str(), mcp_rw_cfg.get_mqtt_port(), mcp_rw_cfg.get_mqtt_username().c_str(), mcp_rw_cfg.get_mqtt_password().c_str());
    std::cout<<"mqtt client started" << std::endl;
    mqtt.register_mcp_manager(&mcp);
    mqtt.register_mcp_config(&mcp_rw_cfg);
    mcp.register_mcp_mqtt(&mqtt);
    mcp.register_mcp_config(&mcp_rw_cfg);
    mcp.update_io();
    std::thread t2(th2, &mqtt);
    std::thread t3(th3, &mqtt);
    while(true){
        mcp.scan_all_inputs();
    }
} 

