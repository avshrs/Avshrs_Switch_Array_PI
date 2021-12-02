import socket
import time
import serial
from ctypes import *
import struct




def send_message(INSTRUCTIONS, CONFIG, VALUE, VALUE1, NAME="none"):
    TCP_IP = "192.168.1.169"
    TCP_PORT = 5656
    INSTRUCTIONS_= '{:08b}'.format(INSTRUCTIONS)
    CONFIG_ = '{:08b}'.format(CONFIG)
    VALUE_ = '{:08b}'.format(VALUE)
    VALUE1_ = '{:08b}'.format(VALUE1)
    NAME_ = ''.join('{0:08b}'.format(ord(x), 'b') for x in NAME)

    my_bytes = bytearray()
    my_bytes.append(int(INSTRUCTIONS_, 2))
    my_bytes.append(int(CONFIG_,2))
    my_bytes.append(int(VALUE_,2))
    my_bytes.append(int(VALUE1_,2))
    
    for i in NAME:
        my_bytes.append(int('{0:08b}'.format(ord(i), 'b'),2))
 
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((TCP_IP, TCP_PORT))
        s.send(my_bytes)


# for i in range(65):
#     time.sleep(0.1)
#     send_message(0, 1, i, i)
    
# for i in range(65):
#     time.sleep(0.1)
#     send_message(2, 1, i, 1)
    

# send_message(3, 1, 7, 1)  
send_message(0, 1, 2, 0)
send_message(0, 1, 0, 2)
send_message(0, 1, 1, 1)
send_message(1, 1, 0, 1)
send_message(1, 1, 2, 1)
send_message(2, 1, 0, 1)
send_message(2, 1, 2, 1)
send_message(4, 1, 2, 0,"Switch_Dzienny")  
send_message(4, 1, 1, 0,"Switch_Dzieciakow")  
send_message(4, 1, 0, 0,"Switch_Goscinny")  
send_message(5, 1, 0, 0,"Light_Dzienny")  
send_message(5, 1, 1, 0,"Light_Dzieciakow")  
send_message(5, 1, 2, 0,"Light_Goscinny")  
send_message(255, 1, 2, 1)
# send_message(4, 0, 7, 1)  
        
# # for i in range(64):
# #     send_message(1, 0, 0, i)
    
# # for i in range(64):
# #     send_message(3, 0, 0, i)    