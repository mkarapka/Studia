import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np


size = 64
board = np.ones((size, size))
colors = {0: "black", 1: "white"}

# UP, RIGHT, DOWN, LEFT
directions = np.array([(0, 1), (1, 0), (0, -1), (-1, 0)])
step = 0
ant_pos = np.array([size // 2, size // 2])

fig, ax = plt.subplots()
ax.set_xlim(0, size)
ax.set_ylim(0, size)
ax.set_aspect("equal", adjustable="box")


def draw_square(x, y, color):
    ax.add_patch(plt.Rectangle((x, y), 1, 1, fc=color))


def update_ant_position():
    global ant_pos
    ant_pos += directions[step]
    ant_pos %= size


def update_board():
    global step
    if board[*ant_pos] == 1:
        step = (step + 1) % 4
        board[*ant_pos] = 0
    else:
        step = (step - 1) % 4
        board[*ant_pos] = 1


def draw_board():
    for x in range(size):
        for y in range(size):
            draw_square(x, y, colors[board[x][y]])


def update(t):
    update_board()
    draw_square(*ant_pos, colors[board[*ant_pos]])
    update_ant_position()
    draw_square(*ant_pos, "red")

def jump_moves(n):
    init_moves = n
    for _ in range(init_moves):
        update_board()
        update_ant_position()
        
jump_moves(10_600)
draw_board()
draw_square(*ant_pos, "red")


ani = animation.FuncAnimation(fig, update, frames=5, interval=200, repeat=True)
plt.show()
