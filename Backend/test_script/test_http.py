import socket
import time
 
# define various data, including both valid and invalid data format 
vld_dt = \
    "POST / HTTP/1.1\r\n" \
    "Connection:Close\r\n" \
    "Content-Length:0\r\n" \
    "\r\n"

# http msg with wrong line break, 
ivld_dt_0 = \
    "POST / \r"

# reversed http attr order
ivld_dt_1 = \
    "/ POST  HTTP/1.1 \r\n"

# wrong content length
ivld_dt_2 = \
    "POST / HTTP/1.1\r\n" \
    "Content-Length:30\r\n" \
    "\r\n" \
    "Haha, got you!"
 
BUF_SIZE = 1024  
server_addr = ('localhost', 8080)  

def one_connection(dt):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
    client.connect(server_addr) 

    # send all data to server
    client.sendall(bytes(dt, 'utf-8'))  

    # get and display HTTP message from server
    resp = client.recv(BUF_SIZE)  
    print(resp.decode('utf-8').replace("\r", ""))

    # close TCP connection
    client.close()

if __name__ == "__main__":
    conn_n = 1
    interval_sec = 0 
    for i in range(conn_n):
      time.sleep(interval_sec)
      one_connection(vld_dt)



  


# remember to set a maximum num of http-msg len