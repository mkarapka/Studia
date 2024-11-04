DROP PROCEDURE IF EXISTS reader_days
GO

DROP TYPE IF EXISTS reader_id_type
GO

CREATE TYPE reader_id_type AS TABLE (reader_id INT);
GO

CREATE PROCEDURE reader_days @readers_id reader_id_type READONLY
AS
BEGIN
    CREATE TABLE #reader_days (
        reader_id INT,
        sum_of_days INT
    )
	INSERT INTO #reader_days (reader_id, sum_of_days)
	SELECT w.Czytelnik_ID, SUM(w.Liczba_dni) FROM dbo.Wypozyczenie w 
	WHERE w.Czytelnik_ID IN (SELECT reader_id FROM @readers_id)
	GROUP BY w.Czytelnik_ID

	SELECT * FROM #reader_days
	DROP TABLE #reader_days
END
GO

DECLARE @readers AS reader_id_type;
INSERT INTO @readers (reader_id)
VALUES (1), (2), (3);

EXEC reader_days @readers_id = @readers;
GO