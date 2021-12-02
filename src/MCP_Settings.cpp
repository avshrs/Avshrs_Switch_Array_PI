#include "MCP_Settings.h"


void MCP_Settings::set_io_relation(uint8_t in, uint8_t out){
    in_settings[in].related_output = out;
}

uint8_t MCP_Settings::get_io_relation(uint8_t in){
    return in_settings[in].related_output;
}

void MCP_Settings::set_in_alarm_armed(uint8_t in, bool flag){
    in_settings[in].in_alarm_armed = flag;
}

bool MCP_Settings::get_in_alarm_armed(uint8_t in){
    return in_settings[in].in_alarm_armed;
}

void MCP_Settings::set_in_status(uint8_t in, bool status){
    in_settings[in].in_enabled = status;
}

bool MCP_Settings::get_in_status(uint8_t out){
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
        std::cout <<"Read out settings: " << out_settings[i].out_enabled << " " << out_settings[i].out_bistable << " " << out_settings[i].out_disabled_by_alarm << std::endl;
    }
}

void MCP_Settings::save_in_settings(){
    std::ofstream file("in_settings.bin", std::ios::out | std::ios::binary);
    if (!file) { return; }
    for (int i = 0; i < 64; i++) {
        file.write(reinterpret_cast<char*>(&in_settings[i].related_output), sizeof(uint8_t));
        file.write(reinterpret_cast<char*>(&in_settings[i].in_alarm_armed), sizeof(bool));
    }
    file.close();
}

void MCP_Settings::read_in_settings(){
    std::ifstream file;
    file.open("in_settings.bin", std::ios::binary);
    for (int i = 0; i < 64; i++) {
        file.read(reinterpret_cast<char*>(&in_settings[i].related_output), sizeof(uint8_t));
        file.read(reinterpret_cast<char*>(&in_settings[i].in_alarm_armed), sizeof(bool));
        std::cout <<"Read in settings: " << unsigned(in_settings[i].related_output) << " " << in_settings[i].in_alarm_armed  << std::endl;
    }
}
