1. Oczekiwanie wykładnicze 
2. Gdzie jest używany routing
3. Bufor odbiorczy 
4. Co to jest record NS
5. POP3 - pobieranie maili, SMTP - wysyłanie maili
6. Czemu adres IP nie jest połączeniowy?
7. Proces wysyłania bitów przez TCP
8. CSMA/CD nie wymaga potwierdzenia ramek
9. Jak działa mechanizm kontroli przepływów
10.  RTO - przekroczenie czasu oczekiwania 
11. ARQ - automatic repeat reQuest
12. Co to jest potwierdzanie skumulowane 
13. LAR - LAST Ack Received 
14. Bufory pomagają przy przejściowym nadmiarze pakietów 
15. PGP - wykożystywany przypodpisywaniu maili 
16. HTTPS = HTTP + TLS -> 443 port
17. TLS nakłada się między warstwą aplikacji a transportową 
18. Coś przechodzi 
19. Full cone przyjmie dowolny adres ip na dany port ale restricted full cone przyjmie tylko 
konkretny adres ip

## zadania z egzaminu
FIN muszą wysłać 2 strony aby w pełni zakończyć połączenie, RST ozacza wystąpienie błędu 
- przeczytać w streszczeniu, jest tylko jedna strona aktywna, i ona robi zamnięcie aktywne 
Kocentrator roprasza jedno połączenie na wszystkie porty
- Na plikacji mogą działać różne protokoły 
- Fragmentacja dzieli pakiet na podpakiety
- rever dns albo dns 
- Co robi DHCP, ustala na jakiś czas adres IP
- greylisting co to, filtry bayesowsie co to
- algorytm nagla łączy małe pakiety w jeden duży 
- Nie chcesz tego używać kiedy wysyłasz coś małego szybko
- W TCP chcesz grupką wysłać a UDP pojedyńczo
- MOST nie dzieli ramek - most jest głupi
- tryb nasłuchu odpala się na przełączniku, on się jakie adresy mac skorleować ze swoimi wyjściami i wejściami 


## Inne pytania 
1. Jak się oblicza sumę CRC
2. Co to jest RTO i dlaczego to się oblicza na podstwie wariancji
3. Co to jest kurwa koncentrator
4. Co to są filtry bayesowskie i greylista
5. Jakie rekordy ma serwer DNS
6. Karta sieciowa w trybie nasłuchu co robi
7. Symetryczny na full-cone, restricted cone
8. IPv6 - zasady :: możemy użyć tylko raz i znaczy, że pomiędzy tymi dwoma : są same zera,
   możemy ususwać zera wiodące, :1: znaczy, żę w bloku na końcu jest 1, :0: znaczy, że w bloku są same zera
9. Jak działa SSH
10. Nie rozumiem pytania 31
11. Czemu w ethernecie komputery przekazują sobie token
12. Czemu przy wysyłaniu ramki do routera mamy tam adres mac bramy domyślnej 
13. W jakiej warstwie działa dns 
14. Czy STMP kożysta z TCP
15. Co to jest zdalny adres IP
16. Co to są gnizada nasłuchujące 
17. ZADANIE 27
## Typy zadań obliczeniowych
1. Oblicz sumę kontroną dla danego wielomianu i wiadomości
2. Dzielenie sieci na podsieci 
3. Obliczenie czy dany adres CIDR to komputer/adres sieci/adres rozgłoszeniowy
4. Obliczanie np. ile zdążmy przesłać bitów zanim dostaniemy odpowiedź 
czyli do policzenia np. RTT, w jakim czasie prześlemy cały pakiet, w jakim czasie przetransferujemy pakiet na kabel

## Pytania 2019
1. Co to było RST
2. CO TO JEST SPF
3. CO TO SĄ SIECI CDN - to działa tak, że jak mamy serwer, i niechcemy, aby klient pobierał jakiś części strony bezpośrednio z serwera to dajemy mu link do serwera cdn i on działa lepiej 
4. PYTANIE 22
5. GDZIE BYŁO WYKŁADNICZE COŚ POZA ODCZEKIWANIEM
5. Odległość Hamminga
6. Co to kod MAC
7. PYTANIE 24
8. Co robi protokół HTTP
9. SPF dodatek do SMTP, żeby nie przyjmować poczty z niedozwolonych źródeł
10. tryp nasłuchu zbiera maci swoich użądzeń
11. Przepływ kontroluje się zmniejszając okno oferowane 
12. Możemy mieć nat symetryczny i asymetryczny 

13. W odległości hamminga chodzi o to, że jeśli mamy odległość hamminga k to jesteśmy w stanie wykryć, że 3 3 miejscach jest błąd, a jesteśmy w stanie poprawić floor((k-1)/2) bitów 
14. RST jest w przypadku przerwania połączenia 
15. Kody MAC służy do uwieżytelniania
