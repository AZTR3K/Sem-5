import socket


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ("127.0.0.1", 2000)

    try:
        client_message = input("Enter programme: ")

        sock.sendto(client_message.encode(), server_address)

        server_message, _ = sock.recvfrom(2000)

        client_message = input("Enter marks (0-100): ")
        sock.sendto(client_message.encode(), server_address)

        server_message, _ = sock.recvfrom(2000)

        print(f"Grade and CGPA: {server_message.decode()}")

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        sock.close()


if __name__ == "__main__":
    main()
