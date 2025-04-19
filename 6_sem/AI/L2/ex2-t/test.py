import numpy as np
import random
def siema():
    for i in range(5):
        yield i

for n in siema():
    print(n)


board = np.array([[1,2,3], [1,2,3], [1,2,3]])
x = (1,1)
y = np.array(x)
z = (2,2)
print(board[*x])
print(type(x + y))
print("test numpy add:")
print(np.add(x, z))
print(type(np.add(x, z)))

print("Frozenset")
arr = [1,1,1,2,3,4,4,5,6,6]
f = frozenset(x for x in arr)
print(f)

d = {"a": 1, "b":2, "c": 3}
print(random.choice(list(d.items())))
