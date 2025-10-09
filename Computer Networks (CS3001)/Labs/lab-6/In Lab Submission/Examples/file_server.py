import socket

HOST = "127.0.0.1"
PORT = 65433

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"File Server listening on port: {PORT}...")
    conn, addr = s.accept()
    with conn:
        print("Connected by", addr)
        filename = conn.recv(1024).decode()
        print(f"Client requested filename: {filename}")

        try:
            with open(filename, "rb") as f:
                data = f.read()
                conn.sendall(data)
                print("File sent successfully.")
        except FileNotFoundError:
            error_message = f"File {filename} not found."
            conn.sendall(error_message.encode())
            print(error_message)
