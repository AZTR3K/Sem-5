import socket

HOST = "127.0.0.1"
PORT = 65433

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    filename_to_request = "sample.txt"
    s.sendall(filename_to_request.encode())

    data = s.recv(4096)

    with open("received_file.txt", "wb") as f:
        f.write(data)

    print(f"File '{ filename_to_request }' received and saved as 'received_file.txt'.")
