#include "MCP_Mosquitto.h"



void MCP_Mosquitto::mos_connect(){
    mqtt_client *iot_client;
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();


    iot_client = new mqtt_client(client_id, host, port);
    iot_client->subscribe(NULL, "switch");
    
    
    while(1)
    {
        rc = iot_client->loop();
                
    }

    mosqpp::lib_cleanup();

    
}