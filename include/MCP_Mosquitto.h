#pragma once

#include <stdio.h>
#include "mqtt.h"
#include "MCP_Manager.h"

#define CLIENT_ID "SwitchMatrix"
#define BROKER_ADDRESS "192.168.1.96"
#define MQTT_PORT 1883;
#define MQTT_TOPIC "switch"

class MCP_Mosquitto{
    public:
        int rc;
        void mos_connect();
        MCP_Manager *mcp_manager;
        void register_mcp_manager(MCP_Manager *mcp_manager_);


};

