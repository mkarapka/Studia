-- Tables: company, emplyoment_details, offer, skill
alter table if exists employment_details
drop constraint if exists employment_details_offer_id_fkey;

-- alter table if exists employment_details
-- add constraint foregin key (offer_id)
-- references offer(id) on delete cascade;

alter table if exists offer
drop constraint if exists offer_company_id_fkey;

-- alter table if exists offer
-- add constraint foregin key (company_id)
-- references company(id) on delete cascade;

alter table if exists skill
drop constraint if exists skill_offer_id_fkey;

drop table if exists skill;
drop table if exists employment_details;
drop table if exists offer;
drop table if exists company;
