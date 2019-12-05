#-*- encoding:utf-8 -*-

import socket

ip_port=("127.0.0.1",5025)
server=socket.socket()
server.bind(ip_port)
server.listen(5)
print("waiting....")

while(True):
    conn,addr=server.accept()
    data=conn.recv(1024)
    print(data)
    while(True):
    
        if(str(data).lower().__contains__("idn")):
            print ("send IDN information")
            conn.sendall("KEYSIGHT\n TECHNOLOGIES,DSOS054A,MY55510151,06.30.01102\n")
        data=""
        data=conn.recv(1024)
    
    
    conn.close()
