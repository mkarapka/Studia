def factoral(n):
    if n == 0:
        return 1
    elif n == 1:
        return 1
    else:
        return n * factoral(n-1)
    
def newton(n, k):
    return factoral(n) / (factoral(k) * factoral(n-k))    

def all_combs(n):
    return sum([newton(n-k, k) for k in range(n//2+1)])
    
    
print(all_combs(6))
print(newton(6, 0))
print(newton(5, 1))
print(newton(4, 2))
print(newton(3, 3))
        
    
    