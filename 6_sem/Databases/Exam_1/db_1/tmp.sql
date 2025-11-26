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
    AND DATE(o.published_at) = '2023-09-01'::date
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
