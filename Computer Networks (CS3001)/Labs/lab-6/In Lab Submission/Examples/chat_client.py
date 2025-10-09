import socket

HOST = "127.0.0.1"
PORT = 65432
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print("Connected to chat server. Type 'quit' to exit.")
    while True:
        message = input("Client: ")
        s.sendall(message.encode())

        data = s.recv(1024)
        if not data or message.lower() == "quit":
            print("Connection closed.")
            break
        print(f"Server: {data.decode()}")
