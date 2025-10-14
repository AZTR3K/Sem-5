import socket
import threading

HOST = "127.0.0.1"
PORT = 5000

registered_voters = set()
already_voted = set()
candidates = []
vote_count = {}

voters_lock = threading.Lock()
vote_count_lock = threading.Lock()


def handle_voter(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    try:
        data = conn.recv(1024).decode().strip()
        if not data:
            return

        name, cnic = data.split("/")

        with voters_lock:
            if cnic not in registered_voters:
                conn.sendall("Error: CNIC not registered.".encode())
                return
            if cnic in already_voted:
                conn.sendall("Error: You have already voted.".encode())
                return
            already_voted.add(cnic)

        response = "Candidate List:\n"
        for i, (cand_name, symbol) in enumerate(candidates, 1):
            response += f"{i}. {cand_name} ({symbol})\n"
        conn.sendall(response.encode())

        symbol = conn.recv(1024).decode().strip()

        with vote_count_lock:
            if symbol in vote_count:
                vote_count[symbol] += 1
                conn.sendall("Vote cast successfully!".encode())
            else:
                conn.sendall("Invalid symbol.".encode())

    finally:
        conn.close()


def main():
    global registered_voters, candidates, vote_count

    with open("voters_list.txt", "r") as file:
        for line in file:
            parts = line.strip().split("/")
            if len(parts) == 2:
                registered_voters.add(parts[1])

    with open("candidates_list.txt", "r") as file:
        for line in file:
            f_name, l_name, symbol = line.strip().split()
            candidates.append((f_name + l_name, symbol))
            vote_count[symbol] = 0

    print(f"[INFO] Loaded {len(registered_voters)} voters and {
          len(candidates)} candidates.")

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)
    print(f"[LISTENING] Server running on {HOST}:{PORT}")

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_voter, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")


if __name__ == "__main__":
    main()
