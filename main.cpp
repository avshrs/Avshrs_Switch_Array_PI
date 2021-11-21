#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "MCPdev.h"
#include "vars.h"

int main(void){ 
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
