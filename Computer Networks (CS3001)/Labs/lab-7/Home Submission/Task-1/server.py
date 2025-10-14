from datetime import datetime
import socket
import threading

HOST = "127.0.0.1"
PORT = 5000

clients = []
thread_counter = 0

clients_lock = threading.Lock()
thread_counter_lock = threading.Lock()


def handle_client(conn, addr):
    global thread_counter
    with thread_counter_lock:
        thread_counter += 1

    print(f"[NEW CONNECTION] {addr} connected.")
    print(f"ACTIVE CLIENTS: {thread_counter}")

    with clients_lock:
        clients.append(conn)

    try:
        message = conn.recv(1024).decode()

        if message == "TIME":
            now = datetime.now()
            response = now.strftime("%A, %B, %d, %Y - %I:%M %p")
        elif message == "IP":
            response = f"{addr[0]}:{addr[1]}"
        elif message == "CLIENTS":
            response = f"{len(clients)} clients"
        else:
            response = "Error: Invalid command"

        conn.sendall(response.encode())
    finally:
        with clients_lock:
            clients.remove(conn)
        with thread_counter_lock:
            thread_counter -= 1
        print(f"[DISCONNECTED] {addr} disconnected.")
        print(f"ACTIVE CLIENTS: {thread_counter}")
        conn.close()


def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen()

    print(f"Server listening on {HOST}:{PORT}")

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))

        thread.start()


if __name__ == "__main__":
    main()
