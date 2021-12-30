#include "SatelIntegra.h"
#include "MCP_Mosquitto.h"
#include <thread>

char client_id[] = "satel";
char host[] = "192.168.1.96";
int port = 1883;
mqtt_client mqtt_(client_id, host, port);


int main(){ 

SatelIntegra sa(67, "192.168.1.240", 25197, "1234", 60);

std::string msg = "ON_TIME";
mqtt_.publish(NULL, "MCP_OUT_S_0", msg.length(), msg.c_str());

// while(true){
// 	sa.ReadZonesStatesAll();
// 	sa.ReadOutputsStatesAll();
// 	sa.ReadArmStatesAll();
// 	sa.ReadAlarm();

//     usleep(100000);
// }

}
