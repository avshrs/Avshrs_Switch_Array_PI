#ifndef MCP_SETTINGS_H
#define MCP_SETTINGS_H

#include "vars.h"

class MCP_Settings {

    uint8_t io_relations[64];
    uint8_t io_status[64];
    uint8_t io_disable_by_alarm[64];
    uint8_t io_bistable[64];

};


#endif // MCP_SETTINGS_H