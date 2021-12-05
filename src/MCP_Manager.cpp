#include "MCP_Manager.h"
#include <string>

void MCP_Manager::MCP_Init(){
    std::string i2c_path = "/dev/i2c-1";
    std::string i2c_path2 = "/dev/i2c-4";
    mcpc_in_0.MCP_Init(i2c_path, MCP5_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_1.MCP_Init(i2c_path, MCP6_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_2.MCP_Init(i2c_path, MCP7_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_3.MCP_Init(i2c_path, MCP8_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    
    mcpc_in[0]= &mcpc_in_0;
    mcpc_in[1]= &mcpc_in_1;
    mcpc_in[2]= &mcpc_in_2;
    mcpc_in[3]= &mcpc_in_3;
    
    mcpc_out_0.MCP_Init(i2c_path2, MCP1_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_1.MCP_Init(i2c_path2, MCP2_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_2.MCP_Init(i2c_path2, MCP3_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);    
    mcpc_out_3.MCP_Init(i2c_path2, MCP4_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP); 
    
    mcpc_out[0] = &mcpc_out_0;
    mcpc_out[1] = &mcpc_out_1;
    mcpc_out[2] = &mcpc_out_2;
    mcpc_out[3] = &mcpc_out_3;
    
    uint8_t mcp_io[4][16];
    bool in = false;
    for(int i=0; i<IN_RANGE;i++){
        scan_in_and_set_out(i);
    }
}

void MCP_Manager::register_mcp_settings(MCP_Settings *mcp_settings_){
    mcp_settings = mcp_settings_;
}


bool MCP_Manager::read_input(uint8_t in)
{
    uint8_t mcp_module = (in-(in%16))/16 ;
    uint8_t mcp_gpio = in - (mcp_module*16);
    mcp_gpio =  std::abs(mcp_gpio - 15);

    return mcpc_in[mcp_module]->read_io(mcp_gpio);
}


bool MCP_Manager::read_output(uint8_t out)
{
    return out_states_real[out];
}   


void MCP_Manager::write_output(uint8_t out, bool state)
{
    uint8_t mcp_module = (out-(out%16))/16 ;
    uint8_t mcp_gpio = out - (mcp_module*16);
    mcp_gpio =  std::abs(mcp_gpio - 15);
    out_states_real[out] = state;
    
    mcpc_out[mcp_module]->write_io(mcp_gpio, state);
}

void MCP_Manager::scan_all_io(){
    for(int i = 0; i < IN_RANGE ; i++){
        scan_in_and_set_out(i);
        usleep(1000);
    }
}

void MCP_Manager::scan_in_and_set_out(int in){
    bool value = false; 
    uint8_t output = 255;

    if (mcp_settings->get_in_status(in)){
        value = read_input(in);
        if (in_states[in] != value){
            in_states[in] = value;
            output = mcp_settings->get_io_relation(in);

            if (mcp_settings->get_out_status(output)){
                if (!mcp_settings->get_out_bistable(output) && out_states[output] != value){
                    out_states[output] = value;
                    write_output(output, value);
                    std::cout<<"get_in_status:"<<unsigned(mcp_settings->get_in_status(in))<< " - ";
                    std::cout<<"read_input(in):"<<unsigned(read_input(in))<< " - value:"<<value<< " - ";
                    std::cout<<"get_io_relation:"<<unsigned(mcp_settings->get_io_relation(in))<< " - ";
                    std::cout<<"get_out_status:"<<unsigned(mcp_settings->get_out_status(output))<< " - ";
                    std::cout<<" - val:"<<unsigned(value)<<std::endl;
                    std::cout<<"MO -"<<mcp_settings->get_in_name(in)<<" in:"<<unsigned(in)<<" - "<<mcp_settings->get_out_name(output)<<" out:"<<unsigned(output)<<" - val:"<<unsigned(value)<<std::endl;
                }
                else {
                    if (out_states[output] > 0 && value > 0){
                        out_states[output] = false;
                        write_output(output, false);
                        std::cout<<"BI -"<<mcp_settings->get_in_name(in)<<" in:"<<unsigned(in)<<" - "<<mcp_settings->get_out_name(output)<<" out:"<<unsigned(output)<<" - val:"<<unsigned(false)<<std::endl;
                    }
                    else if (value > 0){
                        out_states[output] = true;
                        write_output(output, true);
                        std::cout<<"BI -"<<mcp_settings->get_in_name(in)<<" in:"<<unsigned(in)<<" - "<<mcp_settings->get_out_name(output)<<" out:"<<unsigned(output)<<" - val:"<<unsigned(true)<<std::endl;
                    }
                }
            }
        }
    }
}


