#pragma once
#include "vars.h"
#include <iostream>
#include "MCP_Settings.h"

class SettingsServer{
    public:
        MCP_Settings *mcp_settings;
        void register_mcp_settings(MCP_Settings *mcp_settings_);
        void analyze_packet(SERIALMCPFRAME frame);

};
