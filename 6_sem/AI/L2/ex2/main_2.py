import numpy as np
import random


def get_board(file):
    with open(file, "r") as file_in:
        board = np.array([list(line.rstrip()) for line in file_in])
        return board


def get_start_points(board: np.ndarray):
    return [
        (y, x)
        for y in range(len(board))
        for x in range(len(board[0]))
        if board[y][x] == "S" or board[y][x] == "B"
    ]


class Ranger:
    def __init__(self, start_points: np.array, board: np.array):
        self.coords = random.choice(start_points)
        self.board = board
        self.UDLR = {
            "U": np.array([-1, 0]),
            "D": np.array([1, 0]),
            "L": np.array([0, -1]),
            "R": np.array([0, 1]),
        }

    def check_position(self, coords):
        y, x = coords
        if (
            y < 0
            or y >= self.board.shape[0]
            or x < 0
            or x >= self.board.shape[1]
        ):
            return "Wall"
        if self.board[y][x] == "#":
            return "Wall"
        if self.board[y][x] == "G" or self.board[y][x] == "B":
            return "Goal"
        return "Empty"

    def explore_uncertainty(self, limit=100):
        """Faza 1: redukcja niepewności, losowe długie ruchy"""
        path = []
        curr_coords = np.array(self.coords)
        for _ in range(limit):
            dir = random.choice(list(self.UDLR.keys()))
            move = self.UDLR[dir]
            steps = 0
            # idź aż do przeszkody lub celu
            while True:
                next_coords = curr_coords + move
                field = self.check_position(next_coords)
                if field == "Wall":
                    break
                curr_coords = next_coords
                path.append(dir)
                steps += 1
                if field == "Goal":
                    return curr_coords, path
        return curr_coords, path

    def bfs(self, start_coords):
        """Faza 2: klasyczne BFS z rekonstrukcją ścieżki"""
        from collections import deque
        queue = deque()
        queue.append((tuple(start_coords), []))
        visited = set()
        visited.add(tuple(start_coords))

        while queue:
            curr_coords, path = queue.popleft()
            if self.check_position(curr_coords) == "Goal":
                return path
            for dir, move in self.UDLR.items():
                next_coords = tuple(np.array(curr_coords) + move)
                if next_coords not in visited and self.check_position(next_coords) != "Wall":
                    visited.add(next_coords)
                    queue.append((next_coords, path + [dir]))
            if len(path) > 150:
                break
        return None


def get_victory_plan(file: str):
    board = get_board(file)
    start_points = get_start_points(board)

    while True:
        ranger = Ranger(start_points, board)
        reduced_coords, phase1_path = ranger.explore_uncertainty(limit=20)
        phase2_path = ranger.bfs(reduced_coords)
        if phase2_path:
            return phase1_path + phase2_path  # pełna ścieżka


if __name__ == "__main__":
    plan = get_victory_plan("zad_input.txt")
    path_str = "".join(plan)
    print("Zwycięski plan:")
    print(path_str)

    with open("zad_output.txt", "w") as file:
        file.write(path_str + "\n")