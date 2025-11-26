alter table offer drop constraint if exists offer_company_id_fkey;
--alter table employment_details drop constraint if exists employment_details_offer_id_fkey;
alter table skill drop constraint if exists skill_offer_id_fkey;
-- alter table company_branch drop constraint if exists company_branch_company_id_fkey;

drop table if exists skill cascade;
drop table if exists offer;
drop table if exists company;
drop table if exists employment_details;
drop table if exists company_branch;
