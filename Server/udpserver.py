import socket
import sys
import celery_wrapper
from socket import SOL_SOCKET, SO_REUSEADDR
global server_socket

def setup_socket(HOST, PORT):
    # Datagram (udp) socket
    try :
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        print 'Socket created'
    except socket.error, msg :
        print 'Failed to create socket. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
        sys.exit()
     
     
    # Bind socket to local host and port
    try:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
    except socket.error , msg:
        print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
        sys.exit()
         
    print 'Socket bind complete'
    return s

def send_to_host_by_lobby_id(lobby_id, msg):
    global server_socket
    
    #server_socket.sendto("bla bla bla", ("127.0.0.1", 8080))
    pass

def send_to_host_by_host_id(host_id, msg):
    pass

def send_to_lobby_by_lobby_id(lobby_id, msg):
    pass


def listen_blocking(HOST, PORT):
    global server_socket
    s = setup_socket(HOST, PORT)
    server_socket = s
    send_to_host_by_lobby_id(1, 2)
    try:
        #now keep talking with the client
        while True:
            # receive data from client (data, addr)
            d = s.recvfrom(1024)
            data = d[0]
            addr = d[1]
             
            if not data: 
                break
             
            reply = 'OK...' + data
             
            s.sendto(reply , addr)
            print 'Message[' + addr[0] + ':' + str(addr[1]) + '] - ' + data.strip()
    finally:
        s.close()

def listen_nonblocking(HOST, PORT):
    celery_wrapper.start_daemon_task(listen_blocking, HOST, PORT)