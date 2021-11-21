#ifndef MCP_SETTINGS_H
#define MCP_SETTINGS_H

#include "vars.h"

class MCP_Settings {

    uint8_t io_relations[64];
    uint8_t out_status[64];
    uint8_t io_disable_by_alarm[64];
    bool io_bistable[64]; 
    uint8_t in_special_input[64]; // store input number
    void set_io_relation(uint8_t in, uint8_t out);
    uint8_t get_io_relation(uint8_t in);
    void set_out_rstatus(uint8_t out, bool status);
    void set_out_disable_sp1(uint8_t in, uint8_t out);
    void set_io_relation(uint8_t in, uint8_t out);
};


#endif // MCP_SETTINGS_H