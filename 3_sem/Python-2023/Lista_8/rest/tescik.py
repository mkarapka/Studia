def fun(val1, val2, val3):
    return val1 + val2 + val3


lista = range(10)

for i in range(len(lista) - 2):
    print(fun(*lista[i : i + 3]))
