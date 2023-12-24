from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from others import And, Or
    
class Formula:
    def __init__(self, exp) -> None:
        self.exp = exp
    
    def oblicz(self, zmienne):
        return self.exp.oblicz(zmienne)
    
    def __add__(self, other) -> 'Formula':
        return And(self, other)
    
    def __mul__(self, other) -> 'Formula':
        return Or(self, other)
    
    def tautologia(self):
        pass
    
    def simplify(self):
        pass
    
    def print(self):
        print(self.exp)
    

    
    
