#ifndef MCP_MOSQUITTO_H
#define MCP_MOSQUITTO_H

#include <stdio.h>
#include "mqtt.h"

#define CLIENT_ID "SwitchMatrix"
#define BROKER_ADDRESS "192.168.1.96"
#define MQTT_PORT 1883;
#define MQTT_TOPIC "switch"

class MCP_Mosquitto{
    public:
        int rc;
        void mos_connect();
  


};

#endif // MCP_SETTINGS_H


