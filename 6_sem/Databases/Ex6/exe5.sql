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


-- EXPLAIN ANALYZE
-- SELECT * FROM student
-- WHERE last_enrol BETWEEN '2022-03-01' AND '2022-06-01';

-- CREATE INDEX idx_student_last_enrol ON student(last_enrol);
-- CLUSTER student USING idx_student_last_enrol;
-- ANALYZE student;

-- EXPLAIN ANALYZE
-- SELECT * FROM student
-- WHERE last_enrol BETWEEN '2022-03-01' AND '2022-06-01';


ROLLBACK;
