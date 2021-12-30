#pragma once

#include "MCPdev.h"
#include "vars.h"
#include "MCP_Settings.h"
#include <cmath>       
class MCP_Manager
{
    
    private:
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
        MCP_Data mcp_data;

        bool in_states[IN_RANGE] = {true};
        bool out_states_real[OUT_RANGE] = {false};
        bool out_states[OUT_RANGE] = {false};
        bool alarm_armed = false;
        bool out_states_forced[OUT_RANGE] = {false};
        
    public:
        void MCP_Init();
        void register_mcp_settings(MCP_Settings *mcp_settings_);
        bool read_input_direct(uint8_t input);
        void write_output_direct(uint8_t output, bool state);
        bool read_output_buffer(uint8_t output);
        bool read_input_buffer(uint8_t input);
        void scan_all_inputs();
        void write_output(int output, bool value, int input);
        void write_output_timer(int output, unsigned int timeout);
    
    private:
        MCP_Data get_address(uint8_t io);
        void change_state(int output, unsigned int timeout);
};

