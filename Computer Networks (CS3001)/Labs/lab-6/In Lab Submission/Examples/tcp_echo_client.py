import socket
import struct
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ("localhost", 10000)
print(f"Connecting to {server_address[0]} port {server_address[1]}")
sock.connect(server_address)

try:
    message = b"This is the message, it will be repeated."
    msg_len = len(message)
    header = struct.pack("!Q", msg_len)

    print(f"Sending message: {message!r}")
    sock.sendall(header + message)

    amount_received = 0
    amount_expected = msg_len + 8

    full_response = b""
    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        full_response += data

    print(f"Received full response: {full_response!r}")

finally:
    print("Closing socket")
    sock.close()
