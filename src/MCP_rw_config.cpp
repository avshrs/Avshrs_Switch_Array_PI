#include "MCP_rw_config.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>


void MCP_rw_config::read_config(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    if(config["config"].as<int>() == 1){
        for(int i = 0; i < max_out ;i++){
            std::string out_nr ="out";
            out_nr += std::to_string(i);
            output_conf[i].name = config["outputs"][out_nr]["name"].as<std::string>();
            output_conf[i].type = config["outputs"][out_nr]["type"].as<std::string>();
            output_conf[i].default_state = static_cast<bool>(config["outputs"][out_nr]["defaultState"].as<int>());
            output_conf[i].enabled = static_cast<bool>(config["outputs"][out_nr]["enabled"].as<int>());
            output_conf[i].bistable = static_cast<bool>(config["outputs"][out_nr]["bistable"].as<int>());
            output_conf[i].input_related = static_cast<bool>(config["outputs"][out_nr]["inputRelated"].as<int>());
        }
        for(int i = 0; i < max_in ;i++){
            std::string in_nr ="in";
            in_nr += std::to_string(i);
            input_conf[i].name = config["inputs"][in_nr]["name"].as<std::string>();
            input_conf[i].type = config["inputs"][in_nr]["type"].as<std::string>();
            input_conf[i].enabled = static_cast<bool>(config["inputs"][in_nr]["enabled"].as<int>());
            input_conf[i].output_related = config["inputs"][in_nr]["outputRelated"].as<int>();
        }
    }
    std::cout << "Mqtt settings loading" << std::endl;
    mqtt_config.ClientId = config["mqtt"]["ClientId"].as<std::string>();
    mqtt_config.ServerIp = config["mqtt"]["ServerIp"].as<std::string>();
    mqtt_config.serverPort = config["mqtt"]["serverPort"].as<int>();
    mqtt_config.keepAliveTopic = config["mqtt"]["keepAliveTopic"].as<std::string>();
    mqtt_config.keepAliveMsg = config["mqtt"]["keepAliveMsg"].as<std::string>();
    mqtt_config.outSubsring = config["mqtt"]["outSubsring"].as<std::string>();
    mqtt_config.outPubsring = config["mqtt"]["outPubsring"].as<std::string>();
    mqtt_config.outONMsg = config["mqtt"]["outONMsg"].as<std::string>();
    mqtt_config.outOFFMsg = config["mqtt"]["outOFFMsg"].as<std::string>();
    mqtt_config.utONTIMEMsg = config["mqtt"]["utONTIMEMsg"].as<std::string>();
    std::cout << "Mqtt settings loaded" << std::endl;
    std::cout << "I2C settings loading" << std::endl;
    i2c1_config.i2cPath = config["i2c1"]["i2cPath"].as<std::string>();
    i2c1_config.in1Address = config["i2c1"]["in1Address"].as<int>();
    i2c1_config.in2Address = config["i2c1"]["in2Address"].as<int>();
    i2c1_config.in3Address = config["i2c1"]["in3Address"].as<int>();
    i2c1_config.in4Address = config["i2c1"]["in4Address"].as<int>();
    i2c1_config.out1Address = config["i2c1"]["out1Address"].as<int>();
    i2c1_config.out2Address = config["i2c1"]["out2Address"].as<int>();
    i2c1_config.out3Address = config["i2c1"]["out3Address"].as<int>();
    i2c1_config.out4Address = config["i2c1"]["out4Address"].as<int>();
    std::cout << "I2C settings loaded" << std::endl;
}
    
std::string MCP_rw_config::get_out_name(int out){
    return output_conf[out].name;
}

std::string MCP_rw_config::get_out_type(int out){
    return output_conf[out].type;
}

bool MCP_rw_config::get_out_def_state(int out){
    return output_conf[out].default_state;
}

bool MCP_rw_config::get_out_enabled(int out){
    return output_conf[out].enabled;
}
bool MCP_rw_config::get_out_bistable(int out){
    return output_conf[out].bistable;
}

bool MCP_rw_config::get_out_input_rel(int out){
    return output_conf[out].input_related;
}


std::string MCP_rw_config::get_in_name(int in){
    if (in < 64 ){
        return input_conf[in].name;
    }
    else{
        std::string name = "MQTT";
        return name;
    }
}

std::string MCP_rw_config::get_in_type(int in){
    return input_conf[in].type;
}

bool MCP_rw_config::get_in_enabled(int in){
     return input_conf[in].enabled;
}


int MCP_rw_config::get_in_output_related(int in){
    return input_conf[in].output_related;
}

std::string MCP_rw_config::get_mqtt_ClientId(){
    return  mqtt_config.ClientId;
}
std::string MCP_rw_config::get_mqtt_ip(){
    return  mqtt_config.ServerIp;
}
int MCP_rw_config::get_mqtt_port(){
    return  mqtt_config.serverPort;
}
std::string MCP_rw_config::get_mqtt_keepAliveTopic(){
    return  mqtt_config.keepAliveTopic;
}
std::string MCP_rw_config::get_mqtt_keepAliveMsg(){
    return  mqtt_config.keepAliveMsg;
}
std::string MCP_rw_config::get_mqtt_outSubsring(){
    return  mqtt_config.outSubsring;
}
std::string MCP_rw_config::get_mqtt_outPubsring(){
    return  mqtt_config.outPubsring;
}
std::string MCP_rw_config::get_mqtt_outONMsg(){
    return  mqtt_config.outONMsg;
}
std::string MCP_rw_config::get_mqtt_outOFFMsg(){
    return  mqtt_config.outOFFMsg;
}
std::string MCP_rw_config::get_mqtt_outONTIMEMsg(){
    return  mqtt_config.utONTIMEMsg;
}