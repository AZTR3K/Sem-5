import socket


def main():
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Bind the socket to the server address and port
    server_address = ('127.0.0.1', 2000)
    sock.bind(server_address)

    queries = {
        "What is CGPA?": "CGPA is the Cummulative Grade Point Average.",
        "What are the passing marks?": "You need at least 50% to pass.",
        "What is the attendance criteria?": "You need at least 80%.",
        "Who is your favourite person?": "My bbg Husnain."
    }

    print("Socket created and bound")
    print("Waiting for queries...\n")

    print("Queries being caterred: ")
    for key in queries.keys():
        print(key)

    try:
        while True:
            client_message, client_address = sock.recvfrom(2000)
            print(f"Received message from IP: {
                  client_address[0]} and Port number: {client_address[1]}")
            print(f"Client message: {client_message.decode()}")

            send_message = ""

            if client_message.decode() in queries.keys():
                send_message = queries[client_message.decode()]
            else:
                send_message = "Sorry I do not understand that question."

            sock.sendto(send_message.encode(), client_address)

    except Exception as e:
        print(f"An error occured: {e}")

    finally:
        sock.close()


if __name__ == "__main__":
    main()
