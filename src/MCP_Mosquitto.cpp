#include "MCP_Mosquitto.h"



void MCP_Mosquitto::mos_connect(){
    
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();

    mqtt_client iot_client(client_id, host, port);
    iot_client.register_mcp_manager(mcp_manager);
    iot_client.subscribe(NULL, "MCP_Array");  // Main device topic - Online 

    for(int i = 0; i<64; i++){
        std::string pub = "MCP_OUT_P_";
        std::string sub = "MCP_OUT_S_";
        sub += std::to_string(i);
        pub += std::to_string(i);
        iot_client.publish(NULL, pub.c_str());
        iot_client.subscribe(NULL, sub.c_str());
        usleep(10000);
    }
    std::string mcp_array ="MCP_Array";
    std::string mcp_array_msg ="Online";
    while(1)
    {
        rc = iot_client.loop();
       
    }
    mosqpp::lib_cleanup();
}

void MCP_Mosquitto::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}