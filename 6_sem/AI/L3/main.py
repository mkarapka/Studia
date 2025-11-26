import numpy as np

# from itertools import product
from functions import *


def read_nonogram_rows_column_info(file_name):
    with open(file_name, "r") as file:
        readed_file = [[int(d) for d in l.rstrip().split()] for l in file.readlines()]
        rows, columns = readed_file[0][0], readed_file[0][1]

        return rows, columns, readed_file[1 : rows + 1], readed_file[rows + 1 :]


class Size:
    def __init__(self, x, y):
        self.x, self.y = x, y


class Board:
    def __init__(self, rows, columns, size: Size):
        self.rows, self.columns = rows, columns
        self.board_size = size
        self.board = [
            ["." for _ in range(self.board_size.x)] for _ in range(self.board_size.y)
        ]

    def print_board(self):
        for row in range(self.board_size.y):
            print(row, " ".join(self.board[row]))

    def try_color_whole_block_in_row(self, row_index, cell_index):
        row_blocks = self.rows[row_index]
        row = self.board[row_index]
        row_len = len(row)
        possible_block_positions = []

        # Dla każdego bloku sprawdź wszystkie możliwe pozycje
        for block_idx, block_len in enumerate(row_blocks):
            for start in range(row_len - block_len + 1):
                end = start + block_len - 1
                # Czy cell_index należy do tego bloku?
                if not (start <= cell_index <= end):
                    continue
                # Czy blok nie nachodzi na już zabronione komórki?
                if any(row[i] == "X" for i in range(start, end + 1)):
                    continue
                # Czy przed i po bloku nie ma nieprawidłowych kolorowań?
                if start > 0 and row[start - 1] == "#":
                    continue
                if end < row_len - 1 and row[end + 1] == "#":
                    continue
                # Czy w bloku nie ma pustych miejsc, które są już pokolorowane na 'X'?
                possible_block_positions.append((block_idx, start, end))

        # Jeśli tylko jedna możliwość – kolorujemy cały blok
        if len(possible_block_positions) == 1:
            _, start, end = possible_block_positions[0]
            for i in range(start, end + 1):
                self.board[row_index][i] = "#"
            return True  # coś się zmieniło
        return False

    def fill_every_row_with_sure_cells(self):
        def fill_cells_in_row(ROW, cells):
            for column in cells:
                self.board[ROW][column] = "#"

        for row in range(self.board_size.y):
            fill_cells_in_row(*self.find_sure_filled_row_cells(row))

    def fill_every_column_with_sure_cells(self):
        def fill_cells_in_column(COLUMN, cells):
            for row in cells:
                self.board[row][COLUMN] = "#"

        for column in range(self.board_size.x):
            fill_cells_in_column(*self.find_sure_filled_row_cells(column))

    def find_sure_filled_column_cells(self, column_index):
        def generate_sensible_column_block_moves_combinations(column_index):
            min_len_of_all_blocks = (
                sum(self.columns[column_index]) + len(self.columns[column_index]) - 1
            )
            max_free_space = self.board_size.y - min_len_of_all_blocks
            return generate_sensible_block_moves_combinations(
                0, self.columns[column_index], max_free_space
            )

        combinations_of_cells = generate_sensible_column_block_moves_combinations(
            column_index
        )
        sure_filled = [0] * self.board_size.y
        return column_index, find_cells_which_are_in_every_combination(
            combinations_of_cells,
            sure_filled,
            [self.board[r][column_index] for r in range(self.board_size.y)],
        )

    def find_sure_filled_row_cells(self, row_index):
        def generate_sensible_row_block_moves_combinations(row_index):
            min_len_of_all_blocks = (
                sum(self.rows[row_index]) + len(self.rows[row_index]) - 1
            )
            max_free_space = self.board_size.x - min_len_of_all_blocks
            return generate_sensible_block_moves_combinations(
                0, self.rows[row_index], max_free_space
            )

        combinations_of_cells = generate_sensible_row_block_moves_combinations(
            row_index
        )
        sure_filled = [0] * self.board_size.x
        return row_index, find_cells_which_are_in_every_combination(
            combinations_of_cells,
            sure_filled,
            self.board[row_index],
        )

    def clean_board(self):
        for r in range(self.board_size.y):
            for c in range(self.board_size.x):
                if self.board[r][c] == "X":
                    self.board[r][c] = "."

    def mark_banned_row_fields(self, row, last_column, len_of_block):
        if len_of_block <= last_column:
            self.board[row][last_column - len_of_block] = "X"
        if last_column < self.board_size.x - 1:
            self.board[row][last_column + 1] = "X"

    def mark_banned_column_fields(self, column, last_row, len_of_block):
        if len_of_block <= last_row:
            self.board[last_row - len_of_block][column] = "X"
        if last_row < self.board_size.y - 1:
            self.board[last_row + 1][column] = "X"


def write_into_file(board: Board):
    with open("zad_output.txt", "w") as file_out:
        for row in board.board:
            formatted_row = "".join(row) + "\n"
            file_out.write(formatted_row)


# Max to są obrazki 15 x 15
# Zasada
y, x, rows_info, columns_info = read_nonogram_rows_column_info("zad_input.txt")
board = Board(rows=rows_info, columns=columns_info, size=Size(x, y))
print(board.columns)
# print(board.find_sure_filled_column_cells(3))
board.print_board()
board.fill_every_row_with_sure_cells()
board.fill_every_row_with_sure_cells()
print("dupa")
board.print_board()
