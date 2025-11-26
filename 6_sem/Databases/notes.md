# Grupowanie 

- count(*) - liczy wszystkie krotki
- count(col) - policzmy bez nulli, ale policzy powtarzających się użytkowników
- count(DISTINC )

HAVING dotyczy całych group
A WHERE dotyczy krotek samych 

możemy do WHERE dać taki warunek
val > ANY, SOME, ALL, EXISTS + NOT "Podzapytanie" (SELECT ... FROM ... WHERE)

Złączenie naturalne niby słabe - do wyjaśnienie (najlepiej używać po ON)

EXPLAN, EXPLAIN ANALYZE

WAŻNE!!!
Kiedy używamy jakieś tableli, to lepiej robić alias tego, aby te same kolumny
z różnych tabel się nie pomyliły

EXCEPT albo LEFT JOIN

Jeśli JOIN z podzapytaniem to obowiązkowo alias


Co to jest LATERAL?

Czym jest interval

Obczaić jak działa WITH bo podobno fajny 

WITH z DELETE i RETURNING

operator UNINON z ALL i bez
# Jeśli masz błąd ```permission denied for schema public```
- To wpisz ```sudo postgres -u psql -d <database_name>```
- Następnie: ```GRANT ALL ON SCHEMA public TO user```

