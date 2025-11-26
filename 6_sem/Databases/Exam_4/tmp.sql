-- Zadanie 2

-- select super.name
-- from company super
-- where exists (
--     select sub.name
--     from company sub
--     where
--         starts_with(
--             trim(trailing E't' from sub.name),
--             trim(trailing E'\t' from super.name)

--         )
--         and
--             trim(trailing E'\t' from super.name)
--             !=
--             trim(trailing E't' from sub.name)
-- )

SELECT name FROM company AS super
WHERE EXISTS (
SELECT 1 FROM company AS sub
WHERE starts_with (trim(TRAILING E' \t' FROM sub.name) ,
TRIM(TRAILING E' \t' FROM super.name))
AND TRIM(TRAILING E' \t' FROM sub.name)
!= TRIM(TRAILING E' \t' FROM super.name)
)
ORDER BY LENGTH(name), name;
