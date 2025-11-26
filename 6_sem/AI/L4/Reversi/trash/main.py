# 0 - black, 1 - white

def init_board(size):
    bd = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4, "F": 5, "G": 6, "H": 7}
    board = [[-1 for _ in range(size)] for _ in range(size)]
    board[bd["E"]][3], board[bd["E"]][4] = 0, 1
    board[bd["D"]][3], board[bd["D"]][4] = 1, 0
    return board


class board:
    def __init__(self) -> None:
        self.white = None
        self.black = None
        self.board = init_board(8)
        self.directions = {
            "N": (0, -1),
            "NE": (1, -1),
            "E": (1, 0),
            "SE": (1, 1),
            "S": (0, 1),
            "SW": (-1, 1),
            "W": (-1, 0),
            "NW": (-1, -1),
        }

    def is_illegal_to_move(self, position, color):
        x, y = position
        if x < 0 or y < 0:
            return True
        if x > 7 or y > 7:
            return True
        if self.board[y][x] == -1:
            return True
        if self.board[y][x] == color:
            return True
        return False

    def reverse(self, color, p, direct):
        x, y = p
        while not self.is_illegal_to_move(self.board[y][x], color):
            self.board[y][x] = color
            p += direct
            x, y = p

    def move(self, color, p):
        if not self.is_illegal_to_move(p, color):
            board = self.board
            return board
        return None
