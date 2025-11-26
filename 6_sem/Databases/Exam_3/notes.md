# Przypomnienie przed sprawdzianem

## Jak tworzymy triggery?
### 1. Definiujemy funkcje
```SQL
-- ważne aby był ten nawias
create or replace function f()
returns trigger as -- i do gówienko też piszemy
$$ -- obowiąskowo te zjebane dolarki
declare
    x text;
begin
    select name
    into x from B
    where B.name = NEW.name;
    if x in (SELECT name from table_a) then
        return NEW;
    else
        insert into table_a (name) values (x);
        return NEW; -- to ważne jeśli null to nie zapiszemy tego w bazie danych
    end if; -- po każdym ciągu operacji dajemy ;
end;
$$ language plpgsql; -- to gówno też
```
## Definiujemy trigger
- create or replace trigger <nazwa>
- kiedy ma się wywoływać, czy przed modyfikacją czy po modykiacji
- na jakiej tabeli ma nasłuchiwać
- for each row, czyli dla każdego zmodyfikowanego wiersza
- execute function

```SQL
create or replace trigger f_trigger
after insert
on table_c
for each row
execute function f();
```

## Tworzenie tabeli
```SQL
create table if NOT exists dupa (
id int,
name text,
city text,
country text,
primary key (id, city)
)
```

### Tworzenie tabeli jak poprzednia
```SQL
create table dupa (LIKE dupa_a including all);

alter table dupa drop column name;

alter table dupa add column arch_date text;
```

## Liczenie w kolumnie
```sql
select
    name,
    count(distinct case when type = 'b2b' then o.id end;)

    IF (...) THEN update table_a
    set name = NEW.name, id = NEW.id;

    alter table skill
    drop constraint skill_offer_id_fkey;

    alter table skill
    add constraint skill_offer_id_fkey
    foregin key (offer_id)
    references offer (id)
    on delete cascade;

create table tab (like tab_2 including all);

alter table tab drop column siema;
```
