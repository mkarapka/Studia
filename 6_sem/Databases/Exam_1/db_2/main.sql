-- Zad 1

BEGIN;

INSERT INTO company 
VALUES (1149,'dupa', 'https//dupa', 'dupa-logo', 69);

SELECT * FROM company c
WHERE c.name = 'dupa';

ROLLBACK;

-- Zad 2
SELECT DISTINCT c.name
FROM company c JOIN
    company_branch cb ON c.id = cb.id JOIN
    offer o ON cb.id = o.company_id JOIN
    skill s ON o.id = s.offer_id
WHERE
    s.name LIKE '%PostgreSQL%';

-- Zad 3
SELECT DISTINCT c.name
FROM company c JOIN
    company_branch cb ON c.id = cb.id JOIN
    offer o ON cb.id = o.company_id JOIN
    skill s ON o.id = s.offer_id
WHERE
    s.name ILIKE '%postres%'
    OR s.name LIKE '%PostgreSQL%';

-- Zad 4
