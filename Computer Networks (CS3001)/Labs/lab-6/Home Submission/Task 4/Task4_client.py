import socket

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

print("Connected to the guessing game server")

server_message = ""

while "Correct!" not in server_message:
    guess = input("Enter your guess (1-100): ")
    sock.sendall(guess.encode())

    server_message = sock.recv(1024).decode()

    print(f"Server response: {server_message}")

sock.close()
