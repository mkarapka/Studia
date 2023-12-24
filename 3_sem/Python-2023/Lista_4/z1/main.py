from math import isqrt
from timeit import timeit

def isPrime(num):
    if num < 2:
        return False
    for factor in range(2, isqrt(num) + 1):
        if num % factor == 0:
            return False
    return True

def pierwsza_imperatywna(n):
    lst = []
    for i in range(n+1):
        if isPrime(i):
            lst.append(i)
    return lst

def pierwsza_skladana(n):
    return [i for i in range(n+1) if isPrime(i)]

def pierwsza_funkcyjna(n):
    return  list(filter(
        lambda x: isPrime(x),
        range(n+1)
    ))
    
def diff(var, var_1):
    return len(str(var)) - len(str(var_1))

def print_vals(lst):
    cat = "imperatywna"
    cat_1 = "składana"
    cat_2 = "funkcyjna"
    space = 10
    
    print("n    ", cat, " " * space, cat_1, " " * space,cat_2)
    for i in range(len(lst[0])):
        
        print((i+1)*10, " "*2, lst[0][i], end=" ")
        print(" " * (space - diff(lst[0][i], cat)), lst[1][i], end="")
        print(" " * (space - diff(lst[1][i], cat_1)+1), lst[2][i])
        
lst = [[], [], []] 
rd = 9   

for num in range(10, 100, 10):
    
    test_1 = timeit(lambda: pierwsza_imperatywna, number = num)
    test_2 = timeit(lambda: pierwsza_skladana, number = num)
    test_3 = timeit (lambda: pierwsza_funkcyjna, number = num)
    lst[0].append(round(test_1, rd))
    lst[1].append(round(test_2, rd))
    lst[2].append(round(test_3, rd))
    
print_vals(lst)
