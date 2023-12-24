def convert(exp):
    def priority(operator):
        if operator in ['+', '-']:
            return 1
        if operator in ['*', '/']:
            return 2
        return 0

    result = []
    stack = []

    for ch in exp:
        if isinstance(ch, int):
            result.append(ch)
        elif ch == '(':
            stack.append(ch)
        elif ch == ')':
            while stack and stack[-1] != '(':
                result.append(stack.pop())
            stack.pop()
        else:
            while stack and priority(stack[-1]) >= priority(ch):
                result.append(stack.pop())
            stack.append(ch)

    while stack:
        result.append(stack.pop())

    return result

txt = "( 5 + 2 ) * 3"    
          
infx_2 = [1, '+', 2, '*', '(', 3, '-', 4, ')']
lst = [4, '*', 2, '+' , 3]
result = "5 2 3 * 2 / + 7 + 12 2 * - 1 7 * + 6 -"
cos = "5 2 3 * 2 / + 7 - 12 2 * + 1 7 * - 6 +"

k = []
print(convert(infx_2))