-- mabi-Mikołaj-Karapka
-- Zadanie 1

SELECT  s.name, 
        count(DISTINCT o.title) AS stanowiska,
        count(DISTINCT o.id) AS oferty,
        min(s.value)::int AS min,
        max(s.value)::int AS max,
        ROUND(avg(s.value))::int AS avg
FROM skill s JOIN offer o ON s.offer_id = o.id
GROUP BY s.name
ORDER BY 2 DESC, 3 DESC
OFFSET 1;

-- Zadanie 2
SELECT o.title, count(DISTINCT s.name),
(array_agg(DISTINCT s.name))[1:4] AS przyk

FROM offer o 
    JOIN skill s ON o.id = s.offer_id
    
GROUP BY o.title
HAVING count(DISTINCT s.name) > 10
ORDER BY 2 DESC, 1;

-- Zadanie 3
WITH ad_table AS(
    SELECT o.id, o.title, s.name
    FROM offer o 
        JOIN skill s ON o.id = s.offer_id
    WHERE 
        s.name ILIKE '%database%'
        OR s.name ILIKE '%SQL%'
    )

-- SELECT * FROM ad_table;

SELECT DISTINCT c.name
    FROM company c
        JOIN offer o ON o.company_id = c.id
    WHERE 
    o.id NOT IN (SELECT id FROM ad_table);
    

-- Zadanie 4
WITH ad_table AS(
    SELECT c.name
    FROM company c 
        JOIN offer o ON o.company_id = c.id 
        JOIN skill s ON o.id = s.offer_id
    WHERE 
        s.name ILIKE '%database%'
        OR s.name ILIKE '%SQL%'
    )

-- SELECT * FROM ad_table;

SELECT DISTINCT c.name
    FROM company c
    WHERE 
    c.name NOT IN (SELECT name FROM ad_table);

-- Zadanie 5
WITH the_most_offers AS
(
    SELECT cb.city
    FROM company_branch cb
        JOIN offer o ON o.company_branch_id = cb.id
    GROUP BY cb.city
    ORDER BY count(o.id) DESC
    LIMIT 10
),
snowflake AS (
    SELECT  cb.city, count(o.id) AS city_count
    FROM company_branch cb
        JOIN offer o ON o.company_branch_id = cb.id
        JOIN skill s ON s.offer_id = o.id
    WHERE s.name ILIKE '%snowflake%'
    GROUP BY cb.city
) 


SELECT tmo.city, COALESCE(sf.city_count, 0)
FROM the_most_offers tmo 
    LEFT JOIN snowflake sf ON sf.city = tmo.city
ORDER BY 2 DESC;
