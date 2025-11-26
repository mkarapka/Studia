# Encje
## Inwestycje
- ID: PK
- Nazwa
- Rok

## Budynki
- ID_bud: PK
- ID_inwestycji: FK -> Inwestycje(ID)
- Adres

## Lokale
- ID_lokal: PK
- ID_bud: FK -> Budynki(ID_bud)
- Numer int
- Status <Sprzedany - Usuwamy, Rezerwacja, W Budowie, Dostępny>
- Wyświetlenia
- Score
- Cena za m^2
- Metraż

## ID_Udogodnienia
- ID
- Nazwa
- <op. adress>

## Lokale-Udogodnienia
- ID_lokal : Fk -> Lokale(ID_lokal)
- ID_Udogodnienia: Fk -> ID_Udogodnienia(ID)

## Klienci
- ID_klient: PK
- Imie
- Nazwisko
- Email

## Klienci-Lokale
- ID_lokal: FK -> Lokale(ID_lokal)
- ID_klient: FK -> Klienci(ID_klient)

## Firmy podwykonawcze
- ID_Firmy: PK
- Branża
- Nazwa
- Email
- Telefon
- Strona

## Firmy-Inwestycja
- ID_Firmy: FK -> Firmy(ID_Firmy)
- ID_inwestycji: FK -> Inwestycja(ID)

## Usterki
- ID_lokal: FK -> Lokale(ID_lokal)
- Opis

<!-- ## Wiadomości_Od_Klientów
- ID_wiad
- ID_klient : FK -> Klienci(ID_klient)
- Treść -->
