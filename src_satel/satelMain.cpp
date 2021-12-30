#include "SatelIntegra.h"
#include "MCP_Mosquitto.h"
#include <thread>
#include <string>

char client_id[] = "Satel_Listener";
char host[] = "192.168.1.96";
int port = 1883;
mqtt_client mqtt_(client_id, host, port);
SatelIntegra sa(67, "192.168.1.240", 25197, "1234", 60);

void th1(){
    sa.ReadLoop();
}
void chechViolation(){
    while(true){
        if(sa.out_state[100] == true){
            // salon
            std::string msg = "ON_TIME";
            mqtt_.publish(NULL, "MCP_OUT_S_12", msg.length(), msg.c_str());
        }
        if(sa.out_state[101] == true){
            // kuchnia
            std::string msg = "ON_TIME";
            mqtt_.publish(NULL, "MCP_OUT_S_18", msg.length(), msg.c_str());
        }
        if(sa.out_state[102] == true){
            // wiatrołap
            std::string msg = "ON_TIME";
            mqtt_.publish(NULL, "MCP_OUT_S_11", msg.length(), msg.c_str());
        }

        if(sa.out_state[103] == true){
            // garaz
            std::string msg = "ON_TIME";
            mqtt_.publish(NULL, "MCP_OUT_S_22", msg.length(), msg.c_str());
        }
        usleep(10000);
    }
}


int main(){ 
    std::thread t1(th1);
    std::thread t2(chechViolation);
}
