-- mabi-Mikołaj-Karapka*
-- Zadanie 1
SELECT DISTINCT city FROM offer o 
JOIN company c ON c.id = o.company_id
WHERE c.name = 'Siepomaga.pl'
ORDER BY o.city;

-- Zadanie 2
SELECT c.name, o.title
FROM company c JOIN
    offer o ON c.id = o.company_id JOIN
    skill s ON o.id = s.offer_id
WHERE 
    s.name ILIKE '%kotlin%'
    AND s.value < 5
    AND o.city = 'Warszawa'
ORDER BY c.name, o.title;

-- Zadanie 3
SELECT DISTINCT c.name 
FROM company c LEFT JOIN offer o
    ON c.id = o.company_id AND o.remote
WHERE o.id is NULL
ORDER BY c.name;

-- Zadanie 4
SELECT DISTINCT
        c.name, 
        o.title, 
        o.experience_level, 
        et.salary_from,
        et.salary_to,
        (round(et.salary_to - et.salary_from)) AS difference,
        CONCAT((round(100*(et.salary_to - et.salary_from) / et.salary_from)), '%') AS "%",
        et.currency
FROM company c JOIN offer o
    ON c.id = o.company_id JOIN
    employment_details et ON et.offer_id = o.id
WHERE 
    et.type ILIKE 'B2B'
    AND DATE(o.published_at) = '2023-09-01'
    AND et.currency = 'pln'
    AND et.salary_from > 0
ORDER BY 
    "%", c.name;

-- Zadanie 5
-- CREATE TABLE salaries_abroad(LIKE employment_details);
-- ALTER TABLE salaries_abroad ADD COLUMN country_code text;
-- ALTER TABLE salaries_abroad ADD PRIMARY KEY (offer_id, type);
-- ALTER TABLE salaries_abroad ADD FOREIGN KEY (offer_id) REFERENCES offer(id);

-- Zadanie 6
INSERT INTO salaries_abroad 
SELECT e.* , o.country_code 
FROM employment_details e JOIN  
offer o ON e.offer_id = o.id 
WHERE country_code != 'PL';




