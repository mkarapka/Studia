BEGIN;
CREATE TABLE advisor (
    id INTEGER PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    name TEXT
);

CREATE TABLE student (
    id INTEGER PRIMARY KEY GENERATED ALWAYS AS IDENTITY,
    advisor_id INTEGER REFERENCES advisor(id) ON DELETE RESTRICT,
    name TEXT,
    last_enrol DATE
);

-- Insert 10,000 advisors (to be assigned to students)
INSERT INTO advisor(name)
SELECT gen_random_uuid()
FROM generate_series(1, 10000);

-- Insert 20 advisors (not assigned to any student)
INSERT INTO advisor(name)
SELECT gen_random_uuid()
FROM generate_series(1, 20);

-- Insert 2,000,000 students with random advisor assignment and enrollment date
INSERT INTO student(advisor_id, name, last_enrol)
SELECT
    floor(1 + random() * 10000)::int,
    gen_random_uuid(),
    date '2020-01-01' + (random() * (interval '5 years'))
FROM generate_series(1, 2000000);


-- Dlaczego pierwsza z nich trwa szybciej niż druga?
-- SELECT tylko odczytuje dane i nie modyfikuje tabeli, więc nie musi sprawdzać ograniczeń referencyjnych ani blokować wierszy.
-- DELETE musi sprawdzić ograniczenia ON DELETE RESTRICT i zaktualizować strukturę tabeli, co jest bardziej kosztowne.
-- Trigger for constraint student_advisor_id_fkey: time=1932.326 calls=20


CREATE INDEX idx_student_advisor_id ON student(advisor_id);

EXPLAIN ANALYZE
SELECT *
FROM advisor a
WHERE NOT EXISTS (
    SELECT 1 FROM student s WHERE s.advisor_id = a.id
);

-- Usuwanie advisorów bez przypisanego studenta
EXPLAIN ANALYZE
DELETE FROM advisor a
WHERE NOT EXISTS (
    SELECT 1 FROM student s WHERE s.advisor_id = a.id
);
--
EXPLAIN ANALYZE
SELECT *
from student
where

ROLLBACK;
