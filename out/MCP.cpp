
#include "MCP.h"
#include "vars.h"
#include <stdio.h>
#include <i2c/smbus.h>

void MCP_Manager::init_mcp_devices(){

}


void MCP_Manager::read_all_inputs(){
    for(int i=0; i<4 ; i++){
        inputs_buffer[i] = mcpc_in[i]->readAll();
    }
    for(int ii=0; ii<4 ; ii++){
        for(int i=0; i<16 ; i++){
            if ((inputs_buffer[ii] & (1 << i )) != (inputs_memory[ii] & (1 << i )) ) {
                if ((inputs_buffer[ii] & (1 << i )) > 0){
                    update_output(((ii*16)+i), 0xFF);
            }
                else if ((inputs_buffer[ii] & (1 << i )) < 1){
                    update_output(((ii * 16) + i), 0x00);
                }
            }
        }
    }
    for(int i=0; i<4 ; i++){
        inputs_memory[i] = inputs_buffer[i];
    }
}

void MCP_Manager::update_output(int output_nr, uint8_t value){
    if(value > 0)
        value = 0xff;
    else 
        value = 0x00;
    uint8_t mask = (1 << data.output);

    if(mcp_eeprom_->Get_Output_Config(output_nr, OUT_STATE)){
        if(mcp_eeprom_->Get_Output_Config(output_nr, OUT_TYPE)){
            if(value > 0 ){
                if ((outputs_state[data.chipset][data.side] & mask) > 0){
                    write_output(data, 0x00);
                }
                else{
                    write_output(data, (0xff & mask));
                }
            }
        }
        else{
            write_output(data, value);      
        }
    }
}




void MCP_Manager::write_output(MCP_Data data, uint8_t value){
    uint8_t mask = (1 << data.output);
             
    if((outputs_state[data.chipset][data.side] & mask) > (value & mask)){
        outputs_state[data.chipset][data.side] &= ~mask;
    }
    else {
        outputs_state[data.chipset][data.side] |= mask;
    }
    mcpc_out[data.chipset]->writeRaw(data.side, outputs_state[data.chipset][data.side]);
}

