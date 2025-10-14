import socket

HOST = "127.0.0.1"
PORT = 5000


def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((HOST, PORT))
    print("Connected to server! Enter commands to get response.")

    command = input("Enter a command (TIME, IP, CLIENTS): ").upper()
    client.sendall(command.encode())

    response = client.recv(1024).decode()

    print(f"Response: {response}")

    client.close()


if __name__ == "__main__":
    main()
