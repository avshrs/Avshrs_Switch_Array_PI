#include "SatelIntegra.h"

int main(){ 

SatelIntegra sa(67, "192.168.1.240", 25197, "1234", 60);


while(true){
	sa.ReadZonesStatesAll();
	sa.ReadOutputsStatesAll();
	sa.ReadArmStatesAll();
	sa.ReadAlarm();

    usleep(100000);
}
}
