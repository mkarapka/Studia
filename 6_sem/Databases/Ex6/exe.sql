-- begin;

drop table employees;
drop table departments;

create table departments (
id int primary key,
hours int);

create table employees (
id int primary key,
hours int,
department_id int,
foreign key (department_id) references departments(id)
);

insert into departments
select gs, floor(50 + random() * 200)::int
from generate_series(1, 10) as gs;

insert into employees
select
    gs,
    floor(1 + random() * 30)::int,
    floor(1 + random() * 10)
from generate_series(1, 100) as gs;

-- select * from employees;
-- select * from departments;

-- rollback;
