#include "SatelIntegra.h"
#include "MCP_Mosquitto.h"
#include <thread>
#include <string>

char client_id[] = "Satel_Listener";
char host[] = "192.168.1.96";
int port = 1883;
mqtt_client mqtt_(client_id, host, port);

SatelIntegra sa(67, "192.168.1.240", 25197, "1234", 60);

unsigned int count[129] = {0};

void th1(){
    std::cout<< "read loop" << std::endl;
    sa.ReadLoop();
}

void chechViolation(){
    std::cout<< "chechViolation" << std::endl;
    int out = 0;
    while(true){
        out = 100-1;
        if(sa.out_state[out] == true){
            std::cout<< "out_state violated 100" << std::endl;
            if(count[out] == 0){
                // salon
                std::cout<< "out_state violated 100 - counter == 0" << std::endl;
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_12", msg.length(), msg.c_str());
                count[out] = 15;
            }
            else{
                count[out]--;
            }
        }
        else{
            count[out] = 0;
        }
        out = 101-1;
        if(sa.out_state[out] == true){
            std::cout<< "out_state violated 101" << std::endl;
            if(count[out] == 0){
                std::cout<< "out_state violated 101 - counter == 0" << std::endl;
                // kuchnia
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_18", msg.length(), msg.c_str());
                count[out] = 15;
            }
            else{
                count[out]--;
            }

        }
        else{
            count[101] = 0;
        }
        out = 102-1;
        if(sa.out_state[out] == true){
            std::cout<< "out_state violated 102" << std::endl;
            if(count[out] == 0){
                std::cout<< "out_state violated 102 - counter == 0" << std::endl;
                // wiatrołap
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_11", msg.length(), msg.c_str());
                count[out] = 15;
            }
            else{
                count[out]--;
            }

        }
        else{
            count[out] = 0;
        }
        out = 103-1;
        if(sa.out_state[out] == true){
            std::cout<< "out_state violated 103" << std::endl;
            if(count[out] == 0){
                std::cout<< "out_state violated 103 - counter == 0" << std::endl;
                // garaz
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_022", msg.length(), msg.c_str());
                count[out] = 15;
            }
            else{
                count[out]--;
            }

        }
        else{
            count[out] = 0;
        }
        usleep(100000);
    }
}


int main(){ 
    std::thread t1(th1);
    usleep(100000);
    chechViolation();
}
