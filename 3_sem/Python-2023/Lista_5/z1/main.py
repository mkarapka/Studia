from formula import *
dictionary = {"p": False, "q": True, "r": False}

form = Formula(And(Not(Stala(True)), Stala(True)))
form2 = Formula(Stala(True))
form3 = Formula(Or(Stala(True), Or(Zmienna("q") , Zmienna("p"))))
com_form = And(Or(Stala(True), Stala(False)), Not(Stala(False)))

print("f1:", str(form), "f2:",str(form2))
print("f1+f2:", str(form + form2))
print("(f1+f2)*f3:", str((form + form2) * form3))
print("f before silmplify:", str(com_form))
print("and after:", str(com_form.simplify()))
print("check f3 is tautology:", form3.tautology())
print("check f1 is tautology:", form.tautology())
print(f"value of f3:", form3.calculate(dictionary))