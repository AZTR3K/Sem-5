import socket


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ("127.0.0.1", 2000)
    sock.bind(server_address)

    students = []
    print("Server initiated")

    try:
        while True:
            client_message, client_address = sock.recvfrom(2000)
            year, rollno, check = client_message.decode().split("-")

            student = year + '-' + rollno
            server_message = ""

            if check == "CI":
                if student not in students:
                    students.append(student)
                    server_message = f"Welcome Student {student}."
                else:
                    server_message = "You are already there."

            elif check == "CO":
                if student in students:
                    server_message = f"Goodbye Student {
                        student}! Have a nice day."
                    students.remove(student)
                else:
                    server_message = "You didn't check in today. Contact System Administrator."

            sock.sendto(server_message.encode(), client_address)

            print("Checked in student list:")
            for _ in students:
                print(_)

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        sock.close()


if __name__ == "__main__":
    main()
