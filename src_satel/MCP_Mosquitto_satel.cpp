#include "MCP_Mosquitto.h"


#ifdef DEBUG
#include <iostream>

#endif

mqtt_client::mqtt_client(const char *id, const char *host, int port, MCP_Manager *mcp_manager_) : mosquittopp(id)
{
    mcp_manager = mcp_manager_;
    int keepalive = 60;
    connect(host, port, keepalive);
    
}
mqtt_client::mqtt_client(const char *id, const char *host, int port) : mosquittopp(id)
{
    int keepalive = 60;
    connect(host, port, keepalive);
    reconnect_delay_set(5, 1000000, true);
    
}

void mqtt_client::client_loop_forever(){
    if(mcp_manager != NULL){
        reconnect_delay_set(5, 1000000, true);
        loop_forever();
    }
    else{
        std::cout << "Wrong class constructor!!!" << std::endl;
    }
}


void mqtt_client::register_subs(){
    // subscribe(NULL, "MCP_Array");  // Main device topic - Online 

    // for(int i = 0; i<64; i++){
    //     std::string pub = "MCP_OUT_P_";
    //     std::string sub = "MCP_OUT_S_";
    //     sub += std::to_string(i);
    //     pub += std::to_string(i);
    //     publish(NULL, pub.c_str());
    //     subscribe(NULL, sub.c_str());
    //     usleep(10000);
    // }
}

void mqtt_client::unregister_subs(){
    // unsubscribe(NULL, "MCP_Array");  // Main device topic - Online 
    // for(int i = 0; i<64; i++){
    //     std::string pub = "MCP_OUT_P_";
    //     std::string sub = "MCP_OUT_S_";
    //     sub += std::to_string(i);
    //     pub += std::to_string(i);
        
    //     unsubscribe(NULL, sub.c_str());
    //     usleep(10000);
    // }
}

void mqtt_client::on_error() {
    std::cout<<"onerror"<<std::endl;
    return;
}


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

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{

    #ifdef DEBUG
        std::cout << "Subscription succeeded. " << " mid: " << mid << " qos_count: "<< qos_count << " qos_granted: "<< granted_qos << std::endl;
    #endif
}


void mqtt_client::register_mcp_manager(MCP_Manager *mcp_manager_){
    mcp_manager = mcp_manager_;
}

void mqtt_client::send_ack(std::string pub, std::string msg ){
    publish(NULL, pub.c_str(), msg.length(), msg.c_str());
}

void mqtt_client::on_message(const struct mosquitto_message *message){

//     try{
      std::string message_topic(message->topic);
      std::string message_payload(static_cast<char*>(message->payload));
//         if(!message_payload.empty() && message_topic == "MCP_Array"){

//             if(message_payload == "STATUS"){
//                 std::string msg = "Online";
//                 publish(NULL, "MCP_Array", msg.length(), msg.c_str());
//                 #ifdef DEBUG
//                     std::cout << "Status Request Recieved." << std::endl;
//                 #endif
//             }
//         }
//         else if(!message_payload.empty() && message_topic.find("MCP_OUT_S_") != std::string::npos){
//             if(message_payload == "STATE"){
//                 std::string nr_str;
//                 if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
//                     nr_str = message_topic.substr(message_topic.length() - 2);
//                 }
//                 else{
//                     nr_str = message_topic.substr(message_topic.length() - 1);
//                 }
//                 int nr = std::stoi(nr_str);
//                 std::string pub = "MCP_OUT_P_";
//                 std::string msg;
//                 pub += nr_str;

//                 if (mcp_manager->read_output_buffer(nr))
//                     msg = "ON";
//                 else
//                     msg = "OFF";
//                 publish(NULL, pub.c_str(), msg.length(), msg.c_str());
//                 #ifdef DEBUG
//                     std::cout << "Request for output state" << std::endl;
//                 #endif
                    
//             }
//             else if(message_payload == "ON"){
//                 std::string nr_str;
//                 if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
//                     nr_str = message_topic.substr(message_topic.length() - 2);
//                 }
//                 else{
//                     nr_str = message_topic.substr(message_topic.length() - 1);
//                 }
//                 int nr = std::stoi(nr_str);
//                 std::string pub = "MCP_OUT_P_";
//                 std::string msg = "ON";
//                 pub += nr_str;
//                 publish(NULL, pub.c_str(), msg.length(), msg.c_str());
//                 mcp_manager->write_output(nr, true, 999);
//                 #ifdef DEBUG
//                     std::cout << "Request to turn on output nr:" << nr<<std::endl;
//                 #endif
//             }
//             else if(message_payload == "ON_TIME"){
//                 std::string nr_str;
//                 if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
//                     nr_str = message_topic.substr(message_topic.length() - 2);
//                 }
//                 else{
//                     nr_str = message_topic.substr(message_topic.length() - 1);
//                 }
//                 int nr = std::stoi(nr_str);
//                 std::string pub = "MCP_OUT_P_";
//                 std::string msg = "ON";
//                 pub += nr_str;
//                 publish(NULL, pub.c_str(), msg.length(), msg.c_str());
//                 mcp_manager->write_output_timer(nr, 60);
//                 #ifdef DEBUG
//                     std::cout << "Request to turn on output nr:" << nr << "by PIR to 60 seconds" << std::endl;
//                 #endif
//             }

//             else if(message_payload == "OFF"){
//                 std::string nr_str;
//                 if (message_topic.substr(message_topic.length() - 3, 1 ) == "_"){
//                     nr_str = message_topic.substr(message_topic.length() - 2);
//                 }
//                 else{
//                     nr_str = message_topic.substr(message_topic.length() - 1);
//                 }
//                 int nr = std::stoi(nr_str);
//                 std::string pub = "MCP_OUT_P_";
//                 std::string msg = "OFF";
//                 pub += nr_str;
//                 publish(NULL, pub.c_str(), msg.length(), msg.c_str());
//                 mcp_manager->write_output(nr, false, 999);
//                 #ifdef DEBUG
//                     std::cout << "Request to turn off output nr:" << nr<<std::endl;
//                 #endif
//             }
//         }
//     }
//     catch(...){std::cout << "Received Empty Payload" << std:: endl;}
}
