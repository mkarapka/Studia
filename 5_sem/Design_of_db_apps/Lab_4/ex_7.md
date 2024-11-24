# Pessimistic Concurrency Control
## Opis
System zakłada, że konflikty będą występować często dlatego blokuje dane jak najszybciej od rozpoczęcia transakcji. W ten sposób bolkujemy dostęp do danych umniemożliwiając ich modyfikowanie do czasu zakończenia transakcji.
## Przykład 
Alicja i Bob, mają dostęp do tego samego rekordu salda konta A123:

1. Alicja rozpoczyna transakcję, aby wypłacić 500 dolarów z konta A123.
2. W ramach pesymistycznej kontroli współbieżności, transakcja Alicji natychmiast blokuje rekord dla konta A123.
3. W czasie, gdy transakcja Alicji jest w toku, Bob próbuje uzyskać dostęp do salda konta A123, na przykład w celu wpłaty 300 dolarów.
4. Działanie Boba jest zablokowane, dopóki transakcja Alicji się nie zakończy i blokada nie zostanie zwolniona.

# Optimistic Concurrency Control
## Opis 
System zakłada, że konfliky będą występować bardzo rzadko. Zamiast blokować dane początkowo, transakcje są realizowane bez blokad. Dopiero kiedy mają nastąpić zmiany, system sprawdza czy inne transakcje zmodyfikowały dane w tym czasie. Jeśli wykryje konflikt system często aby to rozwiązać ponownie wykona lub wycofa transakcje

## Przykład 
1. Alicja rozpoczyna transakcję, aby wypłacić 500 dolarów z konta A123, odczytując saldo jako 1000 dolarów.
2. Bob również rozpoczyna transakcję, aby wpłacić 300 dolarów na konto A123, odczytując to samo początkowe saldo 1000 dolarów.
3. Transakcja Alicji odejmuje 500 dolarów, aktualizując saldo do 500 dolarów, a ona próbuje zatwierdzić transakcję.
4. Transakcja Boba dodaje 300 dolarów, chcąc zaktualizować saldo do 1300 dolarów, i on również próbuje zatwierdzić transakcję.
5. Sprawdzanie konfliktu: Gdy transakcja Boba próbuje zatwierdzić zmiany, system wykrywa, że transakcja Alicji już zmodyfikowała dane od czasu, gdy Bob je odczytał. W związku z tym transakcja Boba zostaje wycofana lub ponownie uruchomiona, w zależności od strategii rozwiązywania konfliktów.