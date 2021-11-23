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
    void* buffer = malloc(sizeof (in_settings));
    int fd = open("in_settings.dat", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if (fd < 0) {
        printf("Error opening file\n");
    }
    memcpy(buffer, &in_settings, sizeof (in_settings));
    write(fd, buffer, sizeof (in_settings));
    close(fd);
}

void MCP_Settings::read_settings(){
    int fd = open("in_settings.dat", O_RDONLY, S_IWUSR | S_IRUSR);
    if (fd < 0) {
        printf("Error opening file\n");
    }
    char bufferRead[sizeof(in_settings)];
    
    read(fd, bufferRead, sizeof(bufferRead));
    for(int i=0; i<64;i++){
        *in_settings = *reinterpret_cast<IN_SETTINGS*>(bufferRead);
    }
    close(fd);

}
