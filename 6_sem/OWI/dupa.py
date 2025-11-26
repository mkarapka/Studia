import random

numbers = list(range(1, 58))

while len(numbers) > 0:
    n = random.choice(numbers)
    print(n, end="")
    numbers.remove(n)
    input()
