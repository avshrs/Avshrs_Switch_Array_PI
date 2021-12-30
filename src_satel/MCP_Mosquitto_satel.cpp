#include "MCP_Mosquitto_satel.h"



#include <iostream>
#include <iomanip>
#include <ctime>

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    int keepalive = 60;
    // connect(host, port, keepalive);
    connect(host, port, keepalive);
}
void mqtt_client::client_loop_forever(){
        reconnect_delay_set(5, 1000000, true);
        loop_forever();
}

void mqtt_client::on_error() {
    std::cout<<"onerror"<<std::endl;
    return;}


void mqtt_client::on_connect(int rc)
{
    if (!rc)
    {
        #ifdef DEBUG
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);      
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
            std::cout << "Connected with code " << rc << std::endl;
        #endif
    }
        else {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);      
            std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S | ");
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
