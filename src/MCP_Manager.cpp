#include "MCP_Manager.h"


void MCP_Manager::MCP_Init(){
    mcpc_in_0.MCP_Init(MCP5_ADDR, 164, MCP_IN, MCP_PULLUP);
    mcpc_in_1.MCP_Init(MCP6_ADDR, 180, MCP_IN, MCP_PULLUP);
    mcpc_in_2.MCP_Init(MCP7_ADDR, 196, MCP_IN, MCP_PULLUP);
    mcpc_in_3.MCP_Init(MCP8_ADDR, 212, MCP_IN, MCP_PULLUP);
    
    mcpc_in[0]= &mcpc_in_0;
    mcpc_in[1]= &mcpc_in_1;
    mcpc_in[2]= &mcpc_in_2;
    mcpc_in[3]= &mcpc_in_3;
    
    mcpc_out_0.MCP_Init(MCP1_ADDR, 100, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_1.MCP_Init(MCP2_ADDR, 116, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_2.MCP_Init(MCP3_ADDR, 132, MCP_OUT, MCP_NOT_PULLUP);    
    mcpc_out_3.MCP_Init(MCP4_ADDR, 148, MCP_OUT, MCP_NOT_PULLUP); 
    
    mcpc_out[0] = &mcpc_out_0;
    mcpc_out[1] = &mcpc_out_1;
    mcpc_out[2] = &mcpc_out_2;
    mcpc_out[3] = &mcpc_out_3;
    uint8_t mcp_io[4][16];
    
    for(int i=0; i<64;i++){
        bool in = MCP_Manager::read_input(i);
        MCP_Manager::write_output(i, in);
        in_states[i] = in;
        out_states[i] = in;
    }
}

void MCP_Manager::register_mcp_settings(MCP_Settings *mcp_settings_){
    mcp_settings = mcp_settings_;
}

bool MCP_Manager::read_input(uint8_t in){
    uint8_t mcp_module = (in-(in%16))/16 ;
    uint8_t mcp_gpio = in - (mcp_module*16);
    mcp_gpio =  std::abs(mcp_gpio - 15);
    return mcpc_in[mcp_module]->read_io(mcp_gpio);

}
bool MCP_Manager::read_output(uint8_t out){
    return out_states_real[out];
}   

void MCP_Manager::write_output(uint8_t out, bool state){
    uint8_t mcp_module = (out-(out%16))/16 ;
    uint8_t mcp_gpio = out - (mcp_module*16);
    mcp_gpio =  std::abs(mcp_gpio - 15);
    out_states_real[out] = state;
    mcpc_out[mcp_module]->write_io(mcp_gpio, state);
}

void MCP_Manager::scan_io(){
    bool value = false; 
    uint8_t output = o;
    for(int i = 0; i < 64 ; i++){
        if (mcp_settings->get_in_status(i)){
            value = read_input(i);
            std::cout<<"read - "<<unsigned(i)<<" - "<<unsigned(value)<<std::endl;
            if (in_states[i] != value){
                in_states[i] = value;
                output = mcp_settings->get_io_relation(i);
                if(mcp_settings->get_out_status(output)){
                    if(mcp_settings->get_out_bistable(output)){
                        if (value > 0){
                            if(out_states[output] > 0){
                                out_states[output] = false;
                                write_output(output, false);
                                // std::cout<<"BI - "<<unsigned(i)<<" - "<<unsigned(output)<<" - "<<unsigned(false)<<std::endl;
                            }
                            else{
                                out_states[output] = true;
                                write_output(output, true);
                                // std::cout<<"BI - "<<unsigned(i)<<" - "<<unsigned(output)<<" - "<<unsigned(true)<<std::endl;
                            }
                        }
                    }
                    else if(out_states[output] != value){
                        out_states[output] = value;
                        write_output(output, value);
                        // std::cout<<"MO - "<<unsigned(i)<<" - "<<unsigned(output)<<" - "<<unsigned(value)<<std::endl;
                    }
                }
            }
        }
    }
}


