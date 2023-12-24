def draw_square(x, y, color):
    print(x, y)
    ax.add_patch(plt.Rectangle((x, y), 1, 1, fc=color))