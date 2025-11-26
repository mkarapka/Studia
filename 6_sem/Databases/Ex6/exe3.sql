begin;

-- drop table if exists advisor;
-- drop table if exists student;

CREATE TABLE advisor(
id INTEGER PRIMARY KEY
GENERATED ALWAYS AS IDENTITY,
name text
);

CREATE TABLE student (
id INTEGER PRIMARY KEY
GENERATED ALWAYS AS IDENTITY,
advisor_id INTEGER REFERENCES advisor(id) ON DELETE RESTRICT,
name text,
last_enrol date
);

INSERT INTO advisor(name) SELECT gen_random_uuid()
    FROM generate_series(1, 10000); -- tym przypiszemy potem studentów

INSERT INTO advisor(name) SELECT gen_random_uuid()
    from generate_series(1, 20); -- krotki bez przypisanego studenta

INSERT INTO student(advisor_id, name, last_enrol)
SELECT floor(1 + random() * 10000)::int,
gen_random_uuid(),
date '2020-01-01' +
random() * (interval '5 years')
FROM generate_series(1, 2000000);

rollback;
