# Zadanie 5

Wpisy w tablicy będziemy uporządkowywać malejąco wględem długości prefiksu. 

### Dowód

 - Niech $x$ będzie dowolnym adresem IP, który próbujemy dopasować w tablicy routingu.  
Niech $y$ będzie pierwszym wpisem w tablicy, który pasuje do $x$, czyli pierwszym napotkanym wpisem, gdzie $x$ mieści się w jego zakresie.  

- Załóżmy nie wprost, że istnieje inny wpis $z$, który ma lepsze dopasowanie do $x$ niż $y$. 
Zatem:


$$\text{len}(z) > \text{len}(y)$$



- Skoro nasza tablica routingu jest posortowana malejąco względem długości prefiksów, to $z$ musi być przed $y$. 
- A skoro nasz algorytm wybiera **pierwszy pasujący wpis**, to $z$ musiałby zostać wybrany przed $y$ - **sprzeczność**