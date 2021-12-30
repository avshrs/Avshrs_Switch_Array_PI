#include "MCP_Mosquitto_satel.h"


#ifdef DEBUG
#include <iostream>

#endif

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    int keepalive = 60;
    // connect(host, port, keepalive);
    connect_async(host, port, keepalive);
    reconnect_delay_set(5, 1000000, true);
    
}

void mqtt_client::on_error() {
    std::cout<<"onerror"<<std::endl;
    return;}


void mqtt_client::on_connect(int rc)
{
    if (!rc)
    {
        #ifdef DEBUG
            std::cout << "Connected with code " << rc << std::endl;
        #endif
    }
        else {
           std::cout << "Error Connected with code " << rc << std::endl;
        
    }
    
}

void mqtt_client::on_disconnect(int rc)
{
    if (!rc)
    {
        #ifdef DEBUG
            std::cout << "disconnected - code " << rc << std::endl;
        #endif
    }
}
