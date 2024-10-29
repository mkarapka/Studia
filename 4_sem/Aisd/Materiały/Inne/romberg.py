import math


def romberg(f, a, b, n):
    def trapeze_formula(f, a, b, n):
        h = (b - a) / n
        s = f(a) + f(b)
        for i in range(n):
            s += 2 * f(a + i * h)

        return s * h / 2

    def T_mk(m, T_m1k1, T_m1k):
        return (4**m * T_m1k1 - T_m1k) / (4**m - 1)

    T = [trapeze_formula(f, a, b, j) for j in range(1, n + 1)]

    for i in range(1, n):
        m = i
        prev = T[i - 1]
        for j in range(i, n):
            tmp = T[j]
            T[j] = T_mk(m, T[j], prev)
            prev = tmp
    return T


def print_table(table):
    for i in range(len(table)):
        print(table[i])


f1 = lambda x: 2024 * x**8 - 1977 * x**4 - 1981
a = -3
b = 2
args1 = [f1, a, b]

f2 = lambda x: math.sin(x)
a_1 = 0
b_1 = math.pi
args2 = [f2, a_1, b_1]

t2 = romberg(*args2, 7)
print(t2[-1])
