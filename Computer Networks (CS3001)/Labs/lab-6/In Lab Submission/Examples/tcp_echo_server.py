import socket
import struct


def recv_all(sock, n):
    """Helper function to receive n bytes or return None if EOF is hit"""
    data = bytearray()
    while len(data) < n:
        packet = sock.recv(n - len(data))
        if not packet:
            return None
        data.extend(packet)
    return data


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ("localhost", 10000)
print(f"Starting up on {server_address[0]} port{server_address[1]}")
sock.bind(server_address)
sock.listen(1)

while True:
    print("Waiting for a connection")
    connection, client_address = sock.accept()
    try:
        print(f"Connection from {client_address}")

        msg_len_header = recv_all(connection, 8)
        if not msg_len_header:
            break

        msg_len = struct.unpack("!Q", msg_len_header)[0]
        full_message = recv_all(connection, msg_len)
        print(f"Received full message: {full_message!r}")

        print("Sending data back to the client")
        connection.sendall(msg_len_header + full_message)
    finally:
        print("Cleaning up connection")
        connection.close()
