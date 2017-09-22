from socket import *
from threading import Thread

HOST  = ''
PORT  = 2000
QUEUE = 5

server = socket(AF_INET, SOCK_STREAM)
server.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
server.bind((HOST, PORT))
server.listen(QUEUE)
print("listening...")

def serve_client(client, addr):
    client.send("+ok welcome, type your message:\n> ".encode())
    data = client.recv(80).decode()
    print(addr, data, end='')
    client.send("+ok bye!\n".encode())
    client.close()

while True:
    client, addr = server.accept()
    Thread(target=serve_client, args=(client, addr)).start()

server.close()

