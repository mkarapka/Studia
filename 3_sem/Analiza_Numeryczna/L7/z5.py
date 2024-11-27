def frac(n):
    if n == 0:
        return 1
    return n * frac(n - 1)
def subpoint_1():
    n = 0
    while frac(n+1) < pow(10, 12):
        n += 1
    return n

def subpoint_2():
    n = 0
    while frac(n+1) * pow(2, 2*n-1) < pow(10, 12):
        n += 1
    return n
print("Podpunkt 1: ", subpoint_1())
print("Podpunkt 2: ", subpoint_2())