import socket

HOST = '127.0.0.1'
PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind((HOST, PORT))

sock.listen(5)

print(f"Server running on {HOST}:{PORT}")

while True:
    print("Waiting for a client...")
    conn, addr = sock.accept()
    print(f"Connected by {addr}")

    while True:
        data = conn.recv(1024)
        if not data:
            print(f"Client {addr} disconnected.")
            break
        print(f"Client message: {data.decode()}")
        server_message = f"Hello I am server. Your received id is {
            data.decode()[-1]}"
        conn.sendall(server_message.encode())

    conn.close()
