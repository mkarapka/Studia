PRINT 'Executing Query 1';
SET STATISTICS TIME ON;
SELECT DISTINCT c.PESEL, c.Nazwisko
FROM Egzemplarz e
    JOIN Ksiazka k ON e.Ksiazka_ID = k.Ksiazka_ID
    JOIN Wypozyczenie w ON e.Egzemplarz_ID = w.Egzemplarz_ID
    JOIN Czytelnik c ON c.Czytelnik_ID = w.Czytelnik_ID;
SET STATISTICS TIME OFF;

PRINT 'Executing Query 2';
SET STATISTICS TIME ON;
SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c
WHERE c.Czytelnik_ID IN (
    SELECT w.Czytelnik_ID
FROM Wypozyczenie w
    JOIN Egzemplarz e ON e.Egzemplarz_ID = w.Egzemplarz_ID
    JOIN Ksiazka k ON e.Ksiazka_ID = k.Ksiazka_ID
);
SET STATISTICS TIME OFF;

PRINT 'Executing Query 3';
SET STATISTICS TIME ON;
SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c
WHERE c.Czytelnik_ID IN (
    SELECT w.Czytelnik_ID
FROM Wypozyczenie w
WHERE w.Egzemplarz_ID IN (
            SELECT e.Egzemplarz_ID
FROM Egzemplarz e
WHERE e.Ksiazka_ID IN (
                        SELECT k.Ksiazka_ID
FROM Ksiazka k
                                )
                            )
);
SET STATISTICS TIME OFF;