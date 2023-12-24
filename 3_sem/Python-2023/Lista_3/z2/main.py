def prio(op):
    if op in "+-":
        return 0
    if op in "*/":
        return 1
    return -1

def operation(a, b, op):
    if op == '+':
        return a + b
    if op == '-':
        return a - b
    if op == '*':
        return a * b
    if op == '/':
        return a / b
    
def konwersja(infx_exp):
    stack = []
    onp_exp = []
    
    for var in infx_exp:
        
        if var == '(':
            stack.append(var)
            
        elif var == ')':
            while stack != [] and stack[-1] != '(':
                onp_exp.append(stack.pop())
            stack.pop()
            
        elif isinstance(var, int):
            onp_exp.append(var)
            
        else:
            while stack != [] and prio(stack[-1]) >= prio(var):
                onp_exp.append(stack.pop())
            stack.append(var)
            
    while stack != []:
        onp_exp.append(stack.pop())
        
    return onp_exp

def oblicz(onp_exp):
    stack = []
    while len(onp_exp) > 0:
        var = onp_exp[0]
        if not isinstance(var, int):
            a = stack.pop()
            b = stack.pop()
            stack.append(operation(b, a, onp_exp.pop(0)))
        else:
            stack.append(onp_exp.pop(0))
    return stack[0]        

test1 = ['(' , 5 , '+', 2 , ')' , '*' , 3]
test2 = [1, '+', 2, '*', '(', 3, '-', 4, ')']
test3 = [4, '*', 2, '+' , 3]

print("test1:", "ONP:", konwersja(test1), "wynik: ", oblicz(konwersja(test1)))
print("test2:", "ONP:", konwersja(test2), "wynik: ", oblicz(konwersja(test2)))
print("test2:", "ONP:", konwersja(test3), "wynik: ", oblicz(konwersja(test3)))