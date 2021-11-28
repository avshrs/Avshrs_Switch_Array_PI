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
void mqtt_client::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];
    if(!strcmp(message->topic, "MCP_Array"))
    {
        memset(buf, 0, payload_size * sizeof(char));

        /* Copy N-1 bytes to ensure always 0 terminated. */
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));

        #ifdef DEBUG
            std::cout << buf << std::endl;
        #endif

        // Examples of messages for M2M communications...
        
        if (!strcmp(buf, "STATUS"))
        {   
            snprintf(buf, payload_size, "ONLINE");
            publish(NULL, "MCP_Array", strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Status Request Recieved." << std::endl;
            #endif
        }
        
        else if (strstr(buf, "ON"))
        {   try{
                std::string str_nr;
                str_nr.push_back(buf[0]);
                str_nr.push_back(buf[1]);
                int nr = std::stoi( str_nr );
                snprintf(buf, payload_size, "Turning on...");
                publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
                mcp_manager->write_output(nr, true);
                #ifdef DEBUG
                    std::cout << "Request to turn on." << std::endl;
                #endif
            }
            catch(...) {
                std::cout << "wrong mesage" << std::endl;
            }
        }
        else if (strstr(buf, "STATE"))
        {   try{
                std::string str_nr;
                str_nr.push_back(buf[0]);
                str_nr.push_back(buf[1]);
                int nr = std::stoi( str_nr );
                bool value = mcp_manager->read_output(nr);
                if (value)
                snprintf(buf, payload_size, "ON");
                else 
                snprintf(buf, payload_size, "OFF");
                publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
                mcp_manager->write_output(nr, true);
                #ifdef DEBUG
                    std::cout << "Request to turn on." << std::endl;
                #endif
            }
            catch(...) {
                std::cout << "wrong mesage" << std::endl;
            }
        }

        else if (strstr(buf, "OFF"))
        {   
            try{
                std::string str_nr;
                str_nr.push_back(buf[0]);
                str_nr.push_back(buf[1]);
                std::cout << str_nr << std:: endl;
                int nr = std::stoi( str_nr);
                snprintf(buf, payload_size, "Turning off...");
                publish(NULL, PUBLISH_TOPIC, strlen(buf), buf);
                mcp_manager->write_output(nr, false);

                #ifdef DEBUG
                    std::cout << "Request to turn off." << std:: endl;
                #endif
            }
            catch(...) {
                std::cout << "wrong mesage" << std::endl;
            }            
        }
    }
}
