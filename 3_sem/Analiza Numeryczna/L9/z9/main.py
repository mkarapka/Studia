import matplotlib.pyplot as plt
import numpy as np
from module import list_of_points


def de_casteljau(p, n, t):
    W = [[0 for _ in range(n + 1)] for _ in range(n + 1)]
    for i in range(n + 1):
        W[i][0] = p[i]

    for j in range(1, n + 1):
        for i in range(n - j + 1):
            W[i][j] = (
                (1 - t) * W[i][j - 1][0] + t * W[i + 1][j - 1][0],
                (1 - t) * W[i][j - 1][1] + t * W[i + 1][j - 1][1],
            )
    return W[0][n]


def plot_bezier_curve(p, n):
    t_values = np.linspace(0, 1, num=100)
    bezier_points = [de_casteljau(p, n, t) for t in t_values]

    x_values = [point[0] for point in bezier_points]
    y_values = [point[1] for point in bezier_points]

    plt.plot(x_values, y_values)
    plt.show()


plot_bezier_curve(list_of_points, len(list_of_points) - 1)
