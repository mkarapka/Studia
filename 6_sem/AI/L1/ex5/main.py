import random
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


def solve_picture(picture, info):
    # number of rows and columns, number of ones on each row and column
    rows, cols, Tx, Ty = info[0], info[1], info[2], info[3]

    def is_solved():
        for row in range(rows):
            seg, len_ones = is_correct(row)
            if not seg == 1 and not len_ones == Tx[row]:
                return False
            
        for col in range(cols):
            col_array = picture[:, col]
            
        

    def is_correct(row, neg=False, digit=None):
        cp_row = picture[row][:]
        if neg:
            cp_row[digit] = cp_row[digit] ^ 1
            # print(cp_row)

        sum_of_ones = sum(d for d in cp_row)
        if Tx[row] == 0 and sum_of_ones == 0:
            return True

        str_row = "".join(str(d) for d in cp_row)
        segments = sum(1 for seq in str_row.split("0") if "1" in seq)
        len_ones = sum(cp_row)

        return [segments, int(len_ones)]

    def adj_err(row, d):
        S, L = is_correct(row, neg=True, digit=d)
        error = abs(L - Tx[row]) + (S - 1)
        return error

    def chose_best_pixel(row):
        # minimum adjustment error
        mae_array = [adj_err(row, d) for d in picture[row]]

        mae = min(mae_array)
        best_pixel = list(mae_array).index(mae)
        return best_pixel

    # while not is_solved():
    #     row = np.random.randint(0, rows)
    #     min_adj_error = min(adj_err(d) for d in picture[row])

    row = np.random.randint(0, rows)
    print("n of rows, Tx[row], row:", row, Tx[row], picture[row])
    print("output - is_correct", is_correct(row))
    lst = [adj_err(row, d) for d in picture[row]]
    print("mae_array for row:\n", lst)
    print("mae\n", min(lst))
    print("chosing best pixel\n", chose_best_pixel(row))
    # print(adj_err(row))


FILE_IN = "zad5_input.txt"

info = read_picture(FILE_IN)
print(info)
picture = create_picture(info)
print(picture)
solve_picture(picture, info)
