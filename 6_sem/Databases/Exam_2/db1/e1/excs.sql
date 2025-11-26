-- mabi-Mikołaj-Karapka
-- Zadanie 1


WITH
    pln_brands AS (
    SELECT sb_c.id, sb_c.name, sb_e.currency, sb_e.type 
    FROM company sb_c 
        JOIN offer sb_o ON sb_c.id = sb_o.company_id
        JOIN employment_details sb_e ON sb_e.offer_id = sb_o.id
    WHERE sb_o.remote
        AND sb_e.currency = 'pln'
        AND sb_e.type = 'permanent')

-- SELECT * FROM pln_brands;

SELECT c.id, c.name, count(DISTINCT o.id)
FROM company c
    JOIN offer o ON c.id = o.company_id
    JOIN employment_details e ON e.offer_id = o.id
WHERE o.remote
    AND e.currency = 'pln'
    AND c.id NOT IN (SELECT id FROM pln_brands)
GROUP BY c.id, c.name
ORDER BY 3 DESC, 2 ASC;

-- Zadanie 2

WITH imp_offers AS 
(
SELECT o.id, s.name, ed.salary_from FROM offer o 
    JOIN employment_details ed ON o.id = ed.offer_id
    JOIN skill s ON s.offer_id = o.id
WHERE
    o.city = 'Wrocław'
    AND ed.type = 'permanent'
    AND ed.currency = 'pln'
    AND ed.salary_from > 0)


SELECT imp_o.name, min(imp_o.salary_from) FROM imp_offers imp_o 
WHERE
    (SELECT avg(salary_from) FROM imp_offers) < 
    ALL(
        SELECT imp_o1.salary_from FROM imp_offers imp_o1
        WHERE imp_o1.name = imp_o.name 
    )
GROUP BY imp_o.name
ORDER BY 2 DESC, 1 ASC;



-- Zadanie 3
BEGIN;

-- Usunięcie istniejących ograniczeń kluczy obcych
ALTER TABLE offer DROP CONSTRAINT IF EXISTS offer_company_id_fkey;
ALTER TABLE employment_details DROP CONSTRAINT IF EXISTS employment_details_offer_id_fkey;
ALTER TABLE skill DROP CONSTRAINT IF EXISTS skill_offer_id_fkey;

-- Odtworzenie z kaskadowym usuwaniem
ALTER TABLE offer 
    ADD CONSTRAINT offer_company_id_fkey 
    FOREIGN KEY (company_id) REFERENCES company(id) 
    ON DELETE CASCADE;
    
ALTER TABLE employment_details 
    ADD CONSTRAINT employment_details_offer_id_fkey 
    FOREIGN KEY (offer_id) REFERENCES offer(id) 
    ON DELETE CASCADE;
    
ALTER TABLE skill 
    ADD CONSTRAINT skill_offer_id_fkey 
    FOREIGN KEY (offer_id) REFERENCES offer(id) 
    ON DELETE CASCADE;

DELETE FROM company
WHERE id IN (
    SELECT company_id
    FROM offer
    GROUP BY company_id
    HAVING COUNT(*) > 200
);
ROLLBACK;