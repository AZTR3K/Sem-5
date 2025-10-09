import socket

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST, PORT))

client_message = "the birds fly in dry sky at night"
sock.sendall(client_message.encode())

response = sock.recv(1024).decode()

words = response.split(" ")

for i, word in enumerate(words):
    if not any(v in word for v in "aeiou"):
        words[i] = "".join(reversed(word))

client_message = ""

for word in words:
    client_message += " " + word

print(f"Final string: {client_message}")

sock.close()
