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


void mqtt_client::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}

void mqtt_client::on_message(const struct mosquitto_message *message){

    try{
        std::string message_topic(message->topic);
        std::string message_payload(static_cast<char*>(message->payload));
        if(!message_payload.empty() & message_topic == "MCP_Array"){

            if(message_payload == "STATUS"){
                std::string msg = "Online";
                publish(NULL, "MCP_Array", msg.length(), msg.c_str());
                #ifdef DEBUG
                    std::cout << "Status Request Recieved." << std::endl;
                #endif
            }
        }
        else if(!message_payload.empty() & message_topic.find("MCP_OUT_S_") != std::string::npos){
            if(message_payload == "STATE"){
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
                publish(NULL, pub.c_str(), msg.length(), msg.c_str());
                #ifdef DEBUG
                    std::cout << "Request for output state" << std::endl;
                #endif
                    
            }
            else if(message_payload == "ON"){
                std::string nr_str;
                if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
                    nr_str = message_topic.substr(message_topic.length() - 2);
                }
                else{
                    nr_str = message_topic.substr(message_topic.length() - 1);
                }
                int nr = std::stoi(nr_str);
                std::string pub = "MCP_OUT_P_";
                std::string msg = "ON";
                pub += nr_str;
                publish(NULL, pub.c_str(), msg.length(), msg.c_str());
                mcp_manager->write_output(nr, true);
                #ifdef DEBUG
                    std::cout << "Request to turn on." << std::endl;
                #endif
            }

            else if(message_payload == "OFF"){
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
                publish(NULL, pub.c_str(), msg.length(), msg.c_str());
                mcp_manager->write_output(nr, false);
                #ifdef DEBUG
                    std::cout << "Request to turn off." << std:: endl;
                #endif
            }
        }
    }
    catch(...){std::cout << "Received Empty Payload" << std:: endl;}
}
