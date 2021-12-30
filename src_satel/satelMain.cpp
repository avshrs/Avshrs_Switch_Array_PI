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
    while(true){
        if(sa.out_state[100] == true){
            std::cout<< "out_state violated 100" << std::endl;
            if(count[100] == 0){
                // salon
                std::cout<< "out_state violated 100 - counter == 0" << std::endl;
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_12", msg.length(), msg.c_str());
                count[100] = 15;
            }
            else{
                count[100]--;
            }
        }
        else{
            count[100] = 0;
        }
        if(sa.out_state[101] == true){
            std::cout<< "out_state violated 101" << std::endl;
            if(count[101] == 0){
                std::cout<< "out_state violated 101 - counter == 0" << std::endl;
                // kuchnia
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_18", msg.length(), msg.c_str());
                count[101] = 15;
            }
            else{
                count[101]--;
            }

        }
        else{
            count[101] = 0;
        }
        if(sa.out_state[102] == true){
            std::cout<< "out_state violated 102" << std::endl;
            if(count[102] == 0){
                std::cout<< "out_state violated 102 - counter == 0" << std::endl;
                // wiatrołap
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_11", msg.length(), msg.c_str());
                count[102] = 15;
            }
            else{
                count[102]--;
            }

        }
        else{
            count[102] = 0;
        }

        if(sa.out_state[103] == true){
            std::cout<< "out_state violated 103" << std::endl;
            if(count[103] == 0){
                std::cout<< "out_state violated 103 - counter == 0" << std::endl;
                // garaz
                std::string msg = "ON_TIME";
                mqtt_.publish(NULL, "MCP_OUT_S_022", msg.length(), msg.c_str());
                count[103] = 15;
            }
            else{
                count[103]--;
            }

        }
        else{
            count[103] = 0;
        }
        usleep(100000);
    }
}


int main(){ 
    std::thread t1(th1);
    usleep(100000);
    chechViolation();
}
