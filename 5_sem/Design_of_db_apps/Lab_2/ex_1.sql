/*CREATE FUNCTION Func(@days INT) 
RETURNS @tablica TABLE (
	PESEL char(11),
	Liczba_egzemplarzy INT
)
AS
BEGIN
INSERT INTO @tablica
SELECT PESEL, COUNT(Egzemplarz_ID) Liczba_egzemplarzy FROM master.dbo.Czytelnik c JOIN master.dbo.Wypozyczenie w 
ON w.Czytelnik_ID = c.Czytelnik_ID
WHERE w.Czytelnik_ID IN (SELECT DISTINCT Czytelnik_ID FROM Wypozyczenie WHERE Liczba_Dni >= @days)
GROUP BY PESEL
RETURN;
END*/

SELECT *
FROM FUNC(20)
