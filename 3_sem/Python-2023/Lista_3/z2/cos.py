def priority(op):
    if op in "+-":
        return 0
    if op in "*/":
        return 1
      
    
def is_operator(var):
    return var in "+-*/"

def check_ops(stack, arg_op):
    if len(stack) > 2:
        value = stack.pop()
        op = stack.pop()
        if priority(op) < priority(arg_op):
            stack.extend([value, arg_op, op])
        else:
            stack.extend([op, value, arg_op])
    else:
        stack.append(arg_op)
        
    return stack

def konwersja(infx_exp):
    stack = []
    i = 0
    while i < len(infx_exp) - 1:
        var = infx_exp[i]
        if is_operator(var):
            stack.append(infx_exp[i+1])
            stack = check_ops(stack,var)
            i += 2
        elif var == ')':
             return stack
        elif var == '(':
            res = konwersja(infx_exp[i+1:])
            if stack != []:
                res.append(stack[-1])
            stack = stack[:-1] + res
            i += len(res)
        else:
            stack.append(var)
            i += 1
    return stack
            
                
txt = "5 + 2 * 3 / 2 + 7 - 12 * 2 + 1 * 7 - 6" 
txt = "( 5 + 2 ) * 3"               
infx = txt.split()           
 
lst = ["4", "*", "2", "+" , "3"]
result = "5 2 3 * 2 / + 7 + 12 2 * - 1 7 * + 6 -"
cos = "5 2 3 * 2 / + 7 - 12 2 * + 1 7 * - 6 +"

k = []
print(konwersja(infx))
# print(k[-1])