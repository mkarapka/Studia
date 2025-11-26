from collections import deque
import heapq

# Constants
DIRECTIONS = "LRUD"
DIRS = [(0, -1), (0, 1), (-1, 0), (1, 0)]

# Globals
board = [[False]*30 for _ in range(30)]
goal_distance = [[float('inf')]*30 for _ in range(30)]
y_size = x_size = 0
starting_positions = set()
goal_positions = set()


def read_input():
    global y_size, x_size
    with open("zad_input.txt") as f:
        lines = f.readlines()

    y_size = len(lines)
    x_size = len(lines[0].strip())

    for row, line in enumerate(lines):
        for col, char in enumerate(line.strip()):
            if char == 'B':
                starting_positions.add((row, col))
                goal_positions.add((row, col))
            elif char == 'G':
                goal_positions.add((row, col))
            elif char == 'S':
                starting_positions.add((row, col))
            elif char == '#':
                board[row][col] = True


def print_result(moves):
    with open("zad_output.txt", "w") as f:
        f.write(moves + "\n")


def safe(pos):
    y, x = pos
    return 0 <= y < y_size and 0 <= x < x_size


def available(pos):
    y, x = pos
    return safe(pos) and not board[y][x]


def move(pos, dir):
    dy, dx = DIRS[dir]
    new_pos = (pos[0] + dy, pos[1] + dx)
    return new_pos if available(new_pos) else pos


def make_move(positions, dir):
    return {move(pos, dir) for pos in positions}


def calc_dist_from_goals(start):
    vis = [[False]*30 for _ in range(30)]
    q = deque([(start, 0)])
    vis[start[0]][start[1]] = True

    while q:
        (y, x), d = q.popleft()
        goal_distance[y][x] = min(goal_distance[y][x], d)

        for dy, dx in DIRS:
            ny, nx = y + dy, x + dx
            new_pos = (ny, nx)
            if available(new_pos) and not vis[ny][nx]:
                vis[ny][nx] = True
                q.append(((ny, nx), d + 1))


def calc_distance_array():
    for pos in goal_positions:
        calc_dist_from_goals(pos)


def dist(positions):
    return max(goal_distance[y][x] for y, x in positions)


def win(positions):
    return all(pos in goal_positions for pos in positions)


def main():
    read_input()
    calc_distance_array()

    start_state = ("", frozenset(starting_positions))
    heap = [ (dist(start_state[1]), start_state) ]
    visited = set()
    visited.add(start_state[1])

    while heap:
        _, (moves, positions) = heapq.heappop(heap)

        if win(positions):
            print_result(moves)
            return

        for i, d in enumerate(DIRECTIONS):
            new_positions = frozenset(make_move(positions, i))
            if new_positions not in visited:
                visited.add(new_positions)
                new_moves = moves + d
                heapq.heappush(heap, (dist(new_positions) + len(new_moves), (new_moves, new_positions)))


if __name__ == '__main__':
    main()
