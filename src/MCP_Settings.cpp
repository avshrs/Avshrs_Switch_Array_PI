#include "MCP_Settings.h"


void MCP_Settings::set_io_relation(uint8_t in, uint8_t out){
    in_settings[in].related_output = out;
}

uint8_t MCP_Settings::get_io_relation(uint8_t in){
    return in_settings[in].related_output;
}

void MCP_Settings::set_in_name(uint8_t in, std::string name){
    std::cout<<"set_in_name name value: " << name << std::endl;
    strcpy(in_settings[in].in_name, name.c_str());
}

std::string MCP_Settings::get_in_name(uint8_t in){
    return std::string(in_settings[in].in_name);
}

void MCP_Settings::set_out_name(uint8_t out, std::string name){
    strcpy(out_settings[out].out_name, name.c_str());
}

std::string MCP_Settings::get_out_name(uint8_t out){
    return std::string(out_settings[out].out_name);
}

void MCP_Settings::set_in_status(uint8_t in, bool status){
    in_settings[in].in_enabled = status;
}

bool MCP_Settings::get_in_status(uint8_t in){
    return in_settings[in].in_enabled;
}

void MCP_Settings::set_out_status(uint8_t out, bool status){
    out_settings[out].out_enabled = status;
}

bool MCP_Settings::get_out_status(uint8_t out){
    return out_settings[out].out_enabled;
}

void MCP_Settings::set_out_bistable(uint8_t out, bool status){
    out_settings[out].out_bistable = status;
}

bool MCP_Settings::get_out_bistable(uint8_t out){
    return out_settings[out].out_bistable;
}

void MCP_Settings::set_out_disable_by_alarm(uint8_t out, bool flag){
    out_settings[out].out_disabled_by_alarm = flag;
}

bool MCP_Settings::get_out_disable_by_alarm(uint8_t out){
    return out_settings[out].out_disabled_by_alarm;
}

void MCP_Settings::save_settings(){
    MCP_Settings::save_in_settings();
    MCP_Settings::save_out_settings();
}
void MCP_Settings::read_settings(){
    MCP_Settings::read_in_settings();
    MCP_Settings::read_out_settings();
}

void MCP_Settings::save_out_settings(){
    std::ofstream file("out_settings.bin", std::ios::out | std::ios::binary);
    if (!file) { return; }
    for (int i = 0; i < 64; i++) {
        
        file.write(reinterpret_cast<char*>(&out_settings[i].out_enabled), sizeof(bool));
        file.write(reinterpret_cast<char*>(&out_settings[i].out_bistable), sizeof(bool));
        file.write(reinterpret_cast<char*>(&out_settings[i].out_disabled_by_alarm), sizeof(bool));
        file.write(reinterpret_cast<char*>(&out_settings[i].out_name), sizeof(char)*30);
        std::cout <<"save in settings: in:"<< i <<" - "<< out_settings[i].out_name <<std::endl;
    }
    file.close();
}

void MCP_Settings::read_out_settings(){
    std::ifstream file;
    file.open("out_settings.bin", std::ios::binary);
    for (int i = 0; i < 64; i++) {
        file.read(reinterpret_cast<char*>(&out_settings[i].out_enabled), sizeof(bool));
        file.read(reinterpret_cast<char*>(&out_settings[i].out_bistable), sizeof(bool));
        file.read(reinterpret_cast<char*>(&out_settings[i].out_disabled_by_alarm), sizeof(bool));
        file.read(reinterpret_cast<char*>(&out_settings[i].out_name), sizeof(char)*30);

        std::cout <<"Read out settings: out"<< i << " enabled:" << out_settings[i].out_enabled << " bistable:" << out_settings[i].out_bistable << " dis_by_alarm" << out_settings[i].out_disabled_by_alarm<< " name:" << out_settings[i].out_name << std::endl;
        
    }
}

void MCP_Settings::save_in_settings(){
    std::ofstream file("in_settings.bin", std::ios::out | std::ios::binary);
    if (!file) { return; }
    for (int i = 0; i < 64; i++) {
        file.write(reinterpret_cast<char*>(&in_settings[i].related_output), sizeof(uint8_t));
        file.write(reinterpret_cast<char*>(&in_settings[i].in_enabled), sizeof(bool));
        file.write(reinterpret_cast<char*>(&in_settings[i].in_name), sizeof(char)*30);
    
       std::cout <<"save in settings: in:"<< i <<" - "<< in_settings[i].in_name <<std::endl;
    }
    file.close();
}

void MCP_Settings::read_in_settings(){
    std::ifstream file;
    file.open("in_settings.bin", std::ios::binary);
    for (int i = 0; i < 64; i++) {
        file.read(reinterpret_cast<char*>(&in_settings[i].related_output), sizeof(uint8_t));
        file.read(reinterpret_cast<char*>(&in_settings[i].in_enabled), sizeof(bool));
        file.read(reinterpret_cast<char*>(&in_settings[i].in_name), sizeof(char)*30);

        std::cout <<"Read in settings: in:"<< i << " out:"<<unsigned(in_settings[i].related_output) << " enabled:" << in_settings[i].in_enabled  << " - name:" << in_settings[i].in_name << std::endl;
    }
}
