#include "MCP_Mosquitto.h"



void MCP_Mosquitto::mos_connect(){
    mqtt_client *iot_client;
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();


    iot_client = new mqtt_client(client_id, host, port);
    iot_client->register_mcp_manager(mcp_manager);
    iot_client->subscribe(NULL, "MCP_Array");  // Main device topic - Online 
    //iot_client->publish(NULL, "MCP_Array");  // Main device topic - Online 

    for(int i = 0; i<64; i++){
        char pub[13];
        char sub[13];
        std::sprintf(sub, "MCP_OUT_S_%d", i);
        std::sprintf(pub, "MCP_OUT_P_%d", i);
        iot_client->publish(NULL, pub);
        iot_client->subscribe(NULL, sub);
        usleep(10000);
    }
    while(1)
    {
        rc = iot_client->loop();

    }

    mosqpp::lib_cleanup();

    
}

void MCP_Mosquitto::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}