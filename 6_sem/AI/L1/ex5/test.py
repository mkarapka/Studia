import numpy as np

a, b = 0 , 3

for i in range(10):
    print(np.random.randint(a,b))
    
    
x = 0
y = 1

print(f"x = {x}, y={y}")
print(f"~x = {x ^ 1}, ~y={y ^ 1}")