class Formula:
    def __init__(self, left, right=None) -> None:
        
        self.left = left
        self.right = right

        
        if right != None:
            self.right = right
        if self.left == None:
            raise ValueError("Left side of formula cannot be None")
        
    def calculate(self, zmienne):
        if type(zmienne) != dict:
            raise ValueError("Zmienne must be dictionary")
        return self.left.calculate(zmienne)
        
    def __add__(self, other) -> 'Formula':
        return Or(self, other)
    
    def __mul__(self, other) -> 'Formula':
        return And(self, other)
    
    def tautology(self):
        from itertools import product
        def generate_bin_seq(n):
            return [list(p) for p in product([0,1], repeat=n)]
        
        def one_or_two(fun, obj: Formula) -> any:
            if obj.right == None:
                return fun(obj.left)
            return fun(obj.left) + fun(obj.right)
            
        def all_vars(obj: Formula) -> any:
            if type(obj) == Zmienna:
                return [obj.left]
            
            elif type(obj) == Stala:
                return []
        
            else:
                return one_or_two(all_vars, obj)
            
        variables = dict.fromkeys(one_or_two(all_vars, self))
        cases = [dict(zip(variables, p)) for p in generate_bin_seq(len(variables))]
        
        for case in cases:
            if self.calculate(case) == False:
                return False
        return True
        
    def simplify(self):
        if type(self) == Stala:
            return self.left
        
        elif type(self) == And:
            if self.left.simplify() == False or self.right.simplify() == False:
                return False
            
            if self.left.simplify() == True:
                return self.right.simplify()
    
            if self.right.simplify() == True:
                return self.left.simplify()
            
            return And(self.left.simplify(), self.right.simplify())
        
        elif type(self) == Or:
            if self.left.simplify() == True or self.right.simplify() == True:
                return True
            
            if self.left.simplify() == False:
                return self.right.simplify()
    
            if self.right.simplify() == False:
                return self.left.simplify()
            
            return Or(self.left.simplify(), self.right.simplify())
        
        else:
            return self
        
    def __str__(self):
        if type(self) == Formula:
            return str(self.left)
        
        if type(self) == Stala or type(self) == Zmienna:
            return str(self.left)
        else:
            if self.right is None:
                return f"{self.__class__.__name__}({self.left})"
            
            return f"{self.__class__.__name__}({self.left}, {self.right})"

class And(Formula):
    def __init__(self, left, right) -> None:
        super().__init__(left, right)
        
    def calculate(self, zmienne):
        if type(zmienne) != dict:
            raise ValueError("Zmienne must be dictionary")
        return self.left.calculate(zmienne) and self.right.calculate(zmienne)
    
class Or(Formula):
    def __init__(self, left, right) -> None:
        super().__init__(left, right)
    
    def calculate(self, zmienne):
        if type(zmienne) != dict:
            raise ValueError("Zmienne must be dictionary")
        return self.left.calculate(zmienne) or self.right.calculate(zmienne)
        
class Zmienna(Formula):
    def __init__(self, left) -> None:
        super().__init__(left)
        
    def calculate(self, zmienne):
        try:
            return zmienne[self.left]
        except:
            raise ValueError(f"Variable {self.left} not found in dictionary")
     
class Not(Formula):
    def __init__(self, left) -> None:
        super().__init__(left)
    
    def calculate(self, zmienne):
        if type(zmienne) != dict:
            raise ValueError("Zmienne must be dictionary")
        return not super().calculate(zmienne)
    
class Stala(Formula):
    def __init__(self, left) -> None:
        super().__init__(left)
        
    def calculate(self, zmienne):
        return self.left