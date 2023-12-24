from formula import Formula

class And(Formula):
    def __init__(self, left, right) -> None:
        self.left = left
        self.right = right
        
    def oblicz(self, zmienne):
        return self.left.oblicz(zmienne) and self.right.oblicz(zmienne)
    
class Or(Formula):
    def __init__(self, left, right) -> None:
        super.__init__(left)
        self.right = right
        
    def oblicz(self, zmienne):
        return self.left.oblicz(zmienne) or self.right.oblicz(zmienne)
        
class Not(Formula):
    def __init__(self, exp) -> None:
        self.exp = exp
        
    def oblicz(self, zmienne):
        return not self.exp.oblicz(zmienne)
        
# class Implies(Formula):
#     def __init__(self, left_exp, right_exp) -> None:
#         super().__init__(f"{left_exp} Implies {right_exp}")
        
# class Equiv(Formula):
#     def __init__(self, left_exp, right_exp) -> None:
#         super().__init__(f"{left_exp} Equiv {right_exp}")

class Zmienna(Formula):
    def __init__(self, exp) -> None:
        self.exp = exp
        
    def oblicz(self, zmienne):
        return zmienne[self.exp]
        
class Stala(Formula):
    def __init__(self, exp) -> None:
        self.exp = exp
        
    def oblicz(self, zmienne):
        return self.exp