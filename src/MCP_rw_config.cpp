#include "MCP_rw_config.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <algorithm>

void MCP_rw_config::read_config(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    // max_out = config["output_len"].as<int>();
    // max_in = config["input_len"].as<int>();
    
    const YAML::Node& outputs_ = config["outputs"];
    for (YAML::const_iterator it = outputs_.begin(); it != outputs_.end(); ++it) {
        const YAML::Node& out_ = *it;
        Output_conf oc_tmp; 

        oc_tmp.nr = it->second["nr"].as<int>(); 
        oc_tmp.name = it->second["name"].as<std::string>(); 
        oc_tmp.type = it->second["type"].as<std::string>(); 
        oc_tmp.default_state = static_cast<bool>(it->second["defaultState"].as<int>()); 
        oc_tmp.enabled = static_cast<bool>(it->second["enabled"].as<int>()); 
        oc_tmp.bistable = static_cast<bool>(it->second["bistable"].as<int>()); 
        oc_tmp.input_related = static_cast<bool>(it->second["input_related"].as<int>()); 
        
        output_conf_.push_back(oc_tmp);
    }

    const YAML::Node& inputs_ = config["inputs"];
    for (YAML::const_iterator it = inputs_.begin(); it != inputs_.end(); ++it) {
        const YAML::Node& out_ = *it;
        Input_conf oc_tmp; 

        oc_tmp.nr = it->second["nr"].as<int>(); 
        oc_tmp.name = it->second["name"].as<std::string>(); 
        oc_tmp.type = it->second["type"].as<std::string>(); 
        oc_tmp.enabled = static_cast<bool>(it->second["enabled"].as<int>()); 
        oc_tmp.output_related = it->second["outputRelated"].as<int>(); 
        
        intput_conf_.push_back(oc_tmp);
    }

    
    if(config["config"].as<int>() == 1){
        for(int i = 0; i < max_out ;i++){
            std::string out_nr ="out";
            out_nr += std::to_string(i);
            // output_conf[i].nr = config["outputs"][out_nr]["nr"].as<int>();
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
    mqtt_config.outSubstring = config["mqtt"]["outSubstring"].as<std::string>();
    mqtt_config.outPubstring = config["mqtt"]["outPubstring"].as<std::string>();
    mqtt_config.inSubstring = config["mqtt"]["inSubstring"].as<std::string>();
    mqtt_config.inPubstring = config["mqtt"]["inPubstring"].as<std::string>();
    mqtt_config.ONMsg = config["mqtt"]["ONMsg"].as<std::string>();
    mqtt_config.OFFMsg = config["mqtt"]["OFFMsg"].as<std::string>();
    mqtt_config.ONTIMEMsg = config["mqtt"]["ONTIMEMsg"].as<std::string>();
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
    for (auto i : v){
        if( i.nr == out){
            return i.name;
        }
        
    }
    return "";
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
    if (in < 64 ){
        return input_conf[in].type;
    }
    else{
        std::string name = "MQTT";
        return name;
    }
}

bool MCP_rw_config::get_in_enabled(int in){
     if (in < 64 ){
        return input_conf[in].enabled;
    }
    else{
        return false;
    }
}


int MCP_rw_config::get_in_output_related(int in){
    if (in < 64 ){
        return input_conf[in].output_related;
    }
    else{
        return 0;
    }
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
std::string MCP_rw_config::get_mqtt_outSubstring(){
    return  mqtt_config.outSubstring;
}
std::string MCP_rw_config::get_mqtt_outPubstring(){
    return  mqtt_config.outPubstring;
}
std::string MCP_rw_config::get_mqtt_inSubstring(){
    return  mqtt_config.inSubstring;
}
std::string MCP_rw_config::get_mqtt_inPubstring(){
    return  mqtt_config.inPubstring;
}
std::string MCP_rw_config::get_mqtt_ONMsg(){
    return  mqtt_config.ONMsg;
}
std::string MCP_rw_config::get_mqtt_OFFMsg(){
    return  mqtt_config.OFFMsg;
}
std::string MCP_rw_config::get_mqtt_ONTIMEMsg(){
    return  mqtt_config.ONTIMEMsg;
}