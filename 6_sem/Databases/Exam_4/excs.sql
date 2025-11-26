--mabi-Mikołaj-Karapka
--3609

-- Zadanie 1
with stationary as (
    select c.id,
        c.name,
        o.published_at,
        o.country_code,
        o.id as offer_id
    from company c
        join offer o on c.id = o.company_id
    where o.remote = false
)

select c.name,
    count(distinct s.offer_id) as offers,
    count(distinct s.country_code) as countires,
    min(s.published_at),
    max(published_at)
from company c
    left join stationary s on s.id = c.id
group by c.name
order by c.name;
