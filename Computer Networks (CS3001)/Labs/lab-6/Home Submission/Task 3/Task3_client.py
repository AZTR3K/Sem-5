import socket

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = (HOST, PORT)
sock.connect(server_address)

filename = input("Enter filename to count words in: ")
sock.sendall(filename.encode())

word_count = int(sock.recv(1024).decode())

print(f"The server reports: The file contains {word_count} words.")

sock.close()
