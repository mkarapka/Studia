from typing_extensions import Generator
import numpy as np
from itertools import product
import random
from collections import deque

def get_board(file):
    with open(file, "r") as file_in:
        board = np.array([list(line.rstrip()) for line in file_in])
        return board


def get_start_points(board: np.ndarray) -> frozenset:
    return frozenset(
        (y, x)
        for y in range(len(board))
        for x in range(len(board[0]))
        if board[y][x] == "S" or board[y][x] == "B"
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


def add(ran_coords: tuple, move: tuple):
    new_coords = (ran_coords[0] + move[0], ran_coords[1] + move[1])
    if check_position(board, new_coords) == "Wall":
        return ran_coords
    return new_coords


def bfs(board: np.ndarray, start_points: frozenset, moves=0):
    def next_moves(rangers: frozenset) -> Generator:
        for d, m in UDLR.items():
            yield d, frozenset(add(r, m) for r in rangers)

    path = ""
    rangers_state = start_points
    queue = deque([(rangers_state, path)])
    visited = set()
    counter = moves

    while queue and len(path) + moves <= 150:

        # print(len(path) + moves)
        rangers_state, path = queue.popleft()
        visited.add(rangers_state)

        if all(check_position(board, r) == "Goal" for r in rangers_state):
            return path

        for d, m in next_moves(rangers_state):
            if m not in visited:
                queue.append((m, path + d))
    return "Not found"

def random_moves(start_points : frozenset, moves=110, threshold=1, ceil=2000):
    def greedy_path(d1: str, d2: str, steps: int, rangers: frozenset):
        def return_move(direction: str, tmp_rangers: frozenset):
            return direction, frozenset(add(r, UDLR[direction]) for r in tmp_rangers)

        path = ""
        for i in range(steps):
            if i % 2 == 0:
                p, rangers = return_move(d1, rangers)
            else:
                p, rangers = return_move(d2, rangers)
            path += p
        return path, rangers

    pair_1 = ("L", "R")
    pair_2 = ("D", "U")
    cartesian = list(product(pair_1, pair_2))

    counter = 0
    result_state = start_points
    result_path = ""
    iters = 0
    while len(result_state) > threshold and iters < ceil:
        counter = 0
        path = ""
        rangers = start_points
        while counter < moves and len(rangers) > 1:
            steps = random.randint(1, 10)
            rand_direct = random.choice(cartesian)
            new_p, rangers = greedy_path(d1=rand_direct[0], d2=rand_direct[1], steps=steps, rangers=rangers)
            path += new_p
            counter += steps
        if len(rangers) < len(result_state):
            result_state = rangers
            result_path = path
        iters += 1
    return result_path, result_state, counter


with open("zad_output.txt", "w") as file_out:
    board = get_board("zad_input.txt")
    start_points = get_start_points(board)
    # Here is place for random moves
    while True:
        first_path, first_rangers, first_moves = random_moves(start_points, threshold=1)
        print("Length of set:", len(first_rangers))
        print("start points:", first_rangers)
        second_path = bfs(board=board, start_points=first_rangers, moves=first_moves)
        if second_path != "Not found":
            break
    path = first_path + second_path
    file_out.write(path)
