# Listy

# Lista 0

# Lista 1

## Zadanie 1 - DO POPRAWY!!! (ZA DUŻA ZŁOŻONOŚĆ)
![image](https://hackmd.io/_uploads/ryOA9WMpa.png)


**a)**
k = korzeń w T
k = (l, v, r) 

```python
c_all(k):
    jeżeli r = null i l = null:
        zwróc 1
    jeżeli l = null:
        zwróć c_all(r) + 1
    wpp
        zwróć c_all(l) + c_all(r) + 1
```
Złożoność $O(2^n)$

**b)**
```javascript
k - korzeń w T
k = (l, v, r)
max_len(v):
    jeżeli r = null i l = null:
        zwróć 0
    jeżeli l = null:
        zwróć max_len(l) + 1
    wpp
        left = max_len(l) + 1
        right = max_len(r) + 1
        
        jeżeli left>right:
            zwróć left
        zwróć right
        
max_T_len(k):
    jeżeli r = null i l = null:
        zwróć 0 
    jeżeli l == null:
        zwróć max_len(r) + 1
    wpp
        zwróć max_len(r) + max_len(l) + 1

```
Złożoność $O(2^n)$


## Zadanie 2


## Zadanie 3 - DO POPRAWY(TRZEBA SZEREGOWAĆ LEKSYKOGRAFICZNE I TOPOLOGICZNIE)
![image](https://hackmd.io/_uploads/SyEUVdGap.png)

```python= 
S = stos
visited = []
mDFS(v):
    add v to visited
    for each u in v.neighbours
        if u not in visited
            mDFS(u)
    add v to S
    
for each v in G:
    if v not in visited:
        mDFS(v)
```
Złożoność$O(|V| + |E|)$

### Zadanie 4 - BŁĄD, ZŁOŻONOŚĆ N! ORAZ ŹLE PRZECZYTANE POLECENIE
![image](https://hackmd.io/_uploads/ByRdtOzpT.png)

```python=
N = dictionary
for each vertex u != v:
    p = find by dijkstra algorithm the shortest
    path from u to v
    
    N[u] = c(p)
    
R = stack 
visited = []

def find(u, min, d, visited):
    if u == v:
        add d to R
        return 0
    add u to visited
    for each w in u.neighbours 
        if w not in visited:
            if N[w] < min:
                add w to d
                min = N[w]
                find(w, min, visited)
                
find(u, inf, [], visited)
```

## Zadanie 5
![image](https://hackmd.io/_uploads/HJ3Icdzap.png)
### Idea
* Cel: droga największej długości
Dla każdego wierzchołka $v$, jeśli nie jest odwiedzony będziemy wywłoływać zmodyfikowanego rekurencyjnego $DFS$

* Dla każdego wierzchołka będziemy go dodawać na stos  oraz sprawdzać każdego sąsiada $v$, niech będzie to $u$, czyli jeśl $u$ jest odwiedzone, to będziemy brać $max$ wartość ścieżki od niego, jeśl nie to wywołamy rekurencyjego $dfs$.
Do otrzymanego wyniku dodamy 1 bo to jest nasza krawędź wchodząca do $u$. 

* Na koniec trzeba będzie porównać otrzymaną maksymalną wartość i porównać je z konkretnymi zmiennymi, którym zmienimy stan, jeśli spełnione będą określone warunki.

**a)**
```python=
maxG = 0
visited = stack

def mDFS(v):
    add v to visited
    max = 0
    for each u in v.neighbours:
        if u not in visited:
            val = mDFS(u) + 1
        else:
            val = u.max + 1
            
        if val > max:
            max = val
            
    if max > v.max:
        v.max = max
        
    if max > maxG:
        maxG = max
    return max
    
for each v in G:
    if v not in visited:
        mDFS(v)
return maxG
```
Złożoność $O(|V| + |E|)$

### Dowód:
Indukcja po $n$-długości największej ścieżki $v$
weźmy dowolny wierzchołek $v$
* $n = 0$
Od $v$ nie wychodzą żadne krawędzie, zatem najdłuższa ścieżka ma długość 0

* Weźmy dowolne $n$ i założmy, że dana własność zachodzi dla wierzchołka $v$. Dołożmy krawędź $(u,v)$ gdzie $u$ nie należy od najdłuższej ścieżki z $v$. Widzimy wtedy, że najdłuższa ścieżka z $u$ BSO idzie przez $v$.

**b)**
### Idea
Podobnie postępujemy jak z zadaniem poprzednim tylko będziemy dodatkowo przechowywać globalnie stan maksymalnej ścieżki oraz lokalnie w $DFS$ konkretną maksymalną ścieżkę dla danego wierzchołka. 

```python=
maxG = 0
visited = []
longestpath = []

def mDFS(v):
    add v to visited
    max = 0
    path = []
    for each u in v.neighbours:
        if u not in visited:
            val, uPath = mDFS(u) + 1
        else:
            val = u.max + 1
            uPath = u.path
        
        if val > max:
            max = val
            path = [v] + uPath
            
    if max > v.max:
        v.max = max
        v.path = path
        
    if max > maxG:
        maxG = max
        longestPath = path
    return max, path

for each v in G:
    if v not in visited:
        mDFS(v)

print(longestPath)

```
Złożoność $O(|V| + |E|)$

## Zadanie 6
![image](https://hackmd.io/_uploads/rkdhKKMpp.png)

Dzielimy ciąg na dwie tablice $L$ i $R$ o długościach $\lfloor \frac{n}{2} \rfloor$ i $\lceil \frac{n}{2} \rceil$

```python=
i = 0 
j = 0
licznik = 0
while i < floor(n/2):
    if 2L[i] <= R[j]:
        licznik += 1
        i += 1
    j+= 1
return licznik
```
Złożoność $O(n)$



## Zadanie 7 - poprawić
![image](https://hackmd.io/_uploads/Bkn6alapp.png)

```python=
T = stack

Vs = V/{v1,v2, ... vk}

dist = len(V) x len(V) <- inf

for each edge {u, v} in Vs:
    if u == v:
        dist[u][v] = 0
    else:
        dist[u][v] = c({u,v})

for u in Vs:
    for v1 in Vs:
        for v2 in Vs:
            # jezeli suma najkrotszych sciezek do u jest krotsza niz najkrotsza
            # sciezka z v1 do v2 to jest ona nowa najkrotsza sciezka z v1 do v2
            d[v1][v2] = min(d[v1][v2], d[v1][u] + d[u][v2])
D = 0
for u in Vs:
    for v in Vs:
        if u != v:
            D+=dist[u][v]
D = D/2
add D to T
for j = k, k-1, ..., 1:
    add vj to Vs
    for v1 in Vs:
        for v2 in Vs:
            d[v1][v2] = min(d[v1][v2], d[v1][vj] + d[vj][v2])

    D = 0
    for u in Vs:
        for v in Vs:
            if u != v:
                D+=dist[u][v]
    D = D/2
    add D to T
```
Złożoność $O(|V|^3)$

## Zadanie 8
![image](https://hackmd.io/_uploads/H1BlRepaa.png)
```python=       
#{
m = -inf 
r = inf
ind = [1] * k
PQ = []
for i in range(k):
    PQ.push(Li[0], i)
    m = max(m, Li)
                    #} = O(klog(k))
        
        
while PQ:        #{
    a, i = PQ.pop()
    r = min(m-a, r)
    if ind[i] < len(Li):
        x = Li[ind[i]]
        ind[i]++
        m = max(m, x)
        PQ.push(x, i)
        #} = O(n log(k)) - gdzie n to suma wszystkich 
        #                  elementów z list 
    
```
Złożoność $O(klog(n) + nlog(k)) = O(n log(k))$

# Lista 2 
## Zachłanne

## Zadanie 2 - zrobione

## Zadanie 3 - zrobione

## Zadanie 4 - trzeba poprawić
![image](https://hackmd.io/_uploads/rJZSU5V0T.png)

```python=
Dane: n
def coin_change_fib(n):
    R = stack
    f1 = 1
    f2 = 1
    while f2 < n:
        tmp = f2 
        f2 = f2 + f1 
        f1 = tmp

    while n > 0:
        if f1 <= n:
            n -= f1
            add f1 to stack
        tmp = f1 
        f1 = f2 - f1
        f2 = tmp
    return stack
```
**Złożoność**
$O(n)$
jednak $O(\log{k})$ - wyjaśnić dalczego

**Dowód poprawności:**
Niech $P(n)$ będzie taką własnością, że każda liczba $k \in N_+ <= n$ można zapisać jako suma różnych liczb fibonacciego.

* **Baza:**
    n = 1
    Mamy tylko jedną liczbę fibonacciego $F_1 = 1$
* **Krok:**
    Załóżmy, że zachodzi $P(n)$
    Cel: Zachodzi $P(n+1)$
    
    Weźmy największą liczbę fibonacciego $< n + 1$ i nazwijmy ją $x$
    Skoro $x >= 1$, to: 
    $n + 1 - x = y <= n$
    
    Z zał. ind zachodzi $P(y)$. $x$ nie ma w $y$, bo $y$ < $x$.
    
    Zatem skoro dla $y$ zachodzi $P(y)$, a $x$ jest liczbą fibonacciego nie będącą w $y$, to dla $k + 1 = y + x$ zachodzi $P(x + y)$.    
    
    
**Dowód optymalności:**
Załóżmy nie wprost, że dla naszego rozwiązania istnieje inne o mniejszej ilości monet, nazwijmy je $P$. Znaczyło by to, że w $P$ istnieje $c$, które zastąpiło przynajmniej dwie liczby $a$ i $b$ w naszym rozwiązaniu, ale to by znaczyło, że $c$ = $a$ + $b$, więc nasz algorytm wziąłby liczbę $c$, bo zawsze bierze największą możliwą liczbę .
Zatem **OPT** ma tyle samo monet, czyli sprzeczność.

## Zadanie 6 - trzeba dowód
![image](https://hackmd.io/_uploads/r1Fv8q4Ra.png)
```python=
stack Leaves = {}
stack Parents = {}
visited = [1...n]
degs = [1...n]

# dodajemy wszystkie liście na stos
def add_leaves(v):
    for each u of V:
        if deg(u) == 1:
            add u to Leaves
            visited[u] = true
                
def color_tree(L, P, k):
    if k == 1:
        color(L.pop())
        return 
    
    while(L != empty):
        v = L.pop()
        visited[v] = true
        color(v)
        for each neighbour u of v:
            degs[u] -= 1
            if not visited[u] and degs[u] == 1:
                add u to P
    color_tree(P, L, k-2)

add_leaves(root)
visited.clear()
color_tree(Leaves, Parents, k)
```
Złożoność $O(V + E)$

**Dowód poprawności:**
Dla $k = 1$ kolorujemy max 1 dowolony wierzchołek.
Ścieżka może mieć **max dwa** liście.
Więc dla $k >= 2$. Możemy pokolorować wszystkie liście.
## Zadanie 7 
![image](https://hackmd.io/_uploads/H1COMJBR6.png)
```python=
visited = [1...n]
Dane: a, b
def mDFS(h,t,e):
    if h == t:
        return false
    visited[h] = true
    in_mst = true
    for each neighbour u of h:
        if not visited[u] and c({h,u}) < c(e)
            and {h, u} != e:
            if not mDFS(u,t,e):
                in_mst = false
    return in_mst
```
Złożoność $O(V + E)$ - zmodyfikowany dfs

**Dowód poprawności:**
Rozważmy przypadki:
1. e jest mostem
    Jeśli $e$ jest mostem, to znaczy, że nie ma **alternatywnej ścieżki** z $a$ do $b$. W algorytmie sprawdzamy czy obecny wierzchołek jest **różny** $a$ i jego sąsiad jest **różny** od $b$.
    Zatem nigdy nie otrzymamy $h = t$, więc algorytm zwróci **prawdę**.
2. $e$ nie jest mostem

    Czyli $e$ leży na jakimś **cyklu**. Skoro nie przechodzimy przez $e$ i uda nam się przejść z $a$ do $b$, przez krawędzie, gdzie każda miała mniejszą wagę niż $e$ to znaczy, że $e$ nie należy do **MST**, bo jest **najcięższa** z tego **cyklu**.
    
    Natomiast, jeśli nie dojdziemy z $a$ do $b$, nie przechodząc przez $e$, to znaczy, że na naszym **cyklu** napotkaliśmy na **cięższą** krawędź niż $e$, zatem $e$ nie jest **najcięższą** krawędzią w tym **cyklu**, zatem należy do **MST**.
    
    
## Zadanie 8 - można lepiej, trzeba jeszcze dowód
![image](https://hackmd.io/_uploads/BkbdM6BA6.png)

```python=
L - stack
degs = [1...n]
max_path = [1...n]
visited= [1...n]
  
def add_leaves(n):
    for each u of V:
        if deg(u) == 1:
            add u to L
            max_path[u] = 0
            
def find_center(L,P,n,c):
    if n==1:
        return L.pop()
    while(L != empty):
        v = L.pop()
        visited[v] = true
        for each neighbour u of v:
            deg[u] -= 1
            if not visited[u] and deg[u] == 1:
                add u to P
                max_path[u] = c+1
    return find_center(P, L, n-1, c+1)    

def find_max(v):
    if max_path[v] == 0:
        return v
    visited[v] = true
    maxi = 0 
    p = 0
    for each neighbour u of v:
        if not visited[u]:
            if maxi < max_path[u]:
                maxi = max_path[u]
                p = u
    return find_max(p)

add_leaves(n)
v = find_center(L, {}, n, 0)
visited.clear()
a = find_max(v)
b = find_max(v)

maxi = 0
c = a
for each v in V:
    if not visited[v]:
        if maxi <= max_path[v]:
            maxi = max_path[v]:
                c = v
if c != a:
    c = find_max(p)
                 
print(a)
print(b)
print(c)
```
Idea: Znajdujemy centroid
Złożoność $O(4 * (V + E) + 2V)=O(V+E)$
Dowód:
Możemy zauważyć, że równomiernie usuwamy wszystkie liście z kadego podrzewa, tworzymy w ten sposób nowe podrzewa, jednocześnie zbliżając się do środka grafu.

Dlaczego to jest największę rozwiązanie, możemy założyć nie wprost, że istnieje większę, to by znaczyło, że któryś z końców abc nie jest końcem najdłużej ścieżki, ale to by też znaczyło, że np.a nie jest liściem, a to jest sprzeczne z działaniem naszego algorytmu. 
## Zadanie 9

## Zadanie 10


# Lista 3

## Zadanie 3
* k = 2

    Dzielimy liczbę $x$ na dwie części $a$ i $b$, takie że $x = a * 10^{\frac{n}{2}} + b$, gdzie $n$ to długość $x$.

    Wtedy $x^2 = a^2 * 10^n + 2 * 10^{\frac{n}{2}} * ab + b^2$
Widzimy, że $2ab = (a + b)^2 - a^2 - b^2$

    **Algorytm:**                                          |
    
```python=
def karat(x):
    if x < 10:
        return x**2
    
    n = len(x)
    a = x div 10**(n/2)
    b = x % 10**(n/2)
    
    a_2 = karat(a) #T(n/2)
    b_2 = karat(b) #T(n/2)
    abt2 = karat(a + b) - a_2 - b_2 #T(n/2) + theta(n)
    
    return a_2 * 10**n + (abt2 * 10**(n/2)) + b_2 # theta(n)
```
Czyli liczbę operacji to:
$3*T(n/) + 2 *\theta(n)$
![image](https://hackmd.io/_uploads/ryhf-XCAp.png)


Zatem korzystając z **Master theorem** złożoność naszego algorytmu wynosi:
$\theta(n^{\log_23}) \approx \theta(n^{1.58})$


* k = 3


## Zadanie 4
![image](https://hackmd.io/_uploads/SyXOoPRR6.png)

**Wyjaśnienie:** https://algorithmtutor.com/Computational-Geometry/An-efficient-way-of-merging-two-convex-hull/

**Idea:**
1. Wybieramy najbardziej na prawo wysuniety punkt lewej otoczki, oznaczamy go $p$ i najbardziej wysunięty na lewo punkt prawej otoczki, oznaczamy go $q$.
2. Tworzymy kopie $p$ i $q$, nazwijmy je $p'$ - poprzednik $p$ i $q'$ - następnik $q$.
3. Jesli $q'$ jest nad prostą $pq$ to $q = q'$ i $q' = q'$.next, wpp 4) (idziemy zgodnie z kierunkiem ruchów zegara)
4. Jeśli $p'$ jest pod prostą $pq$ to $p = p'$ i $p' = p'$.previous (idziemy przeciwnie do ruchów wskazówek zegara)
5. powtarzamy punkty 3) i 4), aż do momentu, w którym $p$ i $q$ się "ustabilizują" tzn. nie będą się już zmieniały
6. Analogicznie wykonujemy te ruchy w drugą stronę.
![image](https://hackmd.io/_uploads/r11UMg1kC.png)


```cpp=
// zwraca 1 jeśli zgodnie
// zwraca 0 jeśli przeciwnie
funkcja czy_zgodnie(a, b, b`)
    fi = (b.x - a.x)(b`.y - a.y) - (b`.x - a.x)(b.y - a.y);
// jeśli fi > 0 to b' jest pod ab, jeśli < 0 to jest nad
    jeżeli fi > 0 : zwróć 0
    wpp.: zwróć 1

funkcja krawedz_gorna():
    p = najbardziej wysunięty na prawo wierzchołek w L
    q = najbardziej wysunięty na lewo wierzchołek w P
    p' = p.poprzedni
    q' = q.nastepny
    Wykonaj:    
            flaga = 0
            Dopóki czy_zgodnie(p, q, q') == 0:
                    q = q'
                    q' = q'.nastepny
                    flaga = 1
            Dopóki czy_zgodnie(q, p, p') == 0:
                    p = p'
                    p' = p'.poprzedni
                    flaga = 1        
    Dopóki flaga == 1;
    

funkcja krawedz_dolna():
    p = najbardziej wysunięty na prawo wierzchołek w L
    q = najbardziej wysunięty na lewo wierzchołek w P
    p' = p.nastepny
    q' = q.poprzedni
    Wykonaj:    
            flaga = 0
            Dopóki czy_zgodnie(p, q, q') == 1:
                    q = q'
                    q' = q'.poprzedni
                    flaga = 1
            Dopóki czy_zgodnie(q, p, p') == 1:
                    p = p'
                    p' = p'.nastepny
                    flaga = 1        
    Dopóki flaga == 1;
    
    wpp.: zwróć 0
```


# Lista 4


## Zadanie 2 - TO-DO


## Zadanie 3 
![image](https://hackmd.io/_uploads/r1ObkLteC.png)

### Lemat: SCS zawiera LCS
- **Dowód:**
    Załóżmy nie wprost, że $SCS$ nie zawiera $LCSa$.
    Weźmy 2 ciagi $X$ i $Y$. Skoro $LCS$ nie należy do $SCSa$, to znaczy, że istnieje przynajmniej 1 element $c$ z $LCS$, który nie należy do $SCSa$. 
    Z def. $LCS$ możemy uzyskać z $X$, zatem skoro $c \in LCS => c \in X$. Z
    Z def. $SCS$, $X$ możemy uzyskać z $SCS$, więc każdy element z $X$ należy do $SCS$. 
    Skoro $SCS$ nie zawiera $c$ to znaczy, że nie jesteśmy w stanie otrzymać $X$ - **sprzeczność**.
    Analogicznie dla $Y$. 
    
- **Idea:**
    Można zauważyć, że dla naszego $SCSa$ zachodzi dana własność:
    $len(SCS) = len(X) + len(Y) - len(LCS)$
    
    Wykonamy Standardowy algorytm $2-D$ dla $LCSa$, ze zmofikowanym powrotem.
    - Najpierw obliczamy standardowo $LCSa$, potem powracamy.
    - Jeśli $dp[i][j-1] = dp[i-1][j]$, to dodajemy na Stos np. $dp[i][j-1]$ i idziemy na $dp[i-1][j-1]$.
    - Jeśli $dp[i][j-1] \neq dp[i-1][j]$ to dodajemy tą literę gdzie $dp$ jest większe i idziemy na dane dp, np. $dp[i][j-1] > dp[i-1][j]$ to idziemy na $dp[i][j-j]$ i dodajemy literkę $Y[j]$ na stos.
    - Na końcu trzeba uważać na dwie pierwsze litery, bo jeśli nie są równe to dodajemy je obie.
    - Na sam koniec ściągamy wszystko ze stosu i wypisujemy. 

### Algorytm: 
```cpp= 
L[m + 1][n + 1]= [[],[], ..., []];
int lcs( X[1...m],  Y[1...n],  m,  n) 
{ 
     
   
    for (i = 0; i <= m; i++) { 
        for (j = 0; j <= n; j++) { 
            if (i == 0 || j == 0) 
                L[i][j] = 0; 
  
            else if (X[i - 1] == Y[j - 1]) 
                L[i][j] = L[i - 1][j - 1] + 1; 
  
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]); 
        } 
    } 
} 
result = L[m][n]


// Cofanie
Stack s = {}
i = m
j = n
while i > 0 and j >0:
    if i == 1 and j == 1:
        if X[0] != Y[0]:
            add Y[0] to s
            
    if L[i-1][j] == L[i][j-1]:
        add X[j] to s
        j--
        i--
    else if L[i-1][j] > L[i][j-1]:
        add X[i] to s
        i--
    else if L[i-1][j] < L[i][j-1]:
        add Y[j] to s
        j--
    
pull all items from s and print them 

```
## Zadanie 4 - TO-DO



## Zadanie 5
### Wersja 1 - Zwraca poprawną długość, ale nie da się odtworzyć LCS
![image](https://hackmd.io/_uploads/r1QeJUteA.png)
https://www.geeksforgeeks.org/space-optimized-solution-lcs/

#### Idea:
Możemy zauważyć, że do wyliczenia $LCS$ dla danego podciągu, to potrzebowaliśmy dwóch ostatnich wierszy. 

Jednak zawsze patrzymy na 3 wartości:
- lewo
- góra
- po przekątnej

Zatem możemy używać jednej tabeli i zapisać do zmiennych wartość górną i po przekątnej przed ich nadpisaniem. To pozwoli nam poprawnie wybierać maksymalną wartość ciągu.

#### Algorytm:

```cpp=
Input: X and Y


dp[n+1] = {0,0, ..., 0}
for(i = 1 ; i<= m; i++){
    prev = dp[0];
    for(j = 1; j <= n; j++){
        tmp = dp[j];
        
        if(X[j-1] == Y[i-1])
            dp[j] = prev + 1;
        else
            dp[j] = max(dp[j-1], dp[j]);
        prev = tmp; 
    }
}
result = max(dp)      
```
#### Złożoność:
- **Czasowa:** $O(nm)$
- **Pamięciowa:** $O(n)$


### Wersja 2 - Metoda hirschberga 

#### Odnośniki:
- Artykuł: https://www.imada.sdu.dk/u/rolf/Edu/DM823/E16/Hirschberg.pdf
- Filmik: https://youtu.be/-R9exap2jo4?si=4C75WW71Db41nLvG&t=1143

#### Idea:
![image](https://hackmd.io/_uploads/rk9tcCiZC.png)
Dane: $X$, $Y$, $m$ - długość $X$, $n$ - długość $Y$
Weźmy słowo $X$ i podzielmy je na dwie części. 
Na $X_L = X\bigg[1 ...\lfloor \frac{m}{2} \rfloor\bigg]$ i $X_R= X\bigg[(\lfloor \frac{m}{2} \rfloor + 1) ... m\bigg]$

Weźmy teraz najbardziej na prawo $y_k$ , który odpowiada najbardziej oddalonemu na prawo $x_i$ z $X_L$, który należy do $LCS$ (To znaczy, że $x_i$ = $y_k$ oraz $x_i$ i $y_k$ są $j$-tym elementem w $LCS$). 
W ten sposób z $Y$ powstaną nam dwie części $Y_L =  Y[1 ...k]$ i  $Y_R =  Y[(k+1) ...n]$

Teraz wystarczy znaleźć $LCS(X_L, Y_L)$ i $LCS(X_R, Y_R)$ i je połączyć

#### Jak znaleźć taką granicę?
![image](https://hackmd.io/_uploads/B1Bkg12bR.png)
Wyliczamy $LCS$ dwóch połówek, dla jednej idziemy $(0,0)$ do $(n, \lfloor \frac{m}{2} \rfloor),$ a dla drugiej idziemy z $(n,m)$ do $(0,\lfloor \frac{m}{2} \rfloor+1)$.

Ważne są dla nas dwa środkowe wiersze o indeksach $\lfloor \frac{m}{2} \rfloor$ i $\lfloor \frac{m}{2} \rfloor+1$
Przechodzimy teraz po całej długości
i znajdujemy $max_{j = 0,1,...,n-1}\{$górny_wiersz$[j]$ + dolny_wiersz$[j+1]\}$ i wyznaczamy pionową linię między $j$ i $j+1$.

![image](https://hackmd.io/_uploads/Sy_-fkhZ0.png)
Wykonujemy ten proces aż do otrzymania wyniku.
![image](https://hackmd.io/_uploads/Bywbm1n-A.png)

#### Przykład:
![image](https://hackmd.io/_uploads/SJaCbWhW0.png)

#### Algorytm:
Dla znajdowania maksymalnej długości dla danej połówki możemy wykorzystać algorytm z wersji 1
```cpp=
//Znajdowanie maksymalnej wartości LCS przechodząc lewo -> prawo
LCS_FW(X,Y)
//Znajdowanie maksymalnej wartości LCS przechodząc lewo <- prawo
LCS_BW(X,Y)
    
Input: X, Y
find_LCS(X, Y):
    m = len(X)
    n = len(Y)
        
    if m == 1:
        return X in Y?  X : null
    if n == 1:
        return Y in X?  Y : null
        
    mid = m div 2
    up = LCS_FW(X[1...mid], Y)
    down = LCS_BW(X[mid+1...m], Y)
        
    k = 0
    maxi = 0
    prev = 0
    for (i=0; i < n-1; i++):
        if maxi < prev + down[i]:
            maxi = prev + down[i]
            k = i
        prev = up[i]
        
    return Concatenate(
                find_LCS(X[1...mid], Y[1...k]),
                find_LCS(X[mid+1...m], Y[k+1...n])
            )
```
#### Złożoność
- **Czasowa:**
Widzmy, że dla każdej połówki wykonujemy algorytm z wersji 1, a on działa w czasie $O(nm)$. Zatem będziemy mieli $O(nm) * (1 + \frac{1}{2} + \frac{1}{4} + ...) = \sum_{i=0}^\infty (\frac{1}{2})^i * O(nm) = 2 * O(nm) = O(nm)$
Możemy też założyć bso, że $n$ > $m$, wtedy
$O(nm) = O(n^2)$

- **Pamięciowa:**
Dla każdej połówki używamy funkcji $LCS \_ FW$ i $LCS\_BW$, gdzie jedna i druga funkcja używaja po jednej tablicy $dp$ o rozmiarze $n+1$. 
Dodatkowo operacje na różnych połówkach są **niezależne** od siebie, więc cały czas możemy operować na dwóch tablicach $dp$ o rozmiarze $n+1$.
Zatem nasz program zużywa $O(n)$ pamięci.

#### Dowód poprawnośći

##### Dlaczego zwracamy LCS?
Lemat: $LCS(X,Y) = LCS(X_L, Y_L) + LCS'(X_R, Y_R)$

Załóżmy, że mamy do dyspozycji algorytm, który dokładnie wie gdzie jest $y_k$. Skoro podzielił na $X_L$ i $X_R$ oraz na $Y_L$ i $Y_R$, to wiemy, że $X_L$ nie ma odpowiadających sobie elementów z $Y_R$ w $LCS$ ani $X_R$ z $Y_L$.
Zatem wystarczy dodać do siebie $LCS(X_L, Y_L)$ z $LCS'(X_R, Y_R)$ aby otrzymać $LCS$.

Nasz algorytm właśnie sprawdza dla każdego $y_k, \ \{k = 0,1, ... , n\}$ 
 długość $LCS(X_L, Y_L)$ i długość $LCS'(X_R, Y_R)$ i wybiera podział z największą sumą.

##### Dlaczego po wyznaczeniu pionowej lini możemy ignorować lewą dolną część i prawą górną?
Wyjaśnione w dowodzie wyżej.


## Zadanie 6
![image](https://hackmd.io/_uploads/SysS1UKxA.png)


### Idea:
- Idea jest taka, że najpierw ukorzeniamy dowolny wierzchołek w drzewie. 
- Następnie obliczamy następujące wyrażenie $dp[v].value = max\{\sum_{u = child \ of \ v}  LIS(u), \sum_{w = gchild \ of \ v} LIS(w) + c(v) \}$
- Jeśli większa jest pierwsza wartość, to dodajemy $dp$ of wszystkich dzieci $v$ na stos.
- wpp. dodajmy $dp$ wszystkich wnuków i na koniec dodajemy sam wierzchołek v.
- Znajdujemy zbiór niezależnych wierzchołków tak, że jeśli nie ma wierzchołka na stosie to wywołujemy rekurencyjnie cały stos, jeśli jest, to go wypisujemy i wywołujemy rekurencyjnie reszte stosu. 



### Algorytm:

```python= 
root = root any vertex in T
dp[n]{2} = [{stack: {}, value: 0}, ...]

def LIS(v):
    if v == null:
        return 0
    
    gchilds_val = sumOf(for each grandchild u of v LISS(u of v))
    childs_val = sumOf(for each child u of v LISS(u of v))
    
    dp[v].value = max(childs_val, gchilds_val + c(v))
    
    if dp[v].value = childs_val:
        for each child u of v:
            add dp[u].stack to dp[v].stack
    else:
        for each grandchild u of v:
            add dp[u].stack to dp[v].stack
        add v to dp[v].stack
        
    return dp[v].value
 

# Znajdowanie LIS
def find_LIS(dp):
    first = dp.stack.pop()
    
    if typeOf(first) == int:
        print(first)
    else:
        find_LIS(first)
    while dp.stack:
        tmp = dp.stack.pop()
        find_LIS(tmp)

            
    
LIS(root)
find_LIS(dp[root])
```

**Złożoność:**
- Czasowa:
    $O(n)$
- Pamięciowa:
    $O(n)$
    


## Zadanie 7 - TO-DO (wydaje się długie)
![image](https://hackmd.io/_uploads/Hyp1djFx0.png)


## Zadanie 8 - TO-DO
![image](https://hackmd.io/_uploads/H1twnstlC.png)

## Zadanie 9
![image](https://hackmd.io/_uploads/r1qyUTFeR.png)

### Idea:
W zadaniu chodzi o to, że dla każdej liczby z pierwszego wyrazy pechodzimy przez cały wyraz drugi.

Zmienna current służy po to, aby sprawdzić czy jeśli mamy większą wartość i przejszliśmy przez elemet w drugim wyrazie, dla którego ma max ciąg to bierzemy maks z tej wartości i naszego current. Jeśli spotkamy w drugim wyrazie element który obecnie iterujemy to uzpełniamy to o current. 


### Algorytm:
```python=
Input: X i Y

def lcis(X, Y):
    dp = [0 for _ in range(len(X))]
    for i in range(len(Y)):
        current = 0
        for j in range(len(X)):
            if X[j] == Y[i]:
                dp[j] = max(current + 1, dp[j])
            if X[j] < Y[i]:
                current = max(current, dp[j])

    maxi = max(dp)
    tmp = maxi - 1
    res = [X[dp.index(maxi)]]
    prev_val = res[0]
    for i in range(dp.index(maxi), -1, -1):
        if dp[i] == tmp and X[i] < prev_val:
            res.append(X[i])
            prev_val = X[i]
            tmp -= 1
        i -= 1

    return maxi, res[::-1]
```

**Złożoność:**
- Czasowa:
    $O(nm)$
- Pamięciowa:
    $O(n)$
### Co gdy $k$ jest ograniczone?
chuj wie XD
## Zadanie 10
![image](https://hackmd.io/_uploads/rJ8UCKmZC.png)
### a)

Niech punkt $a_i$ będzie punktem przecięcia $p_i$ z prostą $l'$, a $b_i$ z prostą $l''$ analogicznie dla punktów $a_j$ i $b_j$. Bso załóżmy, że $a_i < a_j$. Widzimy wtedy, że odciniki $a_ib_i$ i $a_jb_j$ przecinają się tylko wtedy gdy $b_i > b_j$.

Zatem skoro mamy znaleść największy zbiór nieprzecinających się odcików, to możemy najpierw posortować odcinki względem $a_k$ dla $k = \{1,2,...,n\}$ i znaleść największy rosnący podciąg dla $b_k$.
![image](https://hackmd.io/_uploads/rkXEJqQb0.png)

```python=
pairs = [<a1,b1>, <a2,b2>, ... <an,bn>]
sort pairs by ai

def LIS(pairs):
    dp[n] = [0,0,...,0]
    
    for(i = n-1; i <= 0; i--):
        current_max = 1
        b_i = pairs[i].sec
        for(j = i+1; j < n; j++):
            b_j = pairs[j].sec
            if b_j > b_i:
                current_max = max(current_max, dp[j] + 1)
        dp[i] = current_max
    
    #Odzyskiwanie 
    maxi = max(dp)
    s_max = maxi
    prev_val = inf+
    res = []
    for(i = 0; i < n; i++):
        b_i = pairs[i].sec
        if dp[i] == s_max and b_i < prev_val:
            add b_i to res
            prev_val = b_i
            s_max -= 1
            
    return res, maxi, dp  
```
**Złożoność:**
- Czasowa: $O(n^2)$
- Pamięciowa: $O(n)$

### b) 
#### Idea
Niech $dp$ będzie naszą wyliczoną tablicą, czyli na $i$-tym indeksie będzie długość $LISa$ dla $dp[1...i]$.

Wystarczy zrobić drugą tablicę $count$, która będzie przechowywała, na $i$-tym indeksie ilość nadłuższych podciągów dla $dp[1...i]$
![image](https://hackmd.io/_uploads/HJTHxbpZR.png)

Tak będzie wyglądać tablica $count$ po wypełnienu.

A tak by wyglądał ten problem, gdybyśmy sprowadzili to do drzewa
![image](https://hackmd.io/_uploads/r1ttJbTWC.png)

Widzimy, że jeśli znajdziemy nowy $LIS$, to dodanie kolejnej wartości do wszystkich liści nie zwiększa nam ilości $LISów$

Zwiększają nam natomiast wartości, które są większe od liści natomiast same nie tworzą rosnącego porządku.
np. $10$ i $8$ nie możemy ich ustawić w ciąg $1,...,7,10,8$
Tylko, żeby otrzymać $LIS$ możemy stworzyć ciągi zawierące $10$ albo $8$.

Więc, żeby otrzymać ilość $LISów$ dla $dp[i]$ wystarczy przeiterować się po całej tablicy i sprawdzać ciągi o 1 mniejsze. Jesli dany element jest mniejszy od naszego ostatniego elementu do dodajemy jego wartość w $count$

Na samym końcu jeśli jest kilka wartości $maxi$ w $dp$, to dodajemy wartości jakie mają w $count$, wpp zwracamy tylko jedną wartość.

**Złożoność:**
- Czasowa: $O(n^2)$
- Pamięciowa: $O(n)$
# Lista 5

## Zadanie 1
![image](https://hackmd.io/_uploads/HyslA7nbC.png)

### Idea
Naszym celem jest znalezienie dwóch różnych przypadków, dla których drzewo decyzyjne zwróci ten sam wynik. Punkt nie należy do otoczki wypukłej, jeśli jego dodanie spowoduje rozszerzenie tejże otoczki. 

### Kontrprzykład
Weźmy taką otoczkę wypukłą o punktach $A,B,C$
![image](https://hackmd.io/_uploads/BJpqJk6-C.png)


|przypadek $1$| przypadek $2$|
|-------          | -----------|
|$A_x < D_x < B_x$| $A_x < D'_x < B_x$|
|$B_y < D_y < C_y$| $B_y < D'_y < C_y$|

Widzimy, że w obu przypadkach punkty $D$ i $D'$ trafiają do tego samego liścia w drzewie decyzyjnym. Zatem nie jesteśmy wstanie odróżnić tych dwóch różnych przypadków - **sprzeczność**.
## Zadanie 2 - TO-DO
![image](https://hackmd.io/_uploads/Sk0ZeVnW0.png)

## Zadanie 3
![image](https://hackmd.io/_uploads/rJRfeNnW0.png)
### Odnośniki:
**2sum two:**
https://www.youtube.com/watch?v=cQ1Oz4ckceM

**3sum:**
https://www.youtube.com/watch?v=cQ1Oz4ckceM

### 2sum two
![image](https://hackmd.io/_uploads/HkEFk1aZR.png)

Zadanie polega na tym, że mamy dany **target** = $n$. Naszym celem jest znalezienie takich dwóch liczb na posortowaniej tablicy, których suma jest równa $n$.

#### Idea
Rozwiązanie jest dosyć proste, ponieważ możemy użyć dwóch wskaźników $l$ i $r$, które z każdym krokiem będziemy zbliżać do siebie. 

#### Algorytm
Ustawiamy $l$ na początku tablicy $tab$, a $r$ na końcu. 
Rozważamy 4 przypadki:
- Jeśli $arr[l] + arr[r] > target$
to znaczy, że musimy przesunąć nasz prawy wskaźnik $r$ o $1$ w lewo. Nasza tablica jest posortowana, więc przesunięcie lewego wskaźnika o $l$  w prawo tylko by zwiększyło naszą sumę, która i tak jest większa od $n$. 
- Jeśli $arr[l] + arr[r] < target$
to znaczy, że musimy przesunąć $l$ o $1$ w prawo z analogicznego powodu co w przypadku wyżej
- Jeśli $arr[l] + arr[r] = target$
zwróć $arr[l]$ i $arr[r]$.
- Jeśli $l = r$
zwróć $False$

### 3sum
Problem jest podobny do two sum. Naszym zadaniem jest dla danej tablicy (nieposortowanej) znaleźć takie 3 liczby $a$, $b$ i $c,$ które sumują się do $0$. Z definicji 3sum ta tablica jest zbiorem, zatem nie rozważamy duplikatów.

#### Idea
Aby rozwiązać ten problem, napierw musimy posortować naszą tablicę. Następnie wybieramy $a$ i dla $b$ i $c$ sporowadzamy problem do **2sum two**.

![image](https://hackmd.io/_uploads/S1r_yJaZR.png)

#### Algorytm
```cpp=
Input: Arr, n = len(Arr)
find_3sum(Arr, n):
    Arr = Sort(Arr)
    a = 0
    while a < n-2:
        l, r = a + 1, n-1

        while l < r:
            if Arr[a] + Arr[l] + Arr[r] == 0:
                return Arr[a], Arr[l], Arr[r]

            else if Arr[a] + Arr[l] + Arr[r] < 0:
                l++    
            else:
                r--   
        a++
    return False
```

#### Złożoność
- Czasowa: $O(n^2)$
- Pamięciowa: $O(n)$

## Zadanie 4 - Skip

## Zadanie 5 - TO-DO
![image](https://hackmd.io/_uploads/ryLftWBGC.png)

## Zadanie 6
![image](https://hackmd.io/_uploads/BkQ4KZBfR.png)
### Odnośniki:
https://hackmd.io/A7ckSXmLTQ6hqyGhsth5uw?view#ZAD-4
https://github.com/Arsenicro/University/blob/master/Materia%C5%82y/aisd/adwersarz.pdf

### Rozwiązanie
Mamy dane dwa ciagi $A = a_0,a_1,a_2,...., a_n$ oraz $B = b_0,b_1,b_2, ..., b_n$

Naszym celem jest złączenie tych ciągów w jeden posortowany ciąg $X$. Cała przestrzeń danych ciagu $X$ to $\binom{2n}{n}$, bo wybieramy $n$ elementów z $2n$, a resztę uzupełniamy. Adwersarz ogranicza przestrzeń danych by zawierała $2n$ zestawów danych. 

Strategią adwersarza do otrzymania następującego wyniku.
$$a_0 < b_0 < a_1 < b_1 < ... < a_n < b_n$$
Robi tak, ponieważ dla np.  $a_1 < a_2 < a_3 < b_1 < a_4 < ...$ mógłby istnieć algorytm, który zaczyna pytać adwersarza od $a_3$ i $b_1$, widzimy wtedy, że mielibyśmy mniej porównań niż w pierwszym przypadku. 

Takich ciągów możemy stworzyć $2n$, ponieważ możemy zamienić $2n-1$ poszczególnych par.

$$\begin{align*}
&X_0 = a_0, b_0, a_1, b_1, ..., a_n, b_n \\
&X_1 = b_0, a_0, a_1, b_1, ..., a_n, b_n\\
&X_2 = a_0, a_1, b_0, b_1, ..., a_n, b_n\\
&X_3 = a_0, b_0, b_1, a_1, ..., a_n, b_n \\
&. \\
&. \\
&. \\
&X_{2n-1} = a_0, b_0, a_1, b_1, ..., b_n, a_n 
\end{align*}$$



Czyli możemy stworzyć zbiór takich par:
$$ \{(a_0, b_0), (b_0, a_1), (a_1, b_1), ... , (a_i, b_i),  (b_i, a_{i+1}), ... ,(a_n,b_n) \} $$

Rozważamy wszystkie pytania, która może zadać algorytm $\mathcal{A}$ i pokażemy, że każde pytanie może wyeliminować co najwyżej $1$ parę.Wówczas wykażemy, że do scalenia dwóch posortowanych podciągów potrzebne jest conajmniej $2n-1$ porównań. 

Niech $i$ - indeks $a$, $j$-indeks $b$

1. $i > j + 1$ \
    Adwersarz odpowie, że  $a_i$ jest większe od $b_j$, jednak nie zmieni to przestrzeni danych, ponieważ $a_i$ i $b_j$ nie są w tej samej parze.
2. $i < j$
    Adwersarz odpowie, że $a_i$ jest mniejsze od $b_j$, podobnie jak w przykładzie wyżej, nie zmieni to przestrzeni zdarzeń, ponieważ $a_i$ i $b_j$ nie są w ten samej parze.
3. $i = j$
   Adwersarz odpowie $a_i < b_i$ i wykreśli jeden ciąg, w którym była zamieniona para $(a_i, b_i)$
4. $i = j + 1$
   Adwersarz odpowie $a_i > b_i$ i wykreśli jeden ciąg, w którym była zamieniona para $(b_j, a_{j+1})$

Widzimy, że każde zapytanie usunie co najwyżej $1$ parę.