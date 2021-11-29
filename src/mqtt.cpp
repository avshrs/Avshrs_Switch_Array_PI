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

void mqtt_client::on_message(const struct mosquitto_message *message){
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

    #ifdef DEBUG
        std::cout << message->topic << std::endl;
    #endif
    std::string message_topic(message->topic);
    std::string message_payload(static_cast<char*>(message->payload),MAX_PAYLOAD * sizeof(char));
    
    if(message_topic.find("MCP_Array") != std::string::npos){
        #ifdef DEBUG
            std::cout << buf << std::endl;
        #endif
        if(message_payload.find("STATUS") != std::string::npos){
            snprintf(buf, payload_size, "Online");
            publish(NULL, "MCP_Array", strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Status Request Recieved." << std::endl;
            #endif
        }
    }
    else if(message_topic.find("MCP_OUT_S_") != std::string::npos){
        #ifdef DEBUG
            std::cout << buf << std::endl;
        #endif
        if(message_payload.find("_STATE") != std::string::npos){
            std::string str_nr;
            str_nr.push_back(buf[0]);
            str_nr.push_back(buf[1]);
            int nr = std::stoi( str_nr );
            char msg[7];
            char pub[13] = "MCP_OUT_P_";
            if (mcp_manager->read_output(nr))
                std::strcpy(msg, "00_ON");
            else
                std::strcpy(msg,"00_OFF");
                char comp[2] = "0" ;
            if (buf[0] == comp[0]){
                pub[10] = buf[1];
            }
            else {
                pub[10] = buf[0];
                pub[11] = buf[1];
            }
            msg[0] = buf[0];
            msg[1] = buf[1];

            
            snprintf(buf, payload_size, msg);
            publish(NULL, pub, strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Request for output state" << std::endl;
            #endif
                
        }
        else if(message_payload.find("_ON") != std::string::npos){
            std::string nr_str = message_payload.substr(0, 2);
            int nr = std::stoi(message_payload.substr(0, 2));
            std::string pub = "MCP_OUT_P_";
            std::string msg = "_ON";
            if (message_payload.substr(0, 1) == "0"){
                pub.push_back(nr_str[1]);
            }
            else {
                pub.push_back(nr_str[0]);
                pub.push_back(nr_str[1]);
            }
            msg.insert(0,nr_str);
           
            snprintf(buf, payload_size, msg.c_str());
            publish(NULL, pub.c_str(), strlen(buf), buf);
        
            mcp_manager->write_output(nr, true);
            #ifdef DEBUG
                std::cout << "Request to turn on." << std::endl;
            #endif
            }
    

        else if(message_payload.find("_OFF") != std::string::npos){
            std::string nr_str = message_payload.substr(0, 2);
            int nr = std::stoi(message_payload.substr(0, 2));
            std::string pub = "MCP_OUT_P_";
            std::string msg = "_OFF";
            if (message_payload.substr(0, 1) == "0"){
                pub.push_back(nr_str[1]);
            }
            else {
                pub.push_back(nr_str[0]);
                pub.push_back(nr_str[1]);
            }
            msg.insert(0,nr_str);
           
            snprintf(buf, payload_size, msg.c_str());
            publish(NULL, pub.c_str(), strlen(buf), buf);
        
            mcp_manager->write_output(nr, false);

            #ifdef DEBUG
                std::cout << "Request to turn off." << std:: endl;
            #endif
        }
    }
}
