import socket

HOST = "127.0.0.1"
PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

id = int(input("Enter ID: "))
client_message = f"Hello I am client and my ID is {id}"
sock.sendall(client_message.encode())

response = sock.recv(1024).decode()
print(f"Server response: {response}")

sock.close()
