import socket
import random

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(5)

counter = 0
number = random.randint(0, 100)
guess = -1

conn, addr = sock.accept()
print("Client connected")

while guess != number:
    data = conn.recv(1024)
    if not data:
        break

    guess = int(data.decode())
    counter += 1

    server_message = ""

    if guess == number:
        server_message = f"Correct! You guessed the number in {counter} tries."
    elif guess < number:
        server_message = "Higher"
    else:
        server_message = "Lower"

    print(server_message)
    conn.sendall(server_message.encode())

conn.close()
