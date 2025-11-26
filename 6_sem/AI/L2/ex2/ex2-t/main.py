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
        if board[y][x] == "S"
    ]


class Ranger:
    def __init__(self, start_points: np.array, board: np.array):
        self.coords = random.choice(start_points)
        self.board = board
        self.UDLR = {
            "UP": np.array((1, 0)),
            "DOWN": np.array((-1, 0)),
            "LEFT": np.array((0, -1)),
            "RIGHT": np.array((0, 1)),
        }

        self.prev_board = [
            ["##" if line[i] == "#" else "  " for i in range(len(board[0]))]
            for line in board
        ]

    def check_position(self, coords):
        field = self.board[*coords]
        # print(field)
        if field == "#":
            return "Wall"
        if field == "G" or field == "B":
            return "Goal"
        return "Empty"

    def guess_direct(self, curr_coords, next_coords) -> str:
        step = tuple(next_coords - curr_coords)  # Zamiana na krotkę dla bezpieczeństwa

        if step == (1, 0):  # Ruch w dół
            return "D"
        if step == (-1, 0):  # Ruch w górę
            return "U"
        if step == (0, -1):  # Ruch w lewo
            return "L"
        if step == (0, 1):  # Ruch w prawo
            return "R"
        return ""

    def bfs(self):
        counter = 0
        queue = [(self.coords, "")]
        visited = set()

        val = 0
        curr_coords = (-1, -1)
        self.prev_board[self.coords[0]][self.coords[1]] = "SS"
        while queue and counter < 150:
            prev = curr_coords
            curr_coords, path = queue.pop(0)
            if not tuple(curr_coords) in visited:
                self.prev_board[curr_coords[0]][curr_coords[1]] = (
                    str(val) + " " if len(str(val)) == 1 else str(val)
                )
                val += 1
            visited.add(tuple(curr_coords))
            field = self.check_position(curr_coords)

            rand_direct = random.choice(["UP", "DOWN", "LEFT", "RIGHT"])
            rand_step = self.UDLR[rand_direct]
            while field != "Wall" and field != "Goal":
                prev = curr_coords
                curr_coords += rand_step

                field = self.check_position(curr_coords)
                if field != "Wall" and not tuple(curr_coords) in visited:
                    visited.add(tuple(curr_coords))
                    self.prev_board[curr_coords[0]][curr_coords[1]] = (
                        str(val) + " " if len(str(val)) == 1 else str(val)
                    )

                    path += rand_direct[0]

                    val += 1
                    counter += 1
            curr_coords -= rand_step

            if field == "Goal":
                self.prev_board[curr_coords[0]][curr_coords[1]] = "GG"
                return curr_coords, counter, path, self.prev_board

            for _, m in self.UDLR.items():
                next_coords = curr_coords + m
                if (
                    self.check_position(next_coords) != "Wall"
                    and not tuple(next_coords) in visited
                ):
                    direct = self.guess_direct(curr_coords, next_coords)
                    queue.append((next_coords, path + direct))

            counter += 1
        return None


def get_vitory_plan(file: str, iters=1):
    board = get_board(file)
    start_points = get_start_points(board)

    # print("ranger start", ranger.coords)
    plans = []
    # for _ in range(iters):
    while plans == []:
        # ranger =
        game = Ranger(start_points, board).bfs()
        if game:
            plans.append(game)
    # print(len(plans))
    print(board)
    return min(plans, key=lambda x: x[1])


if __name__ == "__main__":
    victory_plan = get_vitory_plan("zad_input.txt")
    vic = victory_plan
    print(vic[:-2])
    with open("out.txt", "w") as file:
        for i in range(len(vic[-1][0])):
            file.write(f"---{i}--- ")
        file.write("\n")
        for line in vic[-1]:
            file.write(str(line) + "\n")

    print(vic[-2])
