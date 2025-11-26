BEGIN;

-- Tworzenie tabel
CREATE TABLE departments (
    id INT PRIMARY KEY,
    hours INT
);

CREATE TABLE employees (
    id INT PRIMARY KEY,
    hours INT,
    department_id INT,
    FOREIGN KEY (department_id) REFERENCES departments(id)
);

WITH emp_data AS (
    SELECT
        gs AS id,
        FLOOR(1 + random() * 30)::INT AS hours,
        FLOOR(1 + random() * 10)::INT AS department_id  -- 1 do 10
    FROM generate_series(1, 100) AS gs
),

all_departments AS (
    SELECT generate_series(1, 10) AS id
),
dept_sums AS (
    SELECT
        d.id,
        COALESCE(SUM(e.hours), 0)::INT AS hours
    FROM all_departments d
    LEFT JOIN emp_data e ON d.id = e.department_id
    GROUP BY d.id
),
insert_departments AS (
    INSERT INTO departments (id, hours)
    SELECT * FROM dept_sums
    RETURNING id
)

INSERT INTO employees (id, hours, department_id)
SELECT id, hours, department_id FROM emp_data;

COMMIT;
