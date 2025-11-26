

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Square:
    def __init__(self, size, letter):
        self.size = (size, size)
        self.letter = letter
        self.position = Point(-1, -1)

    def set_position(self, p : Point):
        self.position = p

def create_squares(n):
    return [Square(s, chr(ord("A") + s - 1)) for s in range(n, 0, -1)]

def is_fit(sq: Square, board):
    x, y = sq.position.x, sq.position.y
    size = sq.size[0]
    if x + size > 70 or y + size > 70:
        return False
    for r in range(y, y + size):
        for c in range(x, x + size):
            if board[r][c] != '.':
                return False
    return True
def place_square(sq: Square, board):
    x, y = sq.position.x, sq.position.y
    size = sq.size[0]
    for r in range(y, y + size):
        for c in range(x, x + size):
            board[r][c] = sq.letter
    return board

def fit_all_squares(board, squares):
    for sq in squares:
        placed = False
        for y in range(70):
            for x in range(70):
                sq.set_position(Point(x, y))
                if is_fit(sq, board):
                    board = place_square(sq, board)
                    placed = True
                    break
            if placed:
                break

def count_empty(board):
    return sum(row.count('.') for row in board)

def print_board(board):
    print(count_empty(board))
    for row in board:
        print(''.join(row))

def write_board_into_file(board, file_name):
    with open(file_name, "w") as out:
        for row in board:
            out.write(' '.join(row) + '\n')

BOARD = [['.' for _ in range(70)] for _ in range(70)]
squares = create_squares(24)
fit_all_squares(BOARD, squares)
# print_board(BOARD)

print("Amount of empty cells:", count_empty(BOARD))
write_board_into_file(BOARD, "out.txt")
