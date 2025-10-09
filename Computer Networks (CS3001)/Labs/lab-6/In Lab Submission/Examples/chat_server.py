import socket

HOST = "127.0.0.1"
PORT = 65432
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Chat server started, waiting for connection on port {PORT}...")
    conn, addr = s.accept()
    with conn:
        print("Connected by", addr)
        while True:
            data = conn.recv(1024)
            if not data or data.decode().lower() == "quit":
                print("Client has left the chat.")
                break
            print(f"Client: {data.decode()}")

            message = input("Server: ")
            conn.sendall(message.encode())
            if message.lower() == "quit":
                break
