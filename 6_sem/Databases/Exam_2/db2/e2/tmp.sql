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


