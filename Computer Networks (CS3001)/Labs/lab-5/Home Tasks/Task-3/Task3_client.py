import socket


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ("127.0.0.1", 2000)

    try:
        client_message = input("Enter your roll number: ")

        sock.sendto(client_message.encode(), server_address)

        server_message, _ = sock.recvfrom(2000)
        print(server_message.decode())

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        sock.close()


if __name__ == "__main__":
    main()
