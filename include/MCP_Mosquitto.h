#pragma once

#include <mosquittopp.h>
#include <cstring>
#include <string>
#include <cstdio>

class MCP_Manager;

#define DEBUG

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client (const char *id, const char *host, int port, MCP_Manager *mcp_manager_);
    mqtt_client (const char *id, const char *host, int port);
    MCP_Manager *mcp_manager;
    void send_ack(std::string pub, std::string msg);
    void register_mcp_manager(MCP_Manager *mcp_manager_);
    void client_loop_forever();
    void register_subs();
    void unregister_subs();
    void on_connect(int rc);
    void on_error();
    void on_disconnect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
};
