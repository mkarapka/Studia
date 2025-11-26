-- begin;
-- explain analyze select * from article_author
-- where status = 'DOKTORANT';

-- create index status_index on article_author (status);

-- explain analyze select * from article_author
-- where status = 'DOKTORANT';

-- CLUSTER article_author using status_index;
-- analyze article_author;

-- explain analyze select * from article_author
-- where status = 'DOKTORANT';

-- rollback;

-- with extr_date as(
--     select id, country
--     from conference c
--     where extract(year from startdate) = 2017
--     and extract(month from startdate) = 6
-- )

-- select * from extr_date;
--
begin;
explain analyze
delete from
article
where id not in(
select a.id
from conference c
left join article a on c.id = a.conference_id
where a.id is NULL);


create index conf_index on article(conference_id);

explain analyze
delete from
article
where id not in(
select a.id
from conference c
left join article a on c.id = a.conference_id
where a.id is NULL);

rollback;
--
-- begin;

-- explain analyze
-- update article
-- set id = 'dupa'
-- where conference_id NOT IN (select id from conference
-- where year > 2019);

-- rollback;
