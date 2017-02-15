from socket import *

HOST = "127.0.0.1"
PORT = 2000

server = socket(AF_INET, SOCK_STREAM)
server.connect((HOST, PORT))

resp = server.recv(80).decode()
print(resp, end='')

data = input() + '\n'
server.send(data.encode())

resp = server.recv(80).decode()
print(resp, end='')

server.close()
