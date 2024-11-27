from math import ceil
import matplotlib.pyplot as mpt
import numpy 

# Wielomian
def polynomial(arg, x_list):
    result = 1
    for x in x_list:
        result *= (arg - x)
    return result

# Węzły Czebyszewa w przedziale [-1, 1]
def chebyshev_nodes(n):
    return numpy.cos((2 * numpy.arange(1, n + 2) - 1) * numpy.pi / (2 * (n + 1)))

# Węzły równoodległe w przedziale [-1, 1]
def equidistant_nodes(n):
    return numpy.linspace(-1, 1, n + 1)

def draw(start, end, in_row):
    figure, axis = mpt.subplots(ceil((end-start)/in_row), in_row)

    for n in range(start, end + 1): 
        x_values = numpy.linspace(-1, 1, 1000)  # Dla płynniejszego wykresu

        # Rysowanie wykresu dla węzłów Czebyszewa
        y_chebyshev = [polynomial(arg, chebyshev_nodes(n)) for arg in x_values]
        axis[(n-start)//in_row, (n-start)%in_row].plot(x_values, y_chebyshev, label=f'Czebyszew, n={n}', linestyle='--')

        # Rysowanie wykresu dla węzłów równoodległych
        y_equidistant = [polynomial(arg, equidistant_nodes(n)) for arg in x_values]
        axis[(n-start)//in_row, (n-start)%in_row].plot(x_values, y_equidistant, label=f'Equidistant, n={n}')

        # Dodanie etykiet i legendy
        axis[(n-start)//in_row, (n-start)%in_row].set_xlabel('x')
        axis[(n-start)//in_row, (n-start)%in_row].set_ylabel('p(x)')
        axis[(n-start)//in_row, (n-start)%in_row].set_title(f'Comparison for n = {n}')
        figure.subplots_adjust(hspace=0.5, wspace=0.5)
   
    mpt.show()

 
draw(5, 20, 4)