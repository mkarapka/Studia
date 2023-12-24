import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

size = 10
row, col = size, size

board = np.ones((row, col), dtype=int)
ant_pos = np.array([row // 2, col // 2])
colors = {1: "white", 0: "black"}

directions = np.array([
    [0, -1],
    [1, 0],
    [0, 1],
    [-1, 0]
])

step = 2
flag = False

fig, ax = plt.subplots()
ax.set_xlim(0, col)
ax.set_ylim(0, row)
ax.set_aspect("equal", adjustable="box")


def draw_square(x, y, color):
    ax.add_patch(plt.Rectangle((x, y), 1, 1, fc=color))


def draw_squares(ant_x, ant_y):
    for x in range(size):
        for y in range(size):
            if x != ant_x or y != ant_y:
                draw_square(x, y, colors[board[x, y]])


def set_board():
    global step, ant_pos, board, directions, size, colors
    if board[ant_pos[0], ant_pos[1]] == 1:
        board[ant_pos[0], ant_pos[1]] = 0
        step = (step + 1) % 4
    else:
        board[ant_pos[0], ant_pos[1]] = 1
        step = (step - 1) % 4

    ant_pos = (ant_pos + directions[step]) % size


def update(t):
    global ant_pos, board, colors, directions, flag
    if flag:
        draw_squares(*ant_pos)
        flag = False
    else:
        draw_square(*ant_pos, colors[board[ant_pos[0], ant_pos[1]]])
        set_board()


def jump_steps(n):
    global flag
    for _ in range(n):
        set_board()
    flag = True


# jump_steps(10_500)

ani = animation.FuncAnimation(fig, update, frames=5, interval=200, repeat=True)
plt.show()
