from others import *
from formula import Formula

example = "~x Or (p And q)"      

form = Formula(And(Not(Stala(True)), Stala(True)))

form2 = Formula(Stala(True))

result = form + form2
dictionary = {"x": False}
print(result.oblicz(dictionary))