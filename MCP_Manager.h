#ifndef MCP_MANAGER_h
#define MCP_MANAGER_h

#include "MCPdev.h"
#include "vars.h"
#include "MCP_Settings.h"
class MCP_Manager
{
    public:
        MCP *mcpc_in[4];
        MCP mcpc_in_0;
        MCP mcpc_in_1;
        MCP mcpc_in_2;
        MCP mcpc_in_3;

        MCP *mcpc_out[4];
        MCP mcpc_out_0;
        MCP mcpc_out_1;
        MCP mcpc_out_2;
        MCP mcpc_out_3;
        
        MCP_Settings *mcp_settings;
        
        
        bool in_states[64] = {false};
        bool out_states[64] = {false};
        bool alarm_armed = false;

        void MCP_Init();
        void register_mcp_settings(MCP_Settings *mcp_settings_);
        bool read_input(uint8_t in);
        void write_output(uint8_t out, bool state);
        void scan_io();
};

#endif // MCP_MANAGER_h