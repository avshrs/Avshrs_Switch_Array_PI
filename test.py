import socket
import time
import serial
from ctypes import *
import struct

def send_message(INSTRUCTIONS, CONFIG, VALUE, VALUE1, NAME="none"):
    TCP_IP = "192.168.1.168"
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


# for i in range(32):
#     time.sleep(0.1)
#     send_message(1, 1, i, 255)
    
# for i in range(32):
#     time.sleep(0.1)
#     send_message(2, 1, i, 255)
    

# send_message(0, 1, 10, 9)  
# send_message(3, 1, 9, 255)

send_message(4, 1, 0, 0,"Switch_Dzienny")  
send_message(5, 1, 0, 0,"Light_Dzienny")  

send_message(4, 1, 1, 0,"Switch_Dzieciakow")  
send_message(5, 1, 1, 0,"Light_Dzieciakow")  

send_message(4, 1, 2, 0,"Switch_Goscinny")  
send_message(5, 1, 2, 0,"Light_Goscinny")  

send_message(4, 1, 3, 0,"Switch_Sypialnia1")  
send_message(5, 1, 3, 0,"Light_Sypialnia1")  

send_message(4, 1, 4, 0,"Switch_Sypialnia2")  
send_message(5, 1, 4, 0,"Light_Sypialnia2")  

send_message(4, 1, 5, 0,"Switch_Garderoba")  
send_message(5, 1, 5, 0,"Light_Garderoba")  

send_message(4, 1, 6, 0,"Switch_Lazienka_pietro")  
send_message(5, 1, 6, 0,"Light_Lazienka_pietro")  

send_message(4, 1, 7, 0,"Switch_Strych")  
send_message(5, 1, 7, 0,"Light_Strych")  

send_message(4, 1, 8, 0,"Switch_Korytarz")  
send_message(5, 1, 8, 0,"Light_Korytarz")  

send_message(4, 1, 9, 0,"Switch_Schody_pietro")  
send_message(5, 1, 9, 0,"Light_Schody")  

send_message(4, 1, 10, 0,"Switch_Schody_parter")  
send_message(5, 1, 10, 0,"Light_null")  

send_message(4, 1, 11, 0,"Switch_Wiatrolap")  
send_message(5, 1, 11, 0,"Light_Wiatrolap")  

send_message(4, 1, 12, 0,"Switch_Salon_male_kom")  
send_message(5, 1, 12, 0,"Light_Salon_male_kom")  

send_message(4, 1, 13, 0,"Switch_Salon_male")  
send_message(5, 1, 13, 0,"Light_Salon_male")  

send_message(4, 1, 14, 0,"Switch_Salon_duze")  
send_message(5, 1, 14, 0,"Light_Salon_duze")  

send_message(4, 1, 15, 0,"Switch_Salon_wneka")  
send_message(5, 1, 15, 0,"Light_Salon_wneka")  

send_message(4, 1, 16, 0,"Switch_Lazienka_parter")  
send_message(5, 1, 16, 0,"Light_Lazienka_parter")  

send_message(4, 1, 17, 0,"Switch_Kuchnia_duze")  
send_message(5, 1, 17, 0,"Light_Kuchnia_duze")  

send_message(4, 1, 18, 0,"Switch_Kuchnia_szafki")  
send_message(5, 1, 18, 0,"Light_Kuchnia_szafki")  

send_message(4, 1, 19, 0,"Switch_Kuchnia_okap")  
send_message(5, 1, 19, 0,"Light_Kuchnia_okap")  

send_message(4, 1, 20, 0,"Switch_Spizarnia")  
send_message(5, 1, 20, 0,"Light_Spizarnia")  

send_message(4, 1, 21, 0,"Switch_Garaz_brama")  
send_message(5, 1, 21, 0,"Light_Garaz_brama")  

send_message(4, 1, 22, 0,"Switch_Garaz_lodowka")  
send_message(5, 1, 22, 0,"Light_Garaz_lodowka")  

send_message(4, 1, 23, 0,"Switch_Kotlownia")  
send_message(5, 1, 23, 0,"Light_kotlownia")  

send_message(4, 1, 24, 0,"Switch_Piwnica")  
send_message(5, 1, 24, 0,"Light_Piwnica")  

send_message(4, 1, 28, 0,"Czujnik_zmierzchu")  
send_message(4, 1, 29, 0,"Czujnik_zmierzchu")  

send_message(5, 1, 28, 0,"Light_Zew1_przod")  
send_message(5, 1, 29, 0,"Light_Zew1_tyl")  
send_message(5, 1, 30, 0,"Light_Zew2_przod")  
send_message(5, 1, 31, 0,"Light_Zew2_tyl")  

send_message(255, 1, 2, 1)
