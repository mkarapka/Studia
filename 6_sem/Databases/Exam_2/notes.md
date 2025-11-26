# WAŻNE
- Ogarnąć jak łączyć funkcje agregujące z having
- Ogólnie obczaić jak ich używać
- W szczególności porobić przykłady z grupowaniem
- WITH

# Lecture: SQL 1

## Update
```SQL
UPDATE Os SET nick='Ala95' WHERE nick='Ala';
UPDATE wpis SET moment=moment+100;
```

## DELETE
```SQL
DELETE FROM <query>
DELETE FROM (SELECT <query>)
```

## INSERT
```SQL
INSERT INTO Os VALUES('Ala' NULL, now());
INSERT INTO Os(nick) VALUES('Ola');
INSERT INTO Os SELECT ... (Schemat tego zapytania musi
zgadzać się ze schematem tabeli, do której wklejamy)
```


## SELECT
```SQL
- DISTINCT
- WHERE nick =/LIKE '%abc%';

-- Konwersja na date
timestamp::date

-- Sklejanie komurek w jeden string
SELECT name||'z'||url FROM company

-- Iloczyn kartezjański
SELECT nick, adres
FROM Os, Wpisy -- = Os x Wpisy
WHERE Os.nick = Wpisy.nick
```

## JOIN
```SQL
company c LEFT JOIN offer o ON o.company_id = c.id;
company c JOIN offer o ON o.company_id = c.id;
```
### Zwykły JOIN
- Łączy części wspólne kolumn dwóch tabel
```SQL
SELECT * FROM
A JOIN B ON A.x = B.y
```
### NATURAL JOIN
**WAŻNE!!!**
```SQL
NATURAL JOIN połączy nam tabele jeśli mają wpólną nazwę jakieś kolumny, inaczej zachowa się jak CROSS JOIN
```
- Jeśli wiemy, że w **A** i **B** jest tylko jedna kolumna, która może mieć część wspólną z drugą tabelą
(np. w **A** jest **x**, a w **B** jest **y**)
to możemy użyć ```NATURAL JOIN```
```SQL
SELECT * FROM
A NATURAL JOIN B
```
### CROSS JOIN
Czyli iloczyn kartezjański dwóch tabel, nie podajemy też tutaj warunku łączenia
```SQL
SELECT * FROM
A CROSS JOIN B
```

### LEFT JOIN
Zwracamy wszystkie krotki z lewej oraz zwracamy tylko JOIN z prawej który pasuje do lewej
```SQL
SELECT * FROM
A LEFT JOIN B ON A.x = B.max
```
### RIGHT JOIN
- Analogicznie jak wyżej

### OUTTER JOIN
Podobne działanie co LEFT/RIGHT JOIN
z tą różnicą, że zwracamy lewe krotki, które nie miały dopasowania z prawej oraz zwracamy prawe krotki, które nie miały dopasowania z lewej
```SQL
SELECT * FROM
A OUTTER JOIN B ON A.x = B.y
```
## Operacja na zbiorach

```SQL
<set1> UNION ALL <set2>
-- ważne aby te zbiory miały te same typy
-- Przykład
-- Chcemy zwrócić z tego samego SELECT a,b, ...krotki
-- z różnymi zbiorem warunków
-- więc zrobimy zapytanie np.WITH na dwie table i połączymy je UNIONem
```

## Porządkowanie wyniku
```SQL
- Usuwanie dup - DISTINCT
- Nazywanie kolumn - AS
- Sortowanie - ORDER BY <col_name> DESC/ASC
- Ograniczenie liczby krotek - LIMIT/OFFSET (skipujemy n krotek)
```

## Grupowanie i funkcje agregujące

```SQL
SELECT max(kod_grupy) FROM Grupa;

count(*) - wszystkie krotki z NULLem
count(g.kod_g) - wszystkie krotki bez NULLa
count(DISTINCT g.kod_g) - Tylko unikalne wartości g.kod_g bez NULLa

-- Funkcje agregujące
-- MIN, MAX, AVG, COUNT, SUM

HAVING używamy do używania funkcji agregujących/dawania warunków na całą GRUPE a nie pojedyńcze krotki
```

# Lecture: SQL 2

## Podzapytania
### WHERE
```SQL
- WHERE możemy używać do pozapytań
- value > ALL (SELECT ...)
- value > ANY
- IN / NOT IN
- EXISTS
```

## Wyciąganie info z kolumny
```SQL
EXTRACT(year/month/day FROM published_at) AS some_val FROM offer;
```

## Osoby, które mają wynik za zadanie w 2022 i mają lepszy niż inny za to zadanie w poprzednich latach

```SQL
SELECT o.*
FROM Osoba o
    JOIN Wynik w1 ON o.id=w.osoba
WHERE EXTRACT(year FROM w.czawWyk)=2022
    AND w1.wynik > ALL(
        SELECT w.wynik
        FROM wynik w
        WHERE w.osoba = w1.osoba -- ten moment zapamiętać i ogólnie to zapytanie
            AND w.zad=w1.zad
            AND EXTRACT(year FROM czasWyk)<2022
    )
```

## Osoby, które ogólnie uzyskały wynik 100 za jakieś zadanie z BD

```SQL
SELECT DISTINCT * FROM osoba o
    JOIN wynik w ON o.id = w.osoba
WHERE w.wynik = 100
    AND w.zad IN (
        SELECT Zad.id FROM Zad
            JOIN Klas ON id = zad
            JOIN Kat ON Kat.id = Kat.kat
        WHERE Kat.nazwa = 'BD'
    );

```

## IN a EXISTS
- ```IN``` porównuje zapytanie z jakąś wartością
- Natomiast ```EXISTS``` Sprawdza czy podzapytanie zwróci jakąkolwiek wartość
```SQL
IN -- porównuje zapytanie z daną wartością np.
w.osoba IN (SELECT ...)
-- EXISTS
WHERE EXISTS(SELECT ...)
```

## Osoby, które poprawiły swój wynik z poprzenich lat
- czyli istnieje wynik gorszy w poprzednich latach
```SQL
SELECT o.* FROM osoba o
    JOIN Wynik w1 ON o.id = w.osoba
WHERE EXTRACT(year FROM czasWyk) = 2025
    AND EXISTS(
        SELECT w.* FROM wynik w1
            JOIN osoba o1 ON o1.id = w1.osoba
        WHERE w.osoba = w1.osoba
            AND EXTRACT(year FROM czasWyk) < 2025
            AND w.wynik < w1.wynik
    )
```

## EXPLAIN ANALYZE
- Fajnie wiedzieć, że to istnieje, może się kiedyś przydać.

## WITH
Tworzy nam tymczasowy wynik podzapytania, do którego możemy się ODWOŁYWAĆ

#### Przykład
```SQL
WITH
cities AS (
    SELECT c.name AS brand_name
    o.title,
    o.city
    ('01-01-2000')::TIMESTAMP AS first_date
FROM company c
    JOIN offer o ON c.id = o.company_id)

SELECT brand_name,
    EXTRACT(year FROM AGE(now(), first_date)) AS "age",
    first_date::date,
    now()::date AS current_date
FROM cities;
```



## ALTER TABLE
- Służy to do modyfikacji tabeli

## array_agg
```SQL
array_agg(column)[a:b]
```
# TRIGGERS
Triggery to takie jakby funkcje, które zależnie jakie warunki im damy,
to automatycznie wykonają jakąś akcje jeśli zmodyfikujemy naszą bazę danych

## BEGIN I AFTER
Triggery możemy wywoływać **po** lub **przed** modyfikacją bazy danych

### P
```SQL
-- Przykład 1
CREATE TRIGGER before_hourly_pay_update;
BEFORE UPDATE ON employees
FOR EACH ROW
SET NEW.salary = (NEW.hourly_pay * 2080); -- dajemy NEW żeby rozróżnić nową wartość pola od starej
-- I to nam wykona akcje przed UPDATE
--
-- Zobacznie triggerów - tylko w mysql - do wyjebania to
SHOW TRIGGERS;
```


## Pytanie na wykładzie
- Mówił Pan na ostatnim wykładzie, że jak mamy AFTER to nie trzeba uważać a jak BEFORE to trzeba - git
- Zapytać się czy skoro może być delete to będzie trzeba
dodawać usuwanie kaskadowe do bazy danych - git
- Jak niby mam przetestować triggera
- Czy kolejny sprawdzian będzie z tej samej bazy danych

## Do ogarnięcia w domu
- Jak dokładnie działa NEW i OLD w AFTER BEGIN
- Przerobić sobie update, insert, delete w bazie danych
- Sprawdzić jakie są rodzaje SETOF
# Kolejny wykład SQL
- może coś z sql injection
-
