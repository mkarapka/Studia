-- select
--     s.name,
--     o.city,
--     count(
--         distinct case
--         when e.type = 'permanent'
--         then o.id
--         end) as permanent_offers,
--     count(
--         distinct case
--         when e.type = 'b2b'
--         then o.id
--         end) as b2b_offers
-- from skill s
--     join offer o on s.offer_id = o.id
--     join employment_details e on o.id = e.offer_id
-- group by s.name, o.city

-- having
--     count(
--         distinct case
--         when e.type = 'b2b'
--         then o.id
--         end) > 0
--     or
--     count(
--         distinct case
--         when e.type = 'permanent'
--         then o.id
--         end) > 0
-- order by 3 desc;



drop MATERIALIZED VIEW if exists skill_offer_mat_view;
create MATERIALIZED VIEW skill_offer_mat_view  as
select
    name as skill,
    city,
    sum((type = 'b2b')::int) as b2b_offers,
    sum((type = 'permanent')::int) as permanent_offers
from skill
    natural join employment_details
    join offer on id = offer_id
group by skill, city
having
    sum((type = 'b2b')::int) > 0
    or sum((type = 'permanent')::int) > 0;
REFRESH MATERIALIZED VIEW skill_offer_mat_view;

-- select * from skill_offer_mat_view;

drop table if exists skill_offer_table;

create table skill_offer_table(
    skill text,
    city text,
    permanent_offers int,
    b2b_offers int,
    PRIMARY KEY (skill, city)
);

insert into skill_offer_table
select * from skill_offer_mat_view;

create or replace function skill_function()
returns trigger as $$
BEGIN
    delete from skill_offer_table
    where skill = NEW.name;
    REFRESH MATERIALIZED VIEW skill_offer_mat_view;

    insert into skill_offer_table
    select * from skill_offer_mat_view
    where skill = NEW.name;

    return NEW;
end;
$$ LANGUAGE plpgsql;

create or replace trigger skill_offer_trigger
after insert or update
on skill
for each row
EXECUTE function skill_function();


begin;

insert into skill
VALUES('dupaSQL', 5.0, 1);

select * from skill_offer_table
where skill = 'dupaSQL';

rollback;

create or replace function skill_offer_rm()
returns trigger as $$
    begin
        delete from skill_offer_table
        where skill = OLD.name;

        REFRESH MATERIALIZED VIEW skill_offer_mat_view;

        return OLD;
    end;
$$ language plpgsql;

create or replace trigger skill_offer_rm_trigger
after delete
on skill
for each row
execute function skill_offer_rm();

begin;

delete from skill
where name = 'SQL';

rollback;


create or replace function f()
returns trigger as $$
BEGIN
    update table_a
    set name = NEW.name;
    return NEW;
end;
$$ language plpgsql;

create or replace trigger f_trigger
after insert
on table_c
for each row
execute function f();
