import numpy as np
import heapq


def get_board(file):
    with open(file, "r") as file_in:
        board = np.array([list(line.rstrip()) for line in file_in])
        return board


def get_points(board: np.ndarray, letter: str) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(board.shape[0])
        for x in range(board.shape[1])
        if board[y][x] == letter or board[y][x] == "B"
    )

UDLR = {
    "U": (-1, 0),
    "D": (1, 0),
    "L": (0, -1),
    "R": (0, 1),
}


def add(ran_coords: tuple, move: tuple) -> tuple:
    new_coords = (ran_coords[0] + move[0], ran_coords[1] + move[1])
    if board[*new_coords] == "#":
        return ran_coords
    return new_coords


def taxicab_distance(a: tuple, b: tuple) -> int:
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def potencial(rangers_state: frozenset, goal_points: frozenset):
    maxi = 0
    res_goal = ""
    res_ranger = ""
    for r in rangers_state:
        mini = 10**4
        point = (1, 1)
        ranger = (1, 1)
        for g in goal_points:
            dist = taxicab_distance(r, g)
            if dist < mini:
                mini = dist
                point = g
                ranger = r
        if mini > maxi:
            maxi = mini
            res_goal = point
            res_ranger = ranger
    print(res_goal)
    print(res_ranger)
    return [maxi , res_ranger, res_goal]


def Astar(
    board: np.ndarray, rangers_state: frozenset, goal_points: frozenset, f: list
) -> str:
    def next_moves(rangers_state: frozenset, prev_f: list):
        for d, m in UDLR.items():
            new_rangers_state = frozenset(add(r, m) for r in rangers_state)
            ran = add(prev_f[1], m)
            yield (taxicab_distance(ran, prev_f[2]), ran, new_rangers_state, d)

    path = ""
    visited = set()

    priority_queue = []

    g = 1
    heapq.heappush(priority_queue, (g + f[0], f, g, rangers_state, path))

    while priority_queue and len(path) <= 150:

        pp, f, g, rangers_state, path = heapq.heappop(priority_queue)
        visited.add(rangers_state)

        if all(board[*r] == "G" or board[*r] == "B" for r in rangers_state):
            return path

        for pot, ran, state, d in next_moves(rangers_state, f):
            if state not in visited:
                new_g = g + 1
                new_f = [pot, ran, f[2]]
                heapq.heappush(priority_queue, (new_g + pot, new_f, new_g, state, path + d))
    return "R"


with open("zad_output.txt", "w") as file_out:
    board = get_board("zad_input.txt")
    start_points = get_points(board, "S")
    goal_points = get_points(board, "G")
    f = potencial(start_points, goal_points)

    path = Astar(board=board, rangers_state=start_points, goal_points=goal_points, f=f)

    file_out.write(path)
