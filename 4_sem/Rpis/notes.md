<!-- @format -->

# Wykłady

- [ ] Pojęcie prawdopodobieństwa, przestrzeń zdarzeń, pojęcie zmiennej losowej, jej rozkład i charakteryzacja.

- [ ] Zmienne losowe dyskretne (rozkłady: Bernoulliego, geometryczny, Poissona, hipergeometryczny).

- [ ] Zmienne losowe ciągłe (rozkłady: jednostajny, wykładniczy, gamma, normalny, beta, Weibulla). Charakterystyki zmiennych losowych - momenty.
- [ ] Rozkłady zmiennych losowych wielowymiarowych (rozkład dwuwymiarowy, rozkład warunkowy, rozkład brzegowy, niezależność dwóch zmiennych losowych); Macierze kowariancji i korelacji. Wielowymiarowy rozkład normalny i szczególny przypadek dwuwymiarowy(elipsa koncentracji, proste regresji).
- [ ] Funkcje od dwuwymiarowych zmiennych losowych. Wyznaczanie gęstości i dystrybuanty funkcji zmiennych losowych.
- [ ] Funkcja charakterystyczna i jej własności. Związek funkcji charakterystycznej z momentami zmiennej.
- [ ] Populacja i próbka. Rozkłady próbkowe (chi-kwadrat, t-Studenta, F-Snedecora). Centralne twierdzenie graniczne.
- [ ] Estymacja punktowa i przedziałowa. Testowanie hipotez statystycznych. Weryfikacja zgodności rozkładów.
- [ ] Regresja liniowa i inne rodzaje regresji.
- [ ] Różne rodzaje analizy wariancji i związek tejże z regresją.
- [ ] Nierówności (Markova, Czebysheva, Chernoffa).
      Wprowadzenie do łańcuchów Markova.

# Wykład 1

## Prawdopodobieństwo

- $\Omega$ - zbiór możliwych zdarzeń elemetarnych
- **elementy** $\Omega$ - zdarzenia elemetarne
- $A \subseteq \Omega$ - zadarzenie
- $\varnothing$ - zdarzenie niemożliwe
- $A'$ lub $A^c$ - zdarzenie przeciwne do $A$
- $A \cap B$ - jednoczesne zajście $A$ i $B$
- $A \cup B$ - zajście **co najmniej** 1 z nich
- $A \cap B$ - zdarzenia $A$ i $B$ się wykluczają.

### Def. 1.1 - Prawdopodobieństwo dyskretne skończone

to funkcja $P$, która przyporzątkowuje każdemu zdarzeniu elementarnemu $w_i$

$P(w_i) >=0, \ dla \ i = 1,2,...,n$
oraz $\sum_{i=0}^nP(w_i) = 1$

Dla dowolnego zdarzenia $A \subset \Omega$. $ppb$ określamy jako $P(A) = \sum_{i:w_i \in A} P(w_i)$

Przyjmujemy, że $P(w_i) = \frac{1}{n} \ dla \ i = 1,2,...,n$

Stąd mamy wzór na $ppb$: $P(A) = \frac{|A|}{|\Omega|}$

## Przestrzeń probabilitstyczna

## Zmienna losowa

### $\sigma$-ciało borelowskie

### Co to ta zmienna losowa?

## Ciągłe i dyskretne zmienne losowe

### Ciągła zmienna losowa

### Dyskretna zmienna losowa

## Charakterystyki zmiennej losowej

### Wartość oczekiwana

#### P. dyskretny

#### P. ciągły

### Wariancja

#### P. dyskretny

#### P. ciągly

### Moment zwykły rzędu $k$ zmiennej losowej $X$

### Moment centralny rzędu $k$ zmiennej losowej $X$

### Dystrybuanta

# Wykład 2 - TO-DO

## Funkcja gętstości itd

# Wykład 3 - TO-DO

## Przykładowe zadania

# Wykład 4 - TO-DO

## Dwuwymiarowa zmienna losowa

# Wykład 5 - TO-DO

## Funkcja generująca momenty - MGF

## Rozkład normalny

# Wykład 6 - TO-DO

## Dalej MGFy

## Wielowymiarowy rozkład normalny

# Costam

## Przestrzeń problabilistyczna

Jest to taki obiekt $(\Omega, \mathcal{F}, P)$, który składa się z 3 elementów

- $\Omega$: przestrzeń zdarzeń elementarnych
- $\mathcal{F}$: rodziny zdarzeń czyli $P(\Omega)$
- Funkcji prawdopodobieństwa $P$

## Zmienna losowa

Zmienna losowa, jest to taka funkcja
$$ X: (\Omega, \mathcal{F}, P) \rightarrow \real $$
która spełnia warunek
$$ \{\omega : X(\omega) <= a \} \in \mathcal{F}$$

### Przykład zmiennych losowych w doświadczeniach

- Wysokość wygranej na loterii
- Liczba wypadków drogowych w danym weekendzie
- Suma współrzędnych punktów trafioncnych na tarczy

Prościej umując zmienna losowa jest to taka funkcja która z elementów rodziny zbiorów $\mathcal{F}$ zwraca wartości rzeczywiste.

## Dystrybuanta

Dystrybuanta zmiennej losowej $X$ - jest to taka funkcja

$$ F: \real \rightarrow [0,1] $$
$$ F(x) = P(\{\omega : X(\omega)\ <= x\}) $$

W skrócie
$$ F(x) = P(X <= x) $$

Czyli dystrubuanta określa nam prawdopodobieństwo zajścia, że **zmienna losowa** $X$ będzie $<=$ od danej wartości $x$.

Dystrybuanta określa rozkład zmiennej losowej

## Rozkład zmiennej losowej

Jest to zakrest wartości i prawdopodobieństwa z jakim zmienna losowa jest przyjmowana.

# Niezależność zmiennych losowych

Niech $\mathcal{H}$ będzie rodziną zmiennych losowych, określonych na wspólnej przestrzeni probabilistycznej.

Jeśli:

- dla dowolnej skończonej podrozdziny $\{X_1, X_2, ..., X_n\} \sub \mathcal{H}$
- i dowolnych $x_1, x_2, ..., x_n \in \mathbb{R}$

i zachodzi:

$$ P(X*1 <= x, X_2 <= x_2, ... , X_n <= x) = \prod^k*{i = 1} P(X_i <= x_i) $$

## Przykład

Mamy do pewien kwadrat $[0,1] \times [0,1]$
Oraz funkcję $S(A)$, która dla danych współżednych zwraca pole.

Niech $X$ - zmienna losowa odpowiadająca wartością $x$-a
$Y$ - zmienna losowa odpowiadająca wartością $y$-a

Widzimy wtedy, że zachodzi
$$ P(X <= a, Y <= b ) = S(\{(x,y) : x <= a, y <= b \}) = a _ b = P(X <= a) _ P(Y <= b) $$

## Zmienne losowe dyskretne

Wśród zmiennych losowych wyróżniamy dwie klasy:

- zmienne losowe dyskretne
- zmienne losowe z gęstością(chyba to inaczej zmienne losowe ciągłe, ale nie jestem pewnien)

### Zmienna losowa dyskretna

Jest to zmienna losowa $X$ z przestrzeni problablistycznej, która przyjmuję skończoną lub przeliczalną ilość wartości.

Ciąg par $\{(x_i,p_i), \ i = 1,2, ... \}$ nazywamy **rozkładem zmiennej losowej** $X$

Dystrybuanta zmiennej losowej dyskretnej jest funkcją schodkową mającą skoki wielkości $p_i$

![image](https://hackmd.io/_uploads/B1v62PGfA.png)
