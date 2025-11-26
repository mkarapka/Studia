from itertools import product
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
            print(" ".join(self.board[row]))

    def output_board(self):
        for row in range(self.board_size.y):
            print("".join(self.board[row]))

    def fill_every_row_with_sure_cells(self):
        filled_cells = 0
        for row in range(self.board_size.y):
            row_idx, cells = self.find_sure_filled_row_cells(row)
            self.fill_cells_in_row(row_idx, cells)
            filled_cells += len(cells)
        return filled_cells

    def fill_every_column_with_sure_cells(self):
        filled_cells = 0
        for column in range(self.board_size.x):
            column_idx, cells = self.find_sure_filled_column_cells(column)
            self.fill_cells_in_column(column_idx, cells)
            filled_cells += len(cells)
        return filled_cells

    def fill_cells_in_column(self, COLUMN, cells):
        for row in cells:
            if self.board[row][COLUMN] == '.':  # Only fill if not already filled
                self.board[row][COLUMN] = '#'

    def fill_cells_in_row(self, ROW, cells):
        for column in cells:
            if self.board[ROW][column] == '.':  # Only fill if not already filled
                self.board[ROW][column] = '#'

    def find_sure_filled_column_cells(self, column_index):
        def generate_sensible_column_block_moves_combinations(column_index):
            min_len_of_all_blocks = (
                sum(self.columns[column_index]) + len(self.columns[column_index]) - 1
            )
            max_free_space = self.board_size.y - min_len_of_all_blocks

            # Consider existing filled and banned cells
            valid_combinations = []
            combinations = generate_sensible_block_moves_combinations(
                0, self.columns[column_index], max_free_space
            )

            for combination in combinations:
                valid = True
                for start, end in combination:
                    for i in range(start, end + 1):
                        if i < self.board_size.y and self.board[i][column_index] == "X":
                            valid = False
                            break
                    if not valid:
                        break

                # Check spaces between blocks
                if valid and len(combination) > 1:
                    for i in range(len(combination) - 1):
                        current_end = combination[i][1]
                        next_start = combination[i+1][0]
                        for j in range(current_end + 1, next_start):
                            if j < self.board_size.y and self.board[j][column_index] == "#":
                                valid = False
                                break
                        if not valid:
                            break

                if valid:
                    valid_combinations.append(combination)

            return valid_combinations

        combinations_of_cells = generate_sensible_column_block_moves_combinations(
            column_index
        )

        if not combinations_of_cells:
            return column_index, []

        sure_filled = [0] * self.board_size.y
        return column_index, find_cells_which_are_in_every_combination(
            combinations_of_cells, sure_filled
        )

    def find_sure_filled_row_cells(self, row_index):
        def generate_sensible_row_block_moves_combinations(row_index):
            min_len_of_all_blocks = (
                sum(self.rows[row_index]) + len(self.rows[row_index]) - 1
            )
            max_free_space = self.board_size.x - min_len_of_all_blocks

            # Consider existing filled and banned cells
            valid_combinations = []
            combinations = generate_sensible_block_moves_combinations(
                0, self.rows[row_index], max_free_space
            )

            for combination in combinations:
                valid = True
                for start, end in combination:
                    for i in range(start, end + 1):
                        if i < self.board_size.x and self.board[row_index][i] == "X":
                            valid = False
                            break
                    if not valid:
                        break

                # Check spaces between blocks
                if valid and len(combination) > 1:
                    for i in range(len(combination) - 1):
                        current_end = combination[i][1]
                        next_start = combination[i+1][0]
                        for j in range(current_end + 1, next_start):
                            if j < self.board_size.x and self.board[row_index][j] == "#":
                                valid = False
                                break
                        if not valid:
                            break

                if valid:
                    valid_combinations.append(combination)

            return valid_combinations

        combinations_of_cells = generate_sensible_row_block_moves_combinations(
            row_index
        )

        if not combinations_of_cells:
            return row_index, []

        sure_filled = [0] * self.board_size.x
        return row_index, find_cells_which_are_in_every_combination(
            combinations_of_cells, sure_filled
        )

    def mark_banned_cells(self):
        banned_count = 0

        # Mark banned cells in rows
        for row in range(self.board_size.y):
            row_banned = self.find_banned_cells_in_row(row)
            for col in row_banned:
                if self.board[row][col] == '.':
                    self.board[row][col] = 'X'
                    banned_count += 1

        # Mark banned cells in columns
        for col in range(self.board_size.x):
            col_banned = self.find_banned_cells_in_column(col)
            for row in col_banned:
                if self.board[row][col] == '.':
                    self.board[row][col] = 'X'
                    banned_count += 1

        return banned_count

    def find_banned_cells_in_row(self, row_index):
        def generate_all_valid_row_combinations(row_index):
            min_len_of_all_blocks = (
                sum(self.rows[row_index]) + len(self.rows[row_index]) - 1
            )
            max_free_space = self.board_size.x - min_len_of_all_blocks

            all_combinations = generate_sensible_block_moves_combinations(
                0, self.rows[row_index], max_free_space
            )

            valid_combinations = []
            for combination in all_combinations:
                # Check if combination is valid with current board state
                valid = True
                filled_cells = set()

                for start, end in combination:
                    for i in range(start, end + 1):
                        filled_cells.add(i)
                        if i < self.board_size.x and self.board[row_index][i] == "X":
                            valid = False
                            break
                    if not valid:
                        break

                # Check if unfilled cells in combination don't overlap with filled cells on board
                if valid:
                    for i in range(self.board_size.x):
                        if i not in filled_cells and self.board[row_index][i] == "#":
                            valid = False
                            break

                if valid:
                    valid_combinations.append(filled_cells)

            return valid_combinations

        combinations = generate_all_valid_row_combinations(row_index)

        if not combinations:
            return []

        # Find cells that are never filled in any valid combination
        banned_cells = set()
        for i in range(self.board_size.x):
            if all(i not in combo for combo in combinations):
                banned_cells.add(i)

        return list(banned_cells)

    def find_banned_cells_in_column(self, col_index):
        def generate_all_valid_column_combinations(col_index):
            min_len_of_all_blocks = (
                sum(self.columns[col_index]) + len(self.columns[col_index]) - 1
            )
            max_free_space = self.board_size.y - min_len_of_all_blocks

            all_combinations = generate_sensible_block_moves_combinations(
                0, self.columns[col_index], max_free_space
            )

            valid_combinations = []
            for combination in all_combinations:
                # Check if combination is valid with current board state
                valid = True
                filled_cells = set()

                for start, end in combination:
                    for i in range(start, end + 1):
                        filled_cells.add(i)
                        if i < self.board_size.y and self.board[i][col_index] == "X":
                            valid = False
                            break
                    if not valid:
                        break

                # Check if unfilled cells in combination don't overlap with filled cells on board
                if valid:
                    for i in range(self.board_size.y):
                        if i not in filled_cells and self.board[i][col_index] == "#":
                            valid = False
                            break

                if valid:
                    valid_combinations.append(filled_cells)

            return valid_combinations

        combinations = generate_all_valid_column_combinations(col_index)

        if not combinations:
            return []

        # Find cells that are never filled in any valid combination
        banned_cells = set()
        for i in range(self.board_size.y):
            if all(i not in combo for combo in combinations):
                banned_cells.add(i)

        return list(banned_cells)

    def clean_board(self):
        for r in range(self.board_size.y):
            for c in range(self.board_size.x):
                if self.board[r][c] == "X":
                    self.board[r][c] = "."

    def is_puzzle_solved(self):
        # Check if all cells are filled with # or X (no . left)
        for r in range(self.board_size.y):
            for c in range(self.board_size.x):
                if self.board[r][c] == ".":
                    return False
        return True

    def solve(self):
        while True:
            progress = False

            # Fill sure cells in rows
            row_filled = self.fill_every_row_with_sure_cells()

            # Fill sure cells in columns
            col_filled = self.fill_every_column_with_sure_cells()

            # Mark banned cells
            banned = self.mark_banned_cells()

            # If no progress was made in this iteration, we're done
            if row_filled == 0 and col_filled == 0 and banned == 0:
                break

            progress = row_filled > 0 or col_filled > 0 or banned > 0

            if not progress:
                break

            # Check if the puzzle is solved
            if self.is_puzzle_solved():
                break

        # Clean the board for output (remove X marks)
        self.clean_board()

def write_into_file(board: Board):
    with open("zad_output.txt", "w") as file_out:
        for row in board.board:
            formatted_row = "".join(row) + '\n'
            file_out.write(formatted_row)

def main():
    y, x, rows_info, columns_info = read_nonogram_rows_column_info("zad_input.txt")
    board = Board(rows=rows_info, columns=columns_info, size=Size(x, y))

    # Solve the nonogram
    board.solve()

    # Output the solution
    board.output_board()
    write_into_file(board)


if __name__ == "__main__":
    main()
