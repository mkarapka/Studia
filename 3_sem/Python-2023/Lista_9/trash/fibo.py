import matplotlib.pyplot as plt
import numpy as np

# Przygotowanie danych
x = np.arange(0, 10, 0.1)  # Zakres x od 0 do 10
y1 = np.sin(x)  # Przykładowa funkcja 1 (sinus)
y2 = np.cos(x)  # Przykładowa funkcja 2 (cosinus)

# Rysowanie wykresu
plt.plot(x, y1, label='sin(x)')  # Pierwsza funkcja
plt.plot(x, y2, label='cos(x)')  # Druga funkcja

# Dodanie etykiet i legendy
plt.xlabel('x')
plt.ylabel('y')
plt.title('Wykres dwóch funkcji')
plt.legend()

# Pokazanie wykresu
plt.show()
