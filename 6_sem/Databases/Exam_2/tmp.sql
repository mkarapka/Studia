CREATE OR REPLACE FUNCTION add_69()
    RETURNS TRIGGER

AS
$$
DECLARE
    skibidi int := 69;
BEGIN
    NEW.issue_date := NEW.issue_date + skibidi;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS before_add_69 on articles;

create trigger before_add_69_trigger
    before insert
    on article
    for each row
execute procedure add_69();

begin;

insert into journal (id, fullname)
values ('uwu', 'uwr');

insert into article (id, journal_id, issue_date)
values ('uwr', 'uwu', 2000);

select * from article a
where a.journal_id = 'uwu';

rollback;
