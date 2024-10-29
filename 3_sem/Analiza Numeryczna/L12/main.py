from math import cos, pi, sin

import matplotlib.pyplot as plt
import numpy as np

# a)
f1 = lambda x: 2024 * x**8 - 1977 * x**4 - 1981
a = -3
b = 2
args1 = [f1, a, b]

# b)
f2 = lambda x: 1 / (1 + x**2)
a = -3
b = 3
args2 = [f2, a, b]

# c)
f3 = lambda x: sin(5 * x - pi / 3)
a = -3 * pi
b = pi / 6
args3 = [f3, a, b]


def romberg_method(f, a, b, n=20):

    def sumbis(f, a, b, h):
        sum_var = 0.5 * (f(a) + f(b))
        while a < b:
            sum_var += f(a)
            a += h
        return sum_var

    def T_mk(m, T_m_1k1, T_m_1k):
        return (4**m * T_m_1k1 - T_m_1k) / (4**m - 1)

    table = np.zeros((n, n))

    for k in range(n):
        h = (b - a) / (2**k)
        table[k][0] = h * sumbis(f, a, b, h)

    for row in range(1, n):
        for col in range(1, row + 1):
            table[row][col] = T_mk(col, table[row][col - 1], table[row - 1][col - 1])

    return table


def print_table(table):
    for row in range(len(table)):
        for col in range(row + 1):
            print(f"{table[row][col]:.4f}", end=" ")
        print()
    print()


def print_diag(table):
    for i in range(len(table)):
        print(table[i][i])


# def print_table(table):
#     for i in range(len(table)):
#         print(table[i][0])


t1 = romberg_method(*args1, 10)
t2 = romberg_method(*args2, 20)
t3 = romberg_method(*args3, 20)

print_diag(t1)
