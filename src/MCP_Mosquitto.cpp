#include "MCP_Mosquitto.h"

void MCP_Mosquitto::mos_connect(){
    char client_id[] = "SwitchMatrix";
    char host[] = "192.168.1.96";
    int port = 1883;

    mosqpp::lib_init();

    mqtt_client iot_client(client_id, host, port);

    iot_client.reconnect_delay_set(10, 100, true);
    iot_client.register_mcp_manager(mcp_manager);
    
    rc = iot_client.loop_forever();
    
    std::cout<<"loop exited"<< std::endl;
    mosqpp::lib_cleanup();
}

void MCP_Mosquitto::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}

