#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "MCPdev.h"
#include "vars.h"

int main(void){ 
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
    for(int i=0; i<4;i++){
        mcpc_out[i]->write_all(0xff);
    }
    while(true){
    

    for(int i=0; i<4;i++){
        for(int ii=0; ii<16;ii++){
            uint8_t data = 0;
            data = mcpc_in[i]->read_io(ii);
            if(data > 0){
                data=0x00;
                // printf("0");
            }
            else {
               // printf("1");
                data=0xFF;
            }
            if( data != mcp_io[i][ii]){
                mcp_io[i][ii]=data;
                mcpc_out[i]->write_io(ii, data);
            }
        }
       // printf("\n");
    }
    }
            
} 
