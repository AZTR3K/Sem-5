import socket

HOST = "127.0.0.1"
PORT = 5000


def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect((HOST, PORT))
        print("Connected to Voting Server!\n")

        name = input("Enter your full name: ")
        cnic = input("Enter your CNIC (xxxxx-xxxxxxx-x): ")
        message = f"{name}/{cnic}"

        client.sendall(message.encode())

        response = client.recv(2048).decode().strip()

        if "error" in response.lower():
            print(response)
            return

        print("\nAuthenticated successfully!")
        print(response)

        symbol = input(
            "Enter the poll symbol of your chosen candidate: ").strip()
        client.sendall(symbol.encode())

        confirmation = client.recv(1024).decode().strip()
        print("\n" + confirmation)

    finally:
        client.close()


if __name__ == "__main__":
    main()
