

# Wykłady 
# 1. Premineralia 🤯 - TO-DO
## Podstawowe algorytmy i struktury danych 
Na razie pominę, bo mniej więcej ogaraniam o co chodzi, ale i tak ten dział jest do uzupełnienia 

### Sortowanie przez scalanie 

### Algorytm Euklidesa  + wersja rozszerzona

### Algorytmy przechodzenia grafu: DFS i BFS

#### DFS

#### BFS

### Algorytm Prima i Kruskala

### Algorytm Dijkstry 

### Algorytm Warshala-Floyda 

### Algorytm Forda-Fulkersona


# 2. Kopce 💩 TO-DO
## 2.1 Definicja


# 3. Zachłanne 🤑 TO-DO
## Definicja

## Konstrukcja minimalnego drzewa rozpinającego :evergreen_tree: 

### Algorytm Kruskala

### Algorytm Prima

### Algorytm Boruvki 

## Szeregowanie zadań

## Pokrycie zbioru 


# 4. Dziel i zwyciężaj ⚔️ TO-DO

## Definicja
Algorytmy typu **Dziel i zwycieżaj** (Devide and conquer) polegają na podzieleniu danego problemu $x$ na miniejsze podproblemy $x_k, k \in N$. Następnie wylicznone wyniki z podproblemów $x_k$ używamy do wyliczenia problemu $x$.
## Master Theorem 

Jest to bardzo mocne twierdzenie, które służy do oszacowania na podstawie zależności rekurencyjnej danego algorytmu $A$ jego złożoności. 
![image](https://hackmd.io/_uploads/SJYykxgG0.png)

## Sortowanie: 
### Mergesort (przez scalanie):
Algorytm polega na rekurencyjnym dzieleniu tablicy na dwie części, aż długość tej tablicy będzie $1$. Następnie będziemy scalać kolejne tablice tak, aby otrzymać nową tablicę w danym porządku.

Korzystamy tutaj z założenia, że tablica $A$ i $B$ są posortowane. Więc wystarczy przejechać liniowo po wszyskich elementach i połączyć dwie tablice. 

### Quicksort:

## Mnożenie bardzo dużych liczb (Karatsuba)

## Równoczesne znajdowanie minimum i maksimum w zbiorze

# 5. Dziel i zwyciężaj ⚔️⚔️ TO-DO

## Sieci przełączników 

## Para najbliżej położonych punktów


# 6. Programowanie dynamiczne 🧨  TO-DO
## Wstęp
W przypadku, kiedy podproblemy nie są **niezależne** od siebie metoda **Dziel i zwyciężaj** przestaję być optymalna, ponieważ możemy wyliczać wiele tych samych podproblemów, dlatego będziemy chcieli pamiętać ich stan.

## Definicja 
Dany problem $x$, dzielimy na mniejsze podproblemy $x_k$, których wyniki posłużą do obliczenia problemu $x$, dodatkowo dla każdego podproblemu pamiętamy jego stan. 

W każdym algorytmie dynamicznym będziemy używali tablicy $dp$.

## Dwumian Newtona - TO-DO
**Dane:** $n,k \in N$
**Wynik:** $\binom{n}{k}$

#### Wzór na dwumian
$$\binom{n}{k} = \frac{n!}{k! (n-k)!}$$

#### Zależność:
$$ \binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k} $$ 


Widzimy, że metoda dziel i zwyciężaj będzie  tutaj bardzo nieoptymalna, ponieważ wyliczalibyśmy wiele razy te same dwumiany newtona. 
![image](https://hackmd.io/_uploads/SkmbNzZMR.png)

Możemy spamiętywać wartości używając $2$-wymiarowej tablicy $dp$
![image](https://hackmd.io/_uploads/SJrTEGbMC.png)



## Optymalna trasa
**Dane:** plansza liczb **nieujemnych** postaci $\{a_{ij}\}$ o wymiarach $n$ x $m$ 

**Cel:** Przejść z pierwszej kolumny do ostatniej **minimalnym kosztem**

**Dozwolone ruchy:** 
- prawo
- prawo + góra
- prawo + dół

![image](https://hackmd.io/_uploads/rkLbRHlfR.png)

Skoro dla danego elementu $a_{ij}$ możemy iść na $a_{i+1j}$ albo $a_{ij+1}$ albo $a_{i-1j}$. To żeby znaleźć najmniejszy koszt ścieżki dla dowolnego $dp_{ij}$ wystarczy 

$$  dp[i][j]= 
\bigg\{ min \bigg(\begin{array}{cc} 
dp[i+1][j-1]
\\
dp[i][j-1]
\\
dp[i-1][j-1]
\end{array}\bigg) + value[i][j]
$$

Po wypełnieniu całej tablicy bardzo łatwo możemy wypisać  ciąg indeksów szukanej **optymalnej trasy**. 
Wystarczy wybrać **minimum** na ostatniej kolumnie, a natępnie dla każdego $dp[i][j]$ trzeba wybrać indeksy odpowiadające minimum z pośród wartości:

$$ k, l : dp[k][l] = min \bigg(\begin{array}{cc} 
dp[i+1][j-1]
\\
dp[i][j-1]
\\
dp[i-1][j-1]
\end{array}\bigg)
$$

### Złożoność
- Czasowa: $O(nm)$
- Pamięciowa: $O(nm)$

## LCS

## Optymalna kolejność mnożenia macierzy
 
# 7. Programowanie dynamiczne 🧨🧨 TO-DO

## Problem plecakowy

## CYK - na razie to pierdole ez

## drzewa rozpinające drabin

# 8. Dolne Granice ⬇️ TO-DO

## Definicja


# 9. Quicksort  🏃💨 TO-DO


# 10. Sortowanie 🔀 TO-DO


# 11. Problem Selekcji :point_right: 
## Definicja :book: 
Problem selekcji polega na znalezieniu $k$-tej **najmniejszej/największej** liczby z danego ciągu elementów $T[1...n]$ jak najbardziej efektywnie czasowo. 

Zakładamy dla naszego problemu (co nie wpływa na ogólność), że wszystkie elementy są różne. 


## 2. Proste przypadki :straight_ruler: 

1. $k = 1 \ \ => \ \ \theta(n)$
    Robimy po prostu $n-1$ porównań 
2. $k = 2 \ \ => \ \ \theta(n)$
    ### TO-DO
    
3. ***Przypadek ogólny*** $=> \theta(n)$
    Niżej omówimy sobie kilka różnych podejść rozwiązania tego problemu :sunglasses: 

## 3. Przypadek ogólny :sunglasses: :i_love_you_hand_sign: 

### Algorytm deterministyczny 

# 12 - Drzewa AVL:deciduous_tree: 
## BST (Binary search tree)
**Drzewo BST** to takie drzewo, gdzie dla każdego wierzchołka $w$, wszystkie wierzchołki w **lewym** poddrzewie będą od niego mniejsze, a w **prawym** większe.
![image](https://hackmd.io/_uploads/H13XkKZ-0.png)

## Wskaźnik balansu ⚖️
<span style="font-size: 24px;">${b = h_l - h_r}$</span>

gdzie $h_l$ to wysokość **lewego** poddrzewa, a $h_r$ **prawego**.

Drzewo jest **zbalansowane** gdy $b \in \{-1,0,1\}$

## Drzewo AVL 
jest to drzewo, które w **każdym wierzchołku** ma $b \in \{-1,0,1\}$.

### Wysokość drzewa AVL
<span style="font-size: 24px;">$h = 1.44 * \log_2 n$</span>

### Operacje słownikowe
Mamy 3 operacje:
- Wyszukiwanie - tak jak w drzewie BST
- Wstawianie 
- Usuwanie 

Te operacje możemy wykonać w czasie $O(\log n)$

Tylko te dwie ostatnie operacje mogą nam zaburzyć balans drzewa. Przywracaniem struktury drzewa będziemy nazywać **balansowaniem drzewa**, a do tego będziemy używali **rotacji**.
#### Rotacje 
Przykład dla $Rotacji(x)$
Strzałki **niebieskie** - relacje **przed** rotacją
Strzałki **czerwone**   - relacje **po** rotacji
![image](https://hackmd.io/_uploads/rJtJh7_bC.png)


Skoro mamy porządek jak w BST to wszystkie elementy w poddrzewie z korzeniem $x$ są mniejsze niż $y$. 

Zatem przywracając balans ustawimy **prawy** wskaźnik $x$-a na $y$, **lewy** wskaźnik $y$ na $x$ i dodatkowo ustawimy $x$ jako **korzeń** całego poddrzewa. W ten sposób nadal mamy zachowany porządek drzewa **BST** i mamy przywrócony balans.

Analogicznie robimy dla rotacji w drugą stronę, czyli jeśli $x$ byłby w prawym poddrzewie.

### Wstawianie elementu
Załóżmy, że wstawienie $x$ spowodowało zwiększenie wysokości lewego poddrzewa.

**Oznaczenia:**
- Niech $M$ - najniższy wierzchołek, w którym został zaburzony balans po wstawieniu $x$.
- Niech $L$ - korzeń tego poddrzewa

Rozpatrujemy 2 przypadki: 
1. Zwiększyła się wysokość **lewego** poddrzewa $L$
2. Zwiększyła się wysokość **prawego** poddrzewa $L$

Oznaczenia:
- **kropka**: lewe i prawe podrzewo mają tą samą wysokość
- **minus**: lewe podrzewo jest większe od prawego
 
#### Przypadek 1
![image](https://hackmd.io/_uploads/r1AG0X_-A.png)


#### Przypadek 2
![image](https://hackmd.io/_uploads/r1Qfi7OW0.png)
![image](https://hackmd.io/_uploads/SyIms7OZC.png)


### Usuwanie elementu

# 13. B-Drzewa - TO-DO

# 14. Drzewa czerwono-czarne - TO-DO

# 15. Kopce dwumianowe - TO-DO

# 16. Kopce fibonacciego - TO-DO

# 17. Union Find - TO-DO
