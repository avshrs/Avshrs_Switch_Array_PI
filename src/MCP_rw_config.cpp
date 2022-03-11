#include "MCP_rw_config.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <algorithm>

void MCP_rw_config::read_config(){
    YAML::Node config = YAML::LoadFile("config.yaml");
    max_out = config["output_len"].as<int>();
    max_in = config["input_len"].as<int>();
    std::cout << "outputs settings loading" << std::endl;
    const YAML::Node& outputs_ = config["outputs"];
    for (YAML::const_iterator it = outputs_.begin(); it != outputs_.end(); ++it) {
        Output_conf oc_tmp; 

        oc_tmp.nr = it->second["nr"].as<int>(); 
        oc_tmp.name = it->second["name"].as<std::string>(); 
        oc_tmp.type = it->second["type"].as<std::string>(); 
        oc_tmp.default_state = static_cast<bool>(it->second["defaultState"].as<int>()); 
        oc_tmp.enabled = static_cast<bool>(it->second["enabled"].as<int>()); 
        oc_tmp.bistable = static_cast<bool>(it->second["bistable"].as<int>()); 
        oc_tmp.input_related = static_cast<bool>(it->second["inputRelated"].as<int>()); 
        
        output_conf_.push_back(oc_tmp);
    }
    std::cout << "outputs settings loaded" << std::endl;
    std::cout << "inputs settings loading" << std::endl;
    const YAML::Node& inputs_ = config["inputs"];
    for (YAML::const_iterator it = inputs_.begin(); it != inputs_.end(); ++it) {
        Input_conf oc_tmp; 

        oc_tmp.nr = it->second["nr"].as<int>(); 
        oc_tmp.name = it->second["name"].as<std::string>(); 
        oc_tmp.type = it->second["type"].as<std::string>(); 
        oc_tmp.enabled = static_cast<bool>(it->second["enabled"].as<int>()); 
        oc_tmp.enabledOutputRelated = static_cast<bool>(it->second["enabledOutputRelated"].as<int>()); 
        oc_tmp.output_related = it->second["outputRelated"].as<int>(); 
        
        input_conf_.push_back(oc_tmp);
    }
    std::cout << "inputs settings loaded" << std::endl;
    
    
    std::cout << "Mqtt settings loading" << std::endl;
    mqtt_config.ClientId = config["mqtt"]["ClientId"].as<std::string>();
    mqtt_config.ServerIp = config["mqtt"]["ServerIp"].as<std::string>();
    mqtt_config.username = config["mqtt"]["username"].as<std::string>();
    mqtt_config.password = config["mqtt"]["password"].as<std::string>();
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

    i2c1_config.out1Address = config["i2c1"]["out1Address"].as<int>();
    i2c1_config.out1Path = config["i2c1"]["out1Path"].as<std::string>();
    i2c1_config.out1enable = static_cast<bool>(config["i2c1"]["out1enable"].as<int>());

    i2c1_config.out2Address = config["i2c1"]["out2Address"].as<int>();
    i2c1_config.out2Path = config["i2c1"]["out2Path"].as<std::string>();
    i2c1_config.out2enable = static_cast<bool>(config["i2c1"]["out2enable"].as<int>());

    i2c1_config.out3Address = config["i2c1"]["out3Address"].as<int>();
    i2c1_config.out3Path = config["i2c1"]["out3Path"].as<std::string>();
    i2c1_config.out3enable = static_cast<bool>(config["i2c1"]["out3enable"].as<int>());

    i2c1_config.out4Address = config["i2c1"]["out4Address"].as<int>();
    i2c1_config.out4Path = config["i2c1"]["out4Path"].as<std::string>();
    i2c1_config.out4enable = static_cast<bool>(config["i2c1"]["out4enable"].as<int>());

    i2c1_config.out5Address = config["i2c1"]["out5Address"].as<int>();
    i2c1_config.out5Path = config["i2c1"]["out5Path"].as<std::string>();
    i2c1_config.out5enable = static_cast<bool>(config["i2c1"]["out5enable"].as<int>());

    i2c1_config.out6Address = config["i2c1"]["out6Address"].as<int>();
    i2c1_config.out6Path = config["i2c1"]["out6Path"].as<std::string>();
    i2c1_config.out6enable = static_cast<bool>(config["i2c1"]["out6enable"].as<int>());

    i2c1_config.out7Address = config["i2c1"]["out7Address"].as<int>();
    i2c1_config.out7Path = config["i2c1"]["out7Path"].as<std::string>();
    i2c1_config.out7enable = static_cast<bool>(config["i2c1"]["out7enable"].as<int>());

    i2c1_config.out8Address = config["i2c1"]["out8Address"].as<int>();
    i2c1_config.out8Path = config["i2c1"]["out8Path"].as<std::string>();
    i2c1_config.out8enable = static_cast<bool>(config["i2c1"]["out8enable"].as<int>());

    i2c1_config.in1Address = config["i2c1"]["in1Address"].as<int>();
    i2c1_config.in1Path = config["i2c1"]["in1Path"].as<std::string>();
    i2c1_config.in1enable = static_cast<bool>(config["i2c1"]["in1enable"].as<int>());

    i2c1_config.in2Address = config["i2c1"]["in2Address"].as<int>();
    i2c1_config.in2Path = config["i2c1"]["in2Path"].as<std::string>();
    i2c1_config.in2enable = static_cast<bool>(config["i2c1"]["in2enable"].as<int>());

    i2c1_config.in3Address = config["i2c1"]["in3Address"].as<int>();
    i2c1_config.in3Path = config["i2c1"]["in3Path"].as<std::string>();
    i2c1_config.in3enable = static_cast<bool>(config["i2c1"]["in3enable"].as<int>());

    i2c1_config.in4Address = config["i2c1"]["in4Address"].as<int>();
    i2c1_config.in4Path = config["i2c1"]["in4Path"].as<std::string>();
    i2c1_config.in4enable = static_cast<bool>(config["i2c1"]["in4enable"].as<int>());
    std::cout << "I2C settings loaded" << std::endl;
}
    
std::string MCP_rw_config::get_out_name(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.name;
        }
    }
    return "";
}

std::string MCP_rw_config::get_out_type(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.type;
        }
    }
    return "";
}

bool MCP_rw_config::get_out_def_state(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.default_state;
        }
    }
    return 0;
}

bool MCP_rw_config::get_out_enabled(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.enabled;
        }
    }
    return 0;
}
bool MCP_rw_config::get_out_bistable(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.bistable;
        }
    }
    return 0;    
}

bool MCP_rw_config::get_out_input_rel(int out){
    for (auto i : output_conf_){
        if( i.nr == out){
            return i.input_related;
        }
    }
    return 0;    
}


std::string MCP_rw_config::get_in_name(int in){
    for (auto i : input_conf_){
        if( i.nr == in){
            return i.name;
        }
    }
    return "";
}    

std::string MCP_rw_config::get_in_type(int in){
    for (auto i : input_conf_){
        if( i.nr == in){
            return i.type;
        }
    }
    return "";
}

bool MCP_rw_config::get_in_enabled(int in){
    for (auto i : input_conf_){
        if( i.nr == in){
            return i.enabled;
        }
    }
    return 0;
}
bool MCP_rw_config::get_in_enabledOutputRelated(int in){
    for (auto i : input_conf_){
        if( i.nr == in){
            return i.enabledOutputRelated;
        }
    }
    return 0;    
}

int MCP_rw_config::get_in_output_related(int in){
    for (auto i : input_conf_){
        if( i.nr == in){
            return i.output_related;
        }
    }
    return 0;    
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
std::string MCP_rw_config::get_mqtt_password(){
    return  mqtt_config.password;
}
std::string MCP_rw_config::get_mqtt_username(){
    return  mqtt_config.username;
}


uint8_t MCP_rw_config::get_out1Address()
{
    return  i2c1_config.out1Address;
}
std::string MCP_rw_config::get_out1Path()
{
    return  i2c1_config.out1Path;
}
bool MCP_rw_config::get_out1enable()
{
    return  i2c1_config.out1enable;

}
uint8_t MCP_rw_config::get_out2Address()
{
    return  i2c1_config.out2Address;

}
std::string MCP_rw_config::get_out2Path()
{
    return  i2c1_config.out2Path;

}
bool MCP_rw_config::get_out2enable()
{
    return  i2c1_config.out2enable;

}
uint8_t MCP_rw_config::get_out3Address()
{
    return  i2c1_config.out3Address;

}
std::string MCP_rw_config::get_out3Path()
{
    return  i2c1_config.out3Path;

}
bool MCP_rw_config::get_out3enable()
{
    return  i2c1_config.out3enable;

}
uint8_t MCP_rw_config::get_out4Address()
{
    return  i2c1_config.out4Address;

}
std::string MCP_rw_config::get_out4Path()
{
    return  i2c1_config.out4Path;

}
bool MCP_rw_config::get_out4enable()
{
    return  i2c1_config.out4enable;

}
uint8_t MCP_rw_config::get_out5Address()
{
    return  i2c1_config.out5Address;

}
std::string MCP_rw_config::get_out5Path()
{
    return  i2c1_config.out5Path;

}
bool MCP_rw_config::get_out5enable()
{
    return  i2c1_config.out5enable;

}
uint8_t MCP_rw_config::get_out6Address()
{
    return  i2c1_config.out6Address;

}
std::string MCP_rw_config::get_out6Path()
{
    return  i2c1_config.out6Path;

}
bool MCP_rw_config::get_out6enable()
{
    return  i2c1_config.out6enable;

}
uint8_t MCP_rw_config::get_out7Address()
{
    return  i2c1_config.out7Address;

}
std::string MCP_rw_config::get_out7Path()
{
    return  i2c1_config.out7Path;

}
bool MCP_rw_config::get_out7enable()
{
    return  i2c1_config.out7enable;

}
uint8_t MCP_rw_config::get_out8Address()
{
    return  i2c1_config.out8Address;

}
std::string MCP_rw_config::get_out8Path()
{
    return  i2c1_config.out8Path;

}
bool MCP_rw_config::get_out8enable()
{
    return  i2c1_config.out8enable;

}
uint8_t MCP_rw_config::get_in1Address()
{
    return  i2c1_config.in1Address;

}
std::string MCP_rw_config::get_in1Path()
{
    return  i2c1_config.in1Path;

}
bool MCP_rw_config::get_in1enable()
{
    return  i2c1_config.in1enable;

}
uint8_t MCP_rw_config::get_in2Address()
{
    return  i2c1_config.in2Address;

}
std::string MCP_rw_config::get_in2Path()
{
    return  i2c1_config.in2Path;

}
bool MCP_rw_config::get_in2enable()
{
    return  i2c1_config.in2enable;

}
uint8_t MCP_rw_config::get_in3Address()
{
    return  i2c1_config.in3Address;

}
std::string MCP_rw_config::get_in3Path()
{
    return  i2c1_config.in3Path;

}
bool MCP_rw_config::get_in3enable()
{
    return  i2c1_config.in3enable;

}
uint8_t MCP_rw_config::get_in4Address()
{
    return  i2c1_config.in4Address;

}
std::string MCP_rw_config::get_in4Path()
{
    return  i2c1_config.in4Path;

}
bool MCP_rw_config::get_in4enable()
{
    return  i2c1_config.in4enable;

}