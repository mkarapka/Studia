import numpy as np
import random

board = np.array([[1,1,1,1], [2,3,4,5] ,[3,3,3,3], [4,4,4,4]])
x = np.array([1,3])
y = np.array([1,1])

UDLR = np.array([(0, 1), (0, -1), (-1, 0), (1, 0)])
# print(x + y)
# print(board[*x])

for m in UDLR:
    print(x + m)
    
print(random.choice(board))

l = "############"
print(list(l))

dl = ["a", "b"]
d = {"a": 1, "b": 2}
print(d[random.choice(dl)])