#pragma once
#include "vars.h"
#include <iostream>
#include "MCP_Settings.h"

class SettingsServer{
    private:
        MCP_Settings *mcp_settings;
    public:
        void register_mcp_settings(MCP_Settings *mcp_settings_);
        void analyze_packet(SERIALMCPFRAME frame);

};
