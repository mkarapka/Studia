-- Create tables
CREATE TABLE Czytelnik
(
    Czytelnik_ID INT PRIMARY KEY,
    PESEL NVARCHAR(50),
    Nazwisko NVARCHAR(50)
);

CREATE TABLE Ksiazka
(
    Ksiazka_ID INT PRIMARY KEY,
    Tytul NVARCHAR(255)
);

CREATE TABLE Egzemplarz
(
    Egzemplarz_ID INT PRIMARY KEY,
    Ksiazka_ID INT,
    FOREIGN KEY (Ksiazka_ID) REFERENCES Ksiazka(Ksiazka_ID)
);

CREATE TABLE Wypozyczenie
(
    Wypozyczenie_ID INT PRIMARY KEY,
    Egzemplarz_ID INT,
    Czytelnik_ID INT,
    FOREIGN KEY (Egzemplarz_ID) REFERENCES Egzemplarz(Egzemplarz_ID),
    FOREIGN KEY (Czytelnik_ID) REFERENCES Czytelnik(Czytelnik_ID)
);

-- Populate data
DECLARE @i INT = 1;
-- Insert 10,000 readers
WHILE @i <= 10000
BEGIN
    INSERT INTO Czytelnik
        (Czytelnik_ID, PESEL, Nazwisko)
    VALUES
        (@i, CONCAT('PESEL', @i), CONCAT('Surname', @i));
    SET @i = @i + 1;
END;

-- Insert 2,000 books
SET @i = 1;
WHILE @i <= 2000
BEGIN
    INSERT INTO Ksiazka
        (Ksiazka_ID, Tytul)
    VALUES
        (@i, CONCAT('Book Title ', @i));
    SET @i = @i + 1;
END;

-- Insert 5,000 copies
SET @i = 1;
WHILE @i <= 5000
BEGIN
    INSERT INTO Egzemplarz
        (Egzemplarz_ID, Ksiazka_ID)
    VALUES
        (@i, FLOOR(1 + RAND() * 2000));
    SET @i = @i + 1;
END;

-- Insert 20,000 rentals
SET @i = 1;
WHILE @i <= 20000
BEGIN
    INSERT INTO Wypozyczenie
        (Wypozyczenie_ID, Egzemplarz_ID, Czytelnik_ID)
    VALUES
        (@i, FLOOR(1 + RAND() * 5000), FLOOR(1 + RAND() * 10000));
    SET @i = @i + 1;
END;
