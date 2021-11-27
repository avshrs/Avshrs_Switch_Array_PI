#include "mqtt.h"
#define PUBLISH_TOPIC "MCP_Array_pub"


#ifdef DEBUG
#include <iostream>

#endif

mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host, port, keepalive);
}

mqtt_client::~mqtt_client()
{
}

void mqtt_client::on_connect(int rc)
{
    if (!rc)
    {
        #ifdef DEBUG
            std::cout << "Connected - code " << rc << std::endl;
        #endif
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    #ifdef DEBUG
        std::cout << "Subscription succeeded." << std::endl;
    #endif
}

std::string bufferToString(char* buffer, int bufflen)
{
    std::string ret(buffer, bufflen);

    return ret;
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];
    std::string message_topic = bufferToString(message->topic, sizeof(message->topic));

    if(message_topic.find(PUBLISH_TOPIC))
    {
        memset(buf, 0, payload_size * sizeof(char));
        std::string message_payload = bufferToString(buf, sizeof(buf)); 
        /* Copy N-1 bytes to ensure always 0 terminated. */
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));

        #ifdef DEBUG
            // std::cout << buf << std::endl;
            std::cout << message_topic << std::endl;
            std::cout << message_payload << std::endl;
        #endif

        // Examples of messages for M2M communications...
        if (!message_payload.find("STATUS"))
        {
            snprintf(buf, payload_size, "This is a Status Message...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Status Request Recieved." << std::endl;
            #endif
        }

        if (!message_payload.find("ON"))
        {
            snprintf(buf, payload_size, "Turning on...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Request to turn on." << std::endl;
            #endif
        }

        if (!message_payload.find("OFF"))
        {
            snprintf(buf, payload_size, "Turning off...");
            publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Request to turn off." << std:: endl;
            #endif
        }
    }
}
