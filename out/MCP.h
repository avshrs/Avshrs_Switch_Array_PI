#ifndef MCP_Output_h
#define MCP_Output_h
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP23017.h"

class MCP_Manager {
    public:
        MCP_eeprom *mcp_eeprom_;
        
        MCP mcpc_out_0;
        MCP mcpc_out_1;
        MCP mcpc_out_2;
        MCP mcpc_out_3;
        MCP *mcpc_out[4];

        MCP mcpc_in_0;
        MCP mcpc_in_1;
        MCP mcpc_in_2;
        MCP mcpc_in_3;
        MCP *mcpc_in[4];
        
        uint16_t inputs_memory[4]={0};
        uint16_t inputs_buffer[4]={0};
    
    uint8_t outputs_state[4][2];
    void init_mcp_devices();
    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void update_output(int outputm, uint8_t value);
    MCP_Data Get_Data_From_Output(int output_nr);
    void read_all_inputs();
    void write_output(MCP_Data data, uint8_t value);
};
#endif //MCP_Output_h
