def prio(op):
    if isinstance(op, int):
        return -1  # Return -1 for numeric operands
    if op in "+-":
        return 0
    if op in "*/":
        return 1

def check_ops(stack):
    while len(stack) > 2:
        value = stack.pop()
        op = stack.pop()
        op_1 = stack.pop()
        if prio(op_1) < prio(op):
            stack.extend([value, op_1, op])
        else:
            stack.extend([op_1, value, op])
    return stack

def konwersja(infx_exp):
    stack = []
    result = []
    operator = []
    
    while infx_exp:
        var = infx_exp.pop(0)
        if var == '(':
            if stack:
                operator = stack.pop()
            result.extend(stack)
            stack = []
        elif var == ')':
            stack += operator
            result += stack
            stack = []
        elif isinstance(var, int):
            stack.append(var)
            stack = check_ops(stack)
        else:
            stack.append(var)
    
    result.extend(stack)
    return result

infx_2 = [1, '+', 2, '*', '(', 3, '-', 4, ')']
lst = [4, '*', 2, '+' , 3]
result = "5 2 3 * 2 / + 7 + 12 2 * - 1 7 * + 6 -"
cos = "5 2 3 * 2 / + 7 - 12 2 * + 1 7 * - 6 +"

k = []
print(konwersja(infx_2))