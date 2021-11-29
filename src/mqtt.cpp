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
        
    #endif
    try{
        std::string message_topic(message->topic);
        std::string message_payload(static_cast<char*>(message->payload),MAX_PAYLOAD * sizeof(char));
        
        if(!message_payload.empty() & message_topic.find("MCP_Array") != std::string::npos){
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
        else if(!message_payload.empty() & message_topic.find("MCP_OUT_S_") != std::string::npos){
            #ifdef DEBUG
                std::cout << buf << std::endl;
            #endif
            if(message_payload.find("STATE") != std::string::npos){
            std::string nr_str;
                if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
                    nr_str = message_topic.substr(message_topic.length() - 2);
                }
                else{
                    nr_str = message_topic.substr(message_topic.length() - 1);
                }
                int nr = std::stoi(nr_str);
                std::string pub = "MCP_OUT_P_";
                std::string msg;
                pub += nr_str;

                if (mcp_manager->read_output(nr))
                    msg = "ON";
                else
                    msg = "OFF";
                std::cout << pub << " " <<msg<<std::endl;
                snprintf(buf, payload_size, msg.c_str());
                publish(NULL, pub.c_str(), strlen(buf), buf);
                #ifdef DEBUG
                    std::cout << "Request for output state" << std::endl;
                #endif
                    
            }
            else if(message_payload.find("ON") != std::string::npos){
                std::string nr_str;
                if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
                    nr_str = message_topic.substr(message_topic.length() - 2);
                }
                else{
                    nr_str = message_topic.substr(message_topic.length() - 1);
                }
                std::cout << nr_str<<std::endl;
                int nr = std::stoi(nr_str);
                std::string pub = "MCP_OUT_P_";
                std::string msg = "ON";
                pub += nr_str;
                std::cout << pub << " " <<msg<<std::endl;
                snprintf(buf, payload_size, msg.c_str());
                publish(NULL, pub.c_str(), strlen(buf), buf);
                mcp_manager->write_output(nr, true);
                #ifdef DEBUG
                    std::cout << "Request to turn on." << std::endl;
                #endif
                }
        

            else if(message_payload.find("OFF") != std::string::npos){
                std::string nr_str;
                if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
                    nr_str = message_topic.substr(message_topic.length() - 2);
                }
                else{
                    nr_str = message_topic.substr(message_topic.length() - 1);
                }
                int nr = std::stoi(nr_str);
                std::string pub = "MCP_OUT_P_";
                std::string msg = "OFF";
                pub += nr_str;
                std::cout << pub << " " <<msg<<std::endl;
                snprintf(buf, payload_size, msg.c_str());
                publish(NULL, pub.c_str(), strlen(buf), buf);
                mcp_manager->write_output(nr, false);
                #ifdef DEBUG
                    std::cout << "Request to turn off." << std:: endl;
                #endif
            }
        }
    }
    catch(...){}
}
