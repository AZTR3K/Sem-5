# Question 1
def word_frequency(text):
    para = ""
    for char in text:
        if 'a' <= char <= 'z' or 'A' <= char <= 'Z' or char == ' ':
            para += char.lower()

    words = para.split()

    frequency = {}

    for word in words:
        if word in frequency:
            frequency[word] += 1
        else:
            frequency[word] = 1

    return frequency


# Question 2
def matrix_sum(matrix, m, n, r):
    if r == 0:
        row_sums = []
        for i in range(0, m):
            res = 0
            for j in range(0, n):
                res += matrix[i][j]
            row_sums.append(res)
        return row_sums

    elif r == 1:
        col_sums = []
        for i in range(0, n):
            res = 0
            for j in range(0, m):
                res += matrix[j][i]
            col_sums.append(res)
        return col_sums

    elif r == 2:
        diagonal_sums = {}
        d1 = 0
        d2 = 0

        for i in range(m):
            for j in range(n):
                if i == j:
                    d1 += matrix[i][j]

        for i in range(m):
            for j in range(n):
                if i + j == n - 1:
                    d2 += matrix[i][j]

        diagonal_sums['main_diagonal'] = d1
        diagonal_sums['reverse_diagonal'] = d2
        return diagonal_sums


if __name__ == "__main__":
    # Question 1 test
    print("Question 1:")
    text = "Hello, world! Hello Python. Python is great, and Python is fun."
    print(word_frequency(text))

    # Question 2 test
    print("\nQuestion 2:")
    matrix = [[1, 2], [3, 4]]
    print(matrix_sum(matrix, 2, 2, 2))

    # Question 3
    print("\nQuestion 3:")
    dob = input("Enter your date of birth in the format: dd-mm-yyyy ")
    date, month, year = dob.split("-")

    years = 2025 - int(year)
    months = 8 - int(month)
    days = 21 - int(date)

    if days < 0:
        days += 30
        months -= 1

    if months < 0:
        months += 12
        years -= 1

    print(f"You are {years} years, {months} months, {days} days old.")
