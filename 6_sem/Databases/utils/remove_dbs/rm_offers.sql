-- Tables: company, company_branch, offer, skill
alter table if exists company_branch
drop constraint if exists company_branch_company_id_fkey;
alter table if exists skill drop constraint if exists skill_offer_id_fkey;
alter table if exists offer drop constraint if exists offer_company_id_fkey;
alter table if exists offer drop constraint if exists offer_company_branch_id_fkey;

drop table if exists company;
drop table if exists company_branch;
drop table if exists offer;
drop table if exists skill;
