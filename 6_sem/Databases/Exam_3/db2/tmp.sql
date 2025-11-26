drop table if exists archive_offer;
create table archive_offer (like offer including all);

alter table archive_offer
add column archive_date timestamp;

create or replace function archive_offer_func()
returns trigger as $$
begin
    insert into archive_offer
    select * from offer
    where id = OLD.id;

    update archive_offer
    set archive_date = NOW()
    where id = OLD.id;
    return OLD;
end;
$$ language plpgsql;

create or replace trigger archive_offer_trigger
before delete
on offer
for each row
execute function archive_offer_func();

begin;
alter table skill
drop constraint if exists skill_offer_id_fkey;

delete from offer
where id = 324;

select * from archive_offer;

rollback;
