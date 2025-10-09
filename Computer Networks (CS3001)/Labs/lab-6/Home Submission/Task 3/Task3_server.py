import socket

HOST = "127.0.0.1"
PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((HOST, PORT))
sock.listen(5)

conn, addr = sock.accept()

while True:
    data = conn.recv(1024)
    if not data:
        break
    filename = data.decode()
    print(f"Received request for the file: {filename}")

    try:
        with open(filename, "r") as file:
            content = file.read()
        words = content.split()

        print(f"File contains {len(words)} words. Sending result.")
        word_len = str(len(words))
        conn.sendall(word_len.encode())
    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        word_count = str(-1).encode()
        conn.sendall(word_count)

conn.close()
