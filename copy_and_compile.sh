scp -r /home/seba/Documents/RPI_Zero_mcp pi@192.168.1.21:/home/pi/ 
ssh pi@192.168.1.21 "cd /home/pi/RPI_Zero_mcp; g++ -lwiringPi -I. -L. main.cpp MCPdev.cpp && ./a.out"