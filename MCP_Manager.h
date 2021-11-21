#ifndef MCP_MANAGER_h
#define MCP_MANAGER_h

#include "MCPdev.h"
#include "vars.h"

class MCP_Manager {
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

};


#endif // MCP_MANAGER_h