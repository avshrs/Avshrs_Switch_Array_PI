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
            output_conf[i]->name = config["outputs"][out_nr]["name"].as<std::string>();
            output_conf[i]->type = config["outputs"][out_nr]["type"].as<std::string>();
            output_conf[i]->default_state = config["outputs"][out_nr]["defaultState"].as<bool>();
            output_conf[i]->enabled = config["outputs"][out_nr]["enabled"].as<bool>();
            output_conf[i]->bistable = config["outputs"][out_nr]["bistable"].as<bool>();
            output_conf[i]->input_related = config["outputs"][out_nr]["inputRelated"].as<bool>();
        }
        for(int i = 0; i < max_in ;i++){
            std::string in_nr ="in";
            in_nr += std::to_string(i);
            input_conf[i]->name = config["inputs"][in_nr]["name"].as<std::string>();
            input_conf[i]->type = config["inputs"][in_nr]["type"].as<std::string>();
            input_conf[i]->enabled = config["inputs"][in_nr]["enabled"].as<bool>();
            input_conf[i]->outputRelated = config["inputs"][in_nr]["outputRelated"].as<int>();
        }
    }

    for(int i = 0; i<max_out; i++){
        std::cout << output_conf[i]->name << std::endl;
    }
}
    
std::string MCP_rw_config::get_out_name(unsigned int out){
    return output_conf[out]->name;
}

std::string MCP_rw_config::get_out_type(unsigned int out){
    return output_conf[out]->type;
}

bool MCP_rw_config::get_out_def_state(unsigned int out){
    return output_conf[out]->default_state;
}

bool MCP_rw_config::get_out_enabled(unsigned int out){
    return output_conf[out]->enabled;
}
bool MCP_rw_config::get_out_bistable(unsigned int out){
    return output_conf[out]->bistable;
}

bool MCP_rw_config::get_out_input_rel(unsigned int out){
    return output_conf[out]->input_related;
}


std::string MCP_rw_config::get_in_name(unsigned int in){
    return output_conf[in]->name;
}

std::string MCP_rw_config::get_in_type(unsigned int in){
    return output_conf[in]->type;
}

bool MCP_rw_config::get_out_enabled(unsigned int in){
     return output_conf[in]->enabled;
}


int MCP_rw_config::get_in_outputRelated(unsigned int in){
    return output_conf[in]->outputRelated;
}
