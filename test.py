import socket
import time
import serial
from ctypes import *
import struct




def send_message(INSTRUCTIONS, CONFIG, VALUE, VALUE1):
    TCP_IP = "192.168.1.21"
    TCP_PORT = 5656
    INSTRUCTIONS_ = '{:08b}'.format(INSTRUCTIONS)
    CONFIG_ = '{:08b}'.format(CONFIG)
    VALUE_ = '{:08b}'.format(VALUE)
    VALUE1_ = '{:08b}'.format(VALUE1)

    frame = int(INSTRUCTIONS_+CONFIG_+VALUE_+VALUE1_, 2)
    frame_be = struct.pack('>I', frame)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((TCP_IP, TCP_PORT))
        s.send(frame_be)
        
        
        
for i in range(64):
    send_message(0, 1, i, i)
    
for i in range(64):
    send_message(2, 1, i, i)
    
# for i in range(64):
#     send_message(1, 0, 0, i)
    
# for i in range(64):
#     send_message(3, 0, 0, i)    