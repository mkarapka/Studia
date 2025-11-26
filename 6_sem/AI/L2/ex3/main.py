import numpy as np
import heapq


def get_board(file):
    with open(file, "r") as file_in:
        board = np.array([list(line.rstrip()) for line in file_in])
        return board


def get_start_points(board: np.ndarray) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(board.shape[0])
        for x in range(board.shape[1])
        if board[y][x] == "S" or board[y][x] == "B"
    )


def get_goal_points(boad: np.ndarray) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(board.shape[0])
        for x in range(board.shape[1])
        if board[y][x] == "G" or board[y][x] == "B"
    )


UDLR = {
    "U": (-1, 0),
    "D": (1, 0),
    "L": (0, -1),
    "R": (0, 1),
}


def check_position(board: np.ndarray, coords: tuple) -> str:
    if board[*coords] == "#":
        return "Wall"
    if board[*coords] == "G" or board[*coords] == "B":
        return "Goal"
    return "Empty"


def add(ran_coords: tuple, move: tuple) -> tuple:
    new_coords = (ran_coords[0] + move[0], ran_coords[1] + move[1])
    if check_position(board, new_coords) == "Wall":
        return ran_coords
    return new_coords


def potencial(rangers_state: frozenset, goal_points: frozenset) -> int:
    def taxicab_distance(a: tuple, b: tuple) -> int:
        return abs(a[0] - b[0]) + abs(a[1] - b[1])
    return max(min(taxicab_distance(r, g) for g in goal_points) for r in rangers_state)


def Astar(board: np.ndarray, start_points: frozenset, goal_points: frozenset) -> str:
    def next_moves(rangers_state: frozenset):
        for d, m in UDLR.items():
            new_rangers_state = frozenset(add(r, m) for r in rangers_state)
            yield (potencial(new_rangers_state, goal_points), new_rangers_state, d)

    path = ""
    rangers_state = start_points
    visited = set()

    priority_queue = []

    h = potencial(rangers_state, goal_points)
    g = len(path) + 1
    heapq.heappush(priority_queue, (g + h, g, rangers_state, path))

    while priority_queue and len(path) <= 150:

        f, g, rangers_state, path = heapq.heappop(priority_queue)
        visited.add(rangers_state)

        if all(check_position(board, r) == "Goal" for r in rangers_state):
            return path

        for pot, state, d in next_moves(rangers_state):
            if state not in visited:
                new_g = g + 1
                heapq.heappush(priority_queue, (new_g + pot, new_g, state, path + d))
    return "R"


with open("zad_output.txt", "w") as file_out:
    board = get_board("zad_input.txt")
    start_points = get_start_points(board)
    goal_points = get_goal_points(board)

    path = Astar(board=board, start_points=start_points, goal_points=goal_points)

    file_out.write(path)
