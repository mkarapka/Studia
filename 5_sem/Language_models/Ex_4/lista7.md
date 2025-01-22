# zadanie 1
![alt text](image.png)

### Sposób na wyliczanie zanużeń
- trenujemy 
- mamy dwa korpusy, angielski i polski
- jeżeli mamy teksty w obu korpusach, które są swoimi tłumaczeniamy to z nich korzystamy, to będzie nasza baza
- dla teksów z korpusu nieprzetłumaczonych tworzymy dla języka o większej lematyzacji tłumaczenia na język o mniejszej
 (np z polskiego tłumaczymy na angielski korzystając w następujący sposób 
    polskie słowo -> lemat -> tłumaczenie lematu
 )

- Alternatywnie
    - policzyć embeddingi dla obu języków osobno
    - następnie dla słów - angielskiego (Y) i polskiego (X), znaleźć macierz
    przekształcenia minimalizującą ||W*Y - X||^2 i będącą macierzą ortogonalną, czyli zachowującą
    wszelkie odległości i położenia wektorów w Y (algorytm SVD)

    - można też zrobić korpus równoległy i budować zdania z polskimi i odpowieadającymi im słowami angielskimi, np zadania typu
    Ala ma kota
    Ala has a kota
    - trenujemy transformer na takich tłumaczeniach (być może jakoś ze słownika korzystamy) i 
    robimy to tak, żeby dany fragment z polskiego zdania miał podobne ppb do odpowiadającego mu fragmentu z tłumaczenia angielskiego

# zadanie 2
![alt text](image-1.png)

https://arxiv.org/pdf/1902.04094

https://www.youtube.com/watch?v=9gA5Agejlr0

- niech rozmiar sekwencji to będzie jakieś S

```
1. zaczynamy jakimś proptem, np tematem generacji: 'best city in the world'
2. potem do prompta doklajamy 'S' jakiś randomowych słów
3. następnie n*S razy (n należałoby jakoś empirycznie wybrać) losujemy pozycję 'i'
    1. dla pozycji 'i' wybieramy najlepiej pasujące słowo (można użyć pipelin'u fill-mask),
    albo np podzielić jedną część zdania względem maski i znaleźć najbliższy token do obu części
    2. wstawiamy wybrane słowo, lub token do sekwencji
    3. powtarzamy losowanie
```

# zadanie 3
![alt text](image-2.png)

- mamy duży n-gramowy model M_ng, działający na tokenach

### Model n-gramowy recap:
- model językowy zakładający że ppb kolejengo tokenu zależy od prawdopowobieństw n-1 tokenów poprzednich
- mamy na początku tokeny <s> </s> oznaczające początek i koniec sekwencji

- podać 2x scenariusze wykorzystania go do traningu GPT

### Jak trenowany był GPT
1. Generative pretraining

2. Supervised fine-tuning

3. Reward Modeling (stworzenie systemu nagród dla bota)

3. Reinforcement learning from human feedback (uwzględnienie wag i maksymalizacja nagrody)

### Scenariusz I
- w 4 fazie a więc przyznawania ocen przez ludzi dla odpowiedzi wygenerowanych przez bota
moglibyśmy też policzyć ocenę na podstawie ppb tokenów z odpowiedzi policzonych przy pomocy M_ng
i też uwzględnić ten score w ocenie

- ten proces oceniania można by było też jakoś poprzeć sprawdzaniem, czy label dany przez człowieka, pokrywa się
w jakiś sposób z ppb zwrócownym przez M_ng, np sprawdzić ppb label'a?

### Scenariusz II
- w 1,2 fazie moglibyśmy predykcje GPT wzmocnić o wagi na podstawie ppb z M_ng
- w fazie 1 moglibyśmy dzięki M_ng zwalczyć powtarzalność albo bezsensowność odpowiedzi (takie odpowiedzi miałyby bardzo małe ppb)


### S1 
- wspieranie oceniania człowieka dodając dodatkową ocenę oraz eliminując od razu pewne zdania (eliminując bias)
  
### S2 
- Nadawanie większe wagi tokenom w generacji 
- eliminowanie powtarzających się i bezsensownych odpowiedzi 
- można też zakładać, że w korpusie występują błędne słowa (bezsensowne)

### S3
- Augmentacja danych za pomocą n-gramu
# zadanie 4
![alt text](image-3.png)

- mamy BERTa, ale nie mamy osadzeń pozycyjnych
- czy do czegoś się może przydać
- czy fakt użycia słownika o dużej liczbie tokenów jest sprzyjający czy obiciążający

Architektura transofrmera w trakcie obliczeń nigdzie nie zapisuje kolejności obliczanych słów,
więc to my to musimy zrobić
- używamy tych tokenów pozycyjnych, aby przesunąć embedding np pierwszego słowa ze zdania, delikatnie w stronę
innych pierwszych słów
- podobnie dla drugiego itd
- każda pozycja powinna mieć swój identifier (swoje osadznie pozycyjne, niezależne od pozycji i inputu)
- osadzenia takie nie mogą być za duże, bo wtedy pozycyjne podobnieństwo przykryje nam sematyczne podobieństwo, stąd stosujemy
sin albo cos, bo niezależnie od ilości pozycji mamy jssno określone wartości minimalne i maksymalne (-1, 1), 
zwykły sin za często się powtarza, czyli zwiększamy jego okresowość bardzo mocno, robimy takie
operacje dla wszystkich wymiarów osadzeń pozytywnych, przeplatamy różne okresy sin i cos i zamieniamy funkcje
stosując raz sin, raz cos
- w ten sposób uzyskujemy deterministyczne osadzenia dla każdej pozycji
(opisane powyżej działa dla tekstu)
![alt text](image-4.png)

### Co się stanie jak wytrenujemy BERTa bez osadzeń pozycyjnych
- uzyskamy model, który ma zapisane jedynie znaczenie semantyczne wyrazu
- czyli uzyskamy de facto word2vec, ale z osadzeniem zależnym od kontekstu (bo wciąż się będzie ono 
zmieniało w zależności od sekwencji, której zanużenie obliczamy)
- word2vec oblicza embedding dla wszystkiego na podstawie 'bag of words' i każdy token, niezależnie od sekwencji
ma taki sam embedding

### Czy taki model byłby do czegoś użyteczny?
- byłby sensowny do zadań dla word2vec, możliwe że byłby trochę lepszy od samego word2vec, bo uwzględnia kontekstu
- zadania:
    - znajdowanie synonimów sensownych w jakimś kontekście zdania
    - może być użyteczny do znajdowania spamu, maili fishingowych, kategoryzacji maili
    - tłumaczenia słów dalej byłyby możliwe, gorzej ze zdaniami

### Czy to że słownik był duży nam przeszkadza?
- raczej, nie bo mamy więcej danych do treningu, a sam word2vec też był trenowany na ogromnych danych i nie 
psuło do wyników xd

# zadanie 5
![alt text](image-5.png)

### Jaka to właściwość?
W standardowym treningu potrzebujemy osadzeń pozycyjnych, żeby znać kontekst

Jeżeli mamy kila tokenów [MASK], ale nie pamiętamy ich pozycji obliczane słowa, które będą się kryć pod [MASK]
otrzymają te same embeddingi, bo przez brak zanużeń pozycyjnych jedyne czym dysponuje model to 'bag of words'.

Zatem w takim treningu będziemy mogli ppb stosować jeden token [MASK] na raz, jest to kłopotliwe, bo może się wydłużyć przez to trening.

# zadanie 6
![alt text](image-6.png)

### Wyjaśnienie na przykładzie
Zadanie: Klasyfikacja wiadomości i spamu
1. Robimy historgram wystepowania kolejnych słów w wiadomościach
1. Dla każdego słowa jesteśmy w stanie policzyć ppb, że wystąpi w wiadomości
![alt text](image-7.png)
1. robimy historgram dla spamu i obliczamy ppb dla słów ze spamu
![alt text](image-8.png)
1. Wyniki ppb zapisujemy
![alt text](image-9.png)
1. Aby sklasyfikować wiadomość np 'Dear friend' obliczamy P(N | 'Dear friend') -> ppb że jest to normalna wiadomości, po warunkiem że
jej zawartość to 'Dear friend', analogicznie liczymy P(S | 'Dear friend')
![alt text](image-10.png)

(p(N) to jest ppb że dowolna wiadomość, niezależnie od tego co zawiera jest wiadomością normalną)
1. Obecnie problem jest taki, że np 'Lunch' nie występuje w spamie ani razu, więc jakakolwiek wiadomość z tym
słowem będzie zawsze zaakceptowana jako normalna, bo p(S | Lunch) = 0, aby rozwiązać ten problem dodajemy
jakiś extra count 'a', żeby nie było 0 wartości

1. Nie uwzględniamy kolejności!!! (bag of words)

1. Normalnie NBC uwzględnia mianownik w tym ułamku z ppb, ale to by było P('Dear friend'), czyli to
samo w S, N, traktujemy to jako stałą
 
### Dlaczego fine-tuning BERTa może dawać lepsze rezultaty (min 2 powody)
1. Skoro NBC traktuje teksty jako 'bag of words' nie uwzględnia w ogóle kolejności, jest to np istotne
w analizie sentementu: 

- nie, to miło z twojej strony
- to nie miło z twojej strony 

będą miały ten sam sentyment

1. Nie mamy w przypadku BERTa problemu z 'zero frequenct words', metody radzenia sobie
z tym problemem przez jakieś zafiksowane (np dodawania domyślnego countera 'a' wszędzie) wartości niekoniecznie muszą dać coś sensownego.
1. W przypadku BERTa
mając kontekst jesteśmy w stanie ocenić embedding słowa, nawet jak wcześniej go w terningu nie było

# zadanie 7
![alt text](image-11.png)

- bierzemy model GPT
- zbiór danych - losowo wygenerowany ciąg liczb [10,100] o jakiejś ustalonej długości, oraz posortowany ciąg
- tokenizujemy pewnie po liczbach (bo liczb jest mało)
- trenujemy model GPT2 od zera
- powtórzyć kilka razy dla każdego ciągu, sprawdzić jak blisko on jest do ciągu wynikowego
- samplujemy tak długo aż dojdziemy do znaku końcowego
< nieposortowany ciąg, posortowany ciąd >
- sprawdzamy accuracy

# zadanie 8
![alt text](image-12.png)

- znowu niewytrenowany model
- -> to XOR
- tokeny: START, END, ->, 0, 0
- 01 -> 1, trenujemy
ALTERNATYWNIE
- chodzi o XORowanie całych liczb, ciągów 0 i 1
- czy transformer potrafi się nauczyć języka
0 0 1 1 1 0 0 =xor po wszystkich bitach = 1
0 1 1 1 1 0 0 =xor = 0
- to tak średnio, ale możeby go nauczyć jakiegoś algorytmu, który poxoruje rzeczy i to może będzie umiał


# zadanie 9
![alt text](image-13.png)

1. Czy standardowa, trenowana tokenizacja jest tu optymalnym wyborem? Czy też może warto
rozważyć jakąś jej modyfkację (a jeżeli tak, to jaką)

- chcemy tworzyć sekwencje znaków w języku python, zatem raczej chcielibyśmy skorzystać z innej tokenizacji
- możemy użyć tokenizacji leksykalnej, podzielić kod źródłowy na identyfikatory, słowa klucze itd.
![alt text](image-14.png)

- osobno tokenizować komentarze (np jako właśnie język naturalny)

1. Jak najlepiej obsłużyć wcięcia w kodzie?

- wcięcia należy ujednolicić, tzn: tam gdzie są wcięcia niech będą one jednolite, np 4 spacje, i pozamienić
pozostałe wcięcia na 4 spacje
- każde wcięcie to powinien być token, np token [IDENT1] -> zejście do pierwszego poziomu wcięcia, [NIDENT1] -> zejście ze wcięcia pierwszego
- można też zejść do poziomu drzewa składniowego wbudowanego w python

1. Czym jest PEP-8? Czy może on mieć jakieś użycie w tym zadaniu?

- jest to zestwa guidelines'ów jak powinien wyglądać czysty kod w python
- może nam posłużyć do sparsowania ciągów wejściowych kodu python, tak aby były one jendolite, oprócz tego
taki kod zapewne byśmy chceli żeby transformer nam generował
- możemy też użyć tego wskaźnika jako kryterium funkcji straty dla transformera

1. Jakie są argumenty za tym, że warto zmienia¢ nazwy zmiennych/funkcji/klas/... w kodzie (zachowując jego semantykę)?

- ujednolicami kod, na którym operuje transformer
- upraszczamy język, tzn pozbywamy się wszystkich naleciałości programisty, tudzież projektu, który analizujemy
- kod jest anonimizowany, nie przeciekają jakieś wrażliwe dane

1. Jak metody NLP (word2vec?, transformery?, ...) mogą pomóc w zamianie nazw (podaj co najmniej dwa przykłady)


- możemy udenolicić nazwy, np sprowadzając nazwy funkcji do jakiegoś konkretnego obszaru embeddingów z nazwami funkcji, na których operowaliśmy w trakcie treningu
- możemy mieć nazwy identyfikatorów takie, które mają jakiś sens w kontekście dzięki mechanizmowi atencji
- dla długich nazw można znaleźć jakieś krótsze leżące blisko pod względem embeddingu

1. Jak statyczna analiza kodu może pomóc w tym zadaniu? (wystarczy jeden scenariusz)

- statyczna analiza kodu wykrywa naruszenia sntadardów programistycznych, błędy typów, składni, bezpieczeństwa
- statyczna analiza kodu może np posłużyć jako funkcja straty, albo walidacja dla wygenerowanego kodu
- oprócz tego może wykrywać na etapie inputu niepoprawny kod
- może też posłużyć jako pomoc dla mechanizmu zamiany nazw, sprawdzając, czy zmiana nazwy identyfikatora nie spowoduje jakiś problemów (np czy jakaś zmienna nie przesłania innej), może też posłużyć do rozpoznania semantyki kodu

# zadanie 10
![alt text](image-15.png)

1. Które?
- zadanie 9

1. Jakie modyfikacje wprowadzić?
- chcielibyśmy tworzyć porpawny kod, możliwe że fajnie byłoby go wykonywać
- oprócz tworzenia kodu chcielibyśmy, żeby LLM dodawał do wygenerowanego kodu jakieś sensowne komentarze
- chcielibyśmy, żeby bot potrafił wykrywać algorytmiczne błędy w kodzie
- może oprócz czystego pythona jakieś jego biblioteki? frameworki? np django

- zadanie 7,8

1. Modyfikacje
- jak zmusić transformer do rozumienia algorytmu i jego uruchamiania, np algorytm sortujący, algorytm xor
albo inne

# zadanie 11
![alt text](image-16.png)


**Tytuł:** Automatyczny mechanizm oceny wypracowań na egzaminie IELTS (Task 1).

**Opis:** Celem projektu jest stworzenie automatycznego narzędzia oceniającego wypracowania na egzaminie IELTS, część pierwsza – 
wypracowanie na podstawie podanego wykresu.

**Zrozumienie wykresu:** Należy wykorzystać gotowy transformer lub rozważyć, 
jak zastosować model BERT do analizy wykresu.

**Przekazanie informacji w sposób spójny:** Należy użyć modelu typu Llama do odpowiadania na pytania
dotyczące danych zawartych w wykresie oraz w wypracowaniu, a następnie porównać,
jak model poradzi sobie z takim zadaniem.

**Spójność:** Zastosowanie BERTa do sprawdzenia logicznego przepływu zdań i weryfikacji,
jak zdania łączą się ze sobą. Dodatkowo, użycie metryk typu BLEU, ROUGE do porównania
z przykładową odpowiedzią (każdemu wypracowaniu dołączona jest przykładowa odpowiedź).

**Zasobność słownictwa:** Wykorzystanie modelu Word2Vec do wyszukiwania synonimów dla 
popularnych słów oraz przeprowadzenie analizy statystyk wyrazów w tekście.

**Zbadanie poprawności gramatycznej:** Skorzystanie z BERTa, zarówno z wersji pretrenowanej,
jak i ewentualnego dostosowania, lub współpracy ze standardową wersją modelu.

**Ocena efektywności systemu:** 
Do oceny systemu należy wykorzystać bazę danych z wypracowaniami: IELTS Writing Scored Essays Dataset na Kaggle.

**Cel:** Celem zadania jest uzyskanie wyników porównywalnych z narzędziami dostępnymi w internecie, takimi jak: IELTS GPT lub WritingLab IELTS Essay Checker.

Jeśli czas na to pozwoli, warto rozważyć dodanie mechanizmu generowania konstruktywnej krytyki dla ocenianych wypracowań.