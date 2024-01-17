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
f3 = lambda x: math.sin(5 * x - pi / 3)
a = -3 * pi
b = pi / 6
args3 = [f3, a, b]


def romberg_method(fun, a, b, size=20):
    def trapez_method(fun, a, b, n):
        h = (b - a) / n
        t = h / 2 * (fun(a) + fun(b))
        
        for i in range(2**n):
            t += h * fun(a + i * h)
        return t

    def T_mk(m, T_m_1k1, T_m_1k):
        return (4**m * T_m_1k1 - T_m_1k) / (4**m - 1)

    romberg_table = np.zeros((size, size))

    # end = 0
    # for row in range(size):
    #     end += 1
    #     print(end)
    #     for col in range(end):
    #         if col == 0:
    #             romberg_table[row][col] = trapez_method(fun, a, b, 2**row)
    #         else:
    #             romberg_table[row][col] = T_mk(
    #                 col, romberg_table[row][col - 1], romberg_table[row - 1][col - 1]
    #             )
    
    # for row in range(size):
    #     print(row)
    romberg_table[size][0] = trapez_method(fun, a, b, 2**size)
    return romberg_table


print(romberg_method(*args1, 6))

