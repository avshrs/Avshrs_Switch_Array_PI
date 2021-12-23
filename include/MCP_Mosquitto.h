#pragma once

#include <stdio.h>
#include "mqtt.h"
#include "MCP_Manager.h"


class MCP_Mosquitto{
    private:
        int rc;
        MCP_Manager *mcp_manager;
    public:        
        void mos_connect();
        void register_mcp_manager(MCP_Manager *mcp_manager_);
};

