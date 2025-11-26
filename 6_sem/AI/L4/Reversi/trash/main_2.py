import sys
sys.stdout = open(sys.stdout.fileno(), mode='w', buffering=1, encoding='utf-8', closefd=False)

DEPTH = 3

DIRECTIONS = 8
BOARD_SIZE = 64
BOARD_LEN = 8

ROW = [-1, -1, 0, +1, +1, +1, 0, -1]
COL = [0, +1, +1, +1, 0, -1, -1, -1]

CORNERS = [(0, 0), (0, 7), (7, 0), (7, 7)]

CELL_SCORE = [
    [20, -3, 11, 8, 8, 11, -3, 20],
    [-3, -7, -4, 1, 1, -4, -7, -3],
    [11, -4, 2, 2, 2, 2, -4, 11],
    [8, 1, 2, -3, -3, 2, 1, 8],
    [8, 1, 2, -3, -3, 2, 1, 8],
    [11, -4, 2, 2, 2, 2, -4, 11],
    [-3, -7, -4, 1, 1, -4, -7, -3],
    [20, -3, 11, 8, 8, 11, -3, 20]
]

class State:
    def __init__(self, starting=False):
        self.player = [[False]*BOARD_LEN for _ in range(BOARD_LEN)]
        self.opponent = [[False]*BOARD_LEN for _ in range(BOARD_LEN)]
        self.reset(starting)

    def reset(self, starting):
        for i in range(BOARD_LEN):
            for j in range(BOARD_LEN):
                self.player[i][j] = False
                self.opponent[i][j] = False
        self.player[3][4] = self.player[4][3] = True
        self.opponent[3][3] = self.opponent[4][4] = True
        if not starting:
            self.swap_players()

    def set_player_cell(self, row, col, value):
        if self.good_position(row, col):
            self.player[row][col] = value

    def get_player_cell(self, row, col):
        return self.good_position(row, col) and self.player[row][col]

    def set_opponent_cell(self, row, col, value):
        if self.good_position(row, col):
            self.opponent[row][col] = value

    def get_opponent_cell(self, row, col):
        return self.good_position(row, col) and self.opponent[row][col]

    def swap_players(self):
        self.player, self.opponent = self.opponent, self.player

    def make_move(self, row, col):
        self.set_player_cell(row, col, True)
        for d in range(DIRECTIONS):
            if not self.possible_move(row, col, d):
                continue
            new_row, new_col = row + ROW[d], col + COL[d]
            while self.get_opponent_cell(new_row, new_col):
                self.set_player_cell(new_row, new_col, True)
                self.set_opponent_cell(new_row, new_col, False)
                new_row += ROW[d]
                new_col += COL[d]

    def good_position(self, row, col):
        return 0 <= row < BOARD_LEN and 0 <= col < BOARD_LEN

    def possible_move(self, row, col, d):
        row += ROW[d]
        col += COL[d]
        if not self.good_position(row, col) or not self.get_opponent_cell(row, col):
            return False
        while self.good_position(row, col) and self.get_opponent_cell(row, col):
            row += ROW[d]
            col += COL[d]
        return self.good_position(row, col) and self.get_player_cell(row, col)

    def get_actions(self):
        res = []
        for row in range(BOARD_LEN):
            for col in range(BOARD_LEN):
                if self.get_player_cell(row, col) or self.get_opponent_cell(row, col):
                    continue
                for d in range(DIRECTIONS):
                    if self.possible_move(row, col, d):
                        res.append((row, col))
                        break
        return res

    def utility(self):
        res = 0
        for i in range(BOARD_LEN):
            for j in range(BOARD_LEN):
                if self.get_player_cell(i, j):
                    res += 1
                elif self.get_opponent_cell(i, j):
                    res -= 1
        return res

    def calculate_ratio(self, player, opponent):
        if player + opponent == 0:
            return 0
        return int(100 * ((player - opponent) / (player + opponent)))

    def heuristic_value(self):
        board_bilans = 0
        player_cells = 0
        opponent_cells = 0
        for i in range(BOARD_LEN):
            for j in range(BOARD_LEN):
                if self.get_player_cell(i, j):
                    board_bilans += CELL_SCORE[i][j]
                    player_cells += 1
                elif self.get_opponent_cell(i, j):
                    board_bilans -= CELL_SCORE[i][j]
                    opponent_cells += 1

        ratio = self.calculate_ratio(player_cells, opponent_cells)

        player_corners = 0
        opponent_corners = 0
        for row, col in CORNERS:
            if self.get_player_cell(row, col):
                player_corners += 1
            elif self.get_opponent_cell(row, col):
                opponent_corners += 1

        corner_ratio = 0
        if player_corners + opponent_corners:
            corner_ratio = self.calculate_ratio(player_corners, opponent_corners)

        player_close_corners = 0
        opponent_close_corners = 0
        for row, col in CORNERS:
            if self.get_player_cell(row, col) or self.get_opponent_cell(row, col):
                continue
            for d in range(DIRECTIONS):
                new_row, new_col = row + ROW[d], col + COL[d]
                if self.good_position(new_row, new_col):
                    if self.get_player_cell(new_row, new_col):
                        player_close_corners += 1
                    elif self.get_opponent_cell(new_row, new_col):
                        opponent_close_corners += 1

        close_corner_value = player_close_corners - opponent_close_corners

        return ((10 * ratio) + (800 * corner_ratio) + (-12 * 380 * close_corner_value) + (80 * board_bilans))

    def terminal(self, actions=None):
        if actions is None:
            actions = self.get_actions()
        return len(actions) == 0

    def make_action(self, row, col):
        if row != -1 and col != -1:
            self.make_move(row, col)
        self.swap_players()

    def make_new_state(self, row, col):
        res = State()
        res.player = [row[:] for row in self.player]
        res.opponent = [row[:] for row in self.opponent]
        res.make_action(row, col)
        return res

class AI:
    MAX_DEPTH = DEPTH
    MAXI = 1
    MINI = 0
    INF = int(1e9)

    def gest_bets_action(self, state):
        return self.AlphaBetaRoot(state)

    def AlphaBetaRoot(self, state):
        best_value = -self.INF
        best_move = (-1, -1)
        actions = state.get_actions()
        for row, col in actions:
            value = self.AlphaBeta(state.make_new_state(row, col), self.MAX_DEPTH, self.MINI, -self.INF, self.INF)
            if value > best_value:
                best_value = value
                best_move = (row, col)
        return best_move

    def AlphaBeta(self, state, depth, player, alpha, beta):
        actions = state.get_actions()
        if state.terminal(actions):
            next_state = state.make_new_state(-1, -1)
            if next_state.terminal():
                return state.utility() * (1 if player == self.MAXI else -1)
            else:
                return self.AlphaBeta(next_state, depth, 1 - player, alpha, beta)
        if depth == 0:
            return state.heuristic_value() * (1 if player == self.MAXI else -1)
        best_value = -self.INF if player == self.MAXI else self.INF
        for row, col in actions:
            value = self.AlphaBeta(state.make_new_state(row, col), depth - 1, 1 - player, alpha, beta)
            if player == self.MAXI:
                best_value = max(best_value, value)
                alpha = max(alpha, value)
            else:
                best_value = min(best_value, value)
                beta = min(beta, value)
            if alpha >= beta:
                break
        return best_value

def say(s):
    print(s)
    sys.stdout.flush()

def say_move(row, col):
    row, col = col, row
    print(f"IDO {row} {col}")
    sys.stdout.flush()

def main():
    Game = State(True)
    Ai = AI()
    say("RDY")
    while True:
        try:
            str_in = input()
        except EOFError:
            break
        if str_in == "BYE":
            break
        if str_in == "UGO":
            t0, t1 = map(float, input().split())
            p = Ai.gest_bets_action(Game)
            say_move(p[1], p[0])
            Game.make_action(p[0], p[1])
        elif str_in == "HEDID":
            t0, t1, col, row = input().split()
            row, col = int(row), int(col)
            Game.make_action(row, col)
            p = Ai.gest_bets_action(Game)
            say_move(p[1], p[0])
            Game.make_action(p[0], p[1])
        elif str_in == "ONEMORE":
            Game.reset(True)
            say("RDY")
