begin;

select * from skill_offer_table
where skill = 'Docker';

delete from skill where name = 'Docker';

select * from skill_offer_table
where skill = 'Docker';

rollback;