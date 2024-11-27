# Zadanie 1 z rzutowaniem na decimal
from decimal import Decimal

def vat_faktura(lst):
    lst_sum = 0
    for i in range(len(lst)):
        lst_sum += lst[i]
    return lst_sum + lst_sum * Decimal(0.23)

def vat_paragon(lst):
    lst_sum = 0
    for i in range(len(lst)):
        lst_sum += lst[i] + lst[i] * Decimal(0.23)
    return lst_sum

zakupy = [100.50, 45.25, 67.75, 120.00, 89.99, 50.75]

for i in range(len(zakupy)):
    zakupy[i] = Decimal(zakupy[i])


print(vat_faktura(zakupy) == vat_paragon(zakupy))
