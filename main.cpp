#include "MCP_Manager.h"
#include <iostream>
int main(void){ 
    MCP_Manager mcp;
    mcp.MCP_Init();

    while(true){
        mcp.scan_io();
    }
            
} 
