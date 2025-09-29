import socket


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ("127.0.0.1", 2000)
    sock.bind(server_address)

    print("GPA server initiated")
    print("Enter marks to get GPA...\n")

    while True:
        try:
            client_message, client_address = sock.recvfrom(2000)
            print(f"Programme: {client_message.decode()}")
            programme = client_message.decode()

            sock.sendto(client_message, client_address)

            client_message, client_address = sock.recvfrom(2000)
            print(f"Marks: {client_message.decode()}")
            marks = int(client_message.decode())

            server_message = None

            grading_schema = [
                (90, "A+", 4.00),
                (86, "A", 4.00),
                (82, "A-", 3.67),
                (78, "B+", 3.33),
                (74, "B", 3.00),
                (70, "B-", 2.67),
                (66, "C+", 2.33),
                (62, "C", 2.00),
                (58, "C-", 1.67),
                (54, "D+", 1.33),
                (50, "D", 1.00)
            ]

            for cutoff, grade, gpa in grading_schema:
                if marks >= cutoff:
                    if cutoff < 70 and programme == "Ph.D.":
                        server_message = "Grade: F, GPA: 0.00"
                    elif cutoff < 62 and programme == "MS":
                        server_message = "Grade: F, GPA: 0.00"
                    else:
                        server_message = f"Grade: {grade}, GPA: {gpa}"
                    break

            sock.sendto(server_message.encode(), client_address)

        except Exception as e:
            print(f"An error occured: {e}")
            break

    sock.close()


if __name__ == "__main__":
    main()
