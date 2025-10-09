import socket

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(5)

print(f"Server running on {HOST}:{PORT}")

while True:
    conn, addr = sock.accept()

    while True:
        data = conn.recv(1024)
        if not data:
            print(f"Client {addr} disconnected.")
            break
        print(f"Client message: {data.decode()}")

        words = data.decode().split(" ")

        for i, word in enumerate(words):
            if any(v in word for v in "aeiou"):
                words[i] = "".join(reversed(word))

        server_message = " ".join(words)

        print(f"Inverted string: {server_message}")
        conn.sendall(server_message.encode())

    conn.close()
