import numpy as np
import heapq
from functools import lru_cache


# ====== Wczytywanie planszy ======

def get_board(file):
    with open(file, "r") as file_in:
        return np.array([list(line.rstrip()) for line in file_in])


def get_start_points(board: np.ndarray) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(board.shape[0])
        for x in range(board.shape[1])
        if board[y][x] == "S" or board[y][x] == "B"
    )


def get_goal_points(board: np.ndarray) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(board.shape[0])
        for x in range(board.shape[1])
        if board[y][x] == "G" or board[y][x] == "B"
    )


# ====== Ruchy i pomocnicze funkcje ======

UDLR = {
    "U": (-1, 0),
    "D": (1, 0),
    "L": (0, -1),
    "R": (0, 1),
}


def check_position(board: np.ndarray, coords: tuple) -> str:
    y, x = coords
    if y < 0 or y >= board.shape[0] or x < 0 or x >= board.shape[1]:
        return "Wall"
    if board[y][x] == "#":
        return "Wall"
    if board[y][x] == "G" or board[y][x] == "B":
        return "Goal"
    return "Empty"


def add(board: np.ndarray, ran_coords: tuple, move: tuple) -> tuple:
    new_coords = (ran_coords[0] + move[0], ran_coords[1] + move[1])
    if check_position(board, new_coords) == "Wall":
        return ran_coords
    return new_coords


def freeze_state(state: frozenset) -> tuple:
    return tuple(sorted(state))


def taxicab_distance(a: tuple, b: tuple) -> int:
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def make_potencial(goal_points):
    @lru_cache(maxsize=None)
    def potencial(state: tuple) -> int:
        return max(min(taxicab_distance(r, g) for g in goal_points) for r in state)
    return potencial


# ====== A* Algorytm ======

def Astar(board: np.ndarray, start_points: frozenset, goal_points: frozenset) -> str:
    potencial = make_potencial(tuple(goal_points))

    def next_moves(rangers_state: frozenset):
        for d, m in UDLR.items():
            new_rangers_state = frozenset(add(board, r, m) for r in rangers_state)
            yield (potencial(freeze_state(new_rangers_state)), new_rangers_state, d)

    path = ""
    visited = set()
    priority_queue = []

    h = potencial(freeze_state(start_points))
    g = 0
    heapq.heappush(priority_queue, (g + h, g, start_points, path))

    while priority_queue and len(path) <= 150:
        f, g, rangers_state, path = heapq.heappop(priority_queue)
        state_key = freeze_state(rangers_state)

        if state_key in visited:
            continue
        visited.add(state_key)

        if all(check_position(board, r) == "Goal" for r in rangers_state):
            return path

        for pot, state, d in next_moves(rangers_state):
            state_key = freeze_state(state)
            if state_key not in visited:
                new_g = g + 1
                heapq.heappush(priority_queue, (new_g + pot, new_g, state, path + d))

    return "R"  # fallback


# ====== Uruchomienie programu ======

if __name__ == "__main__":
    board = get_board("zad_input.txt")
    start_points = get_start_points(board)
    goal_points = get_goal_points(board)

    path = Astar(board=board, start_points=start_points, goal_points=goal_points)

    with open("zad_output.txt", "w") as file_out:
        file_out.write(path)
