import numpy as np

np.random.seed(43)
def read_picture(file_in):
    lines = [l.rstrip() for l in open(file_in, "r").readlines()]
    x_size, y_size = map(int, lines[0].split())
    rows = [int(lines[row]) for row in range(1, x_size + 1)]
    columns = [int(lines[col]) for col in range(x_size + 1, x_size + y_size + 1)]

    return [x_size, y_size, rows, columns]


def create_picture(picture_info):
    rows, cols = picture_info[0], picture_info[1]
    picture = np.random.randint(0, 2, size=(rows, cols))
    return picture


def solve_picture(picture, info, steps):
    # number of rows and columns, number of ones on each row and column
    rows, cols, Tx, Ty = info[0], info[1], info[2], info[3]

    def is_solved():
        for row in range(rows):
            seg_1, len_ones_1 = is_correct(picture[row], Tx[row])

            if seg_1 != 1 or len_ones_1 != Tx[row]:
                return False

        for col in range(cols):
            seg, len_ones = is_correct(picture[:, col], Ty[col])
            if seg != 1 or len_ones != Ty[col]:
                return False
        # print(len_ones_1, Tx[row])
        return True

    def is_correct(line, T, neg=False, digit=None):
        cp_row = line.copy()
        if neg:
            cp_row[digit] ^= 1

        sum_of_ones = sum(d for d in cp_row)
        if T == 0 and sum_of_ones == 0:
            return [0, 0]

        str_row = "".join(str(d) for d in cp_row)
        segments = sum(1 for seq in str_row.split("0") if "1" in seq)
        len_ones = sum(cp_row)

        return [segments, int(len_ones)]

    def adj_err(row, d):
        S, L = is_correct(picture[row], Tx[row], neg=True, digit=d)
        row_error = abs(L - Tx[row]) + (S - 1) ** 2

        S, L = is_correct(picture[:, d], Ty[d], neg=True, digit=row)
        column_error = abs(L - Ty[d]) + (S - 1) ** 2

        return row_error + column_error

    def chose_best_pixel(row):
        mae_array = [
            adj_err(row, d) for d in range(len(picture[row]))
        ]  # Indeksy, nie wartości!
        mae = min(mae_array)
        best_pixel = mae_array.index(mae)  # Znalezienie indeksu, a nie wartości
        return best_pixel

    def flip_pixel(row):
        if np.random.rand() < 0.05:
            i = np.random.randint(0, cols)
        else:
            i = chose_best_pixel(row)

        picture[row][i] ^= 1

    def do_work(s):
        steps = 0
        while not is_solved() and steps < s:
            row = np.random.randint(0, rows)
            flip_pixel(row)
            steps += 1

        if is_solved():
            return True
        return False

    it = 0
    while True:
        if it % 100 == 0:
            print(it)
        if do_work(steps):
            return picture
        picture = create_picture(info)
        it += 1


FILE_IN = "zad5_input.txt"

info = read_picture(FILE_IN)
picture = create_picture(info)

solved_picture = solve_picture(picture, info, 10**3)
# print(solved_picture)
# print(info[2], info[3])

with open("zad5_output.txt", "w") as write_file:
    for line in solved_picture:
        prep_line = ""
        for d in line:
            pixel = "." if d == 0 else "#"
            prep_line += pixel
        write_file.write(prep_line + "\n")
