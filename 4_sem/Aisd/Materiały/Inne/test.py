import math


def trapez_composite(f, a, b, n):
    h = (b - a) / n  # Szerokość podprzedziału
    sum = f(a) + f(b)

    # Suma wartości funkcji w środkach podprzedziałów
    for i in range(1, n):
        sum += 2 * f(a + i * h)

    return (h / 2) * sum


# To zjebałem, ale nie wiem dlaczego nie działa
def romberg(f, a, b, n):
    def trapeze_formula(f, a, b, n):
        h = (b - a) / 2**n
        s = 0.5 * (f(a) + f(b))
        for i in range(n):
            s += f(a + i * h)
        return s * h

    T = [trapeze_formula(f, a, b, j) for j in range(n)]


# Przykład użycia
f1 = lambda x: 2021 * x**5 - 2020 * x**4 + 2019 * x**2
f2 = lambda x: math.sin(x)
a = -1
b = 2
n = 17

a_1 = 0
b_1 = math.pi


integral = trapez_composite(f1, a, b, n)

print(f"Przybliżona wartość całki ∫[0, 1] x^2 dx: {integral}")
print(trapez_composite(f2, a_1, b_1, 4))
