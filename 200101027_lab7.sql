create database assignment07;
use assignment07;

-- Task 2.1

DELIMITER $$
create function stud_year(rollNo int)
returns int
deterministic
begin
 declare yearF int ;
 set yearF = 2000 + rollNo/10000000;
 return yearF;
end $$
DELIMITER ;

-- Task 2.2

DELIMITER $$
create function stud_program(rollNo int)
returns varchar(2)
deterministic
begin
  declare programCode int;
  declare programCodeF varchar(2);
  set programCode =(rollNo/100000)%100;
  set programCodeF = concat('0',programCode);
  return programCodeF;
end $$
DELIMITER ;

-- Task 2.3

DELIMITER $$
create function stud_dept(rollNo int)
returns varchar(2)
deterministic
begin
  declare deptCode int;
  declare deptCode2 int;
  declare deptCodeF varchar(2);
  set deptCode = (rollNo/1000)%100;
  set deptCode2 = (rollNo/10000)%10;
  if deptCode2 = 0 then
      set deptCodeF = concat('0',deptCode);
  else
      set deptCodeF = deptCode;

  end if;
  return deptCodeF;
end $$
DELIMITER ;


-- Task 3
create table hss_electives(roll_number int primary key, sname varchar(500) not null, cid varchar(500) not null, cname varchar(500) not null);


-- Task 4
create table student_details(roll_number int primary key, sname varchar(500) not null, joined_year int not null, joined_program varchar(500) not null, joined_dept varchar(500) not null);


-- Task 5

DELIMITER $$
create function stud_program_conversion(prog_code varchar(2))
returns varchar(20)
deterministic
begin
  declare prog_final varchar(20);
  if prog_code = '01' then
      set prog_final = 'B. Tech';
  else
      set prog_final = 'B. Des';
  end if;
  return prog_final;
end $$
DELIMITER ;

DELIMITER $$
create function stud_dept_conversion(dept_code varchar(2))
returns varchar(20)
deterministic
begin
  declare dept_final varchar(20);
  if dept_code = '01' then
      set dept_final = 'CSE';
  elseif dept_code = '02' then
      set dept_final = 'ECE';
  elseif dept_code = '03' then
      set dept_final = 'ME';
  elseif dept_code = '04' then
      set dept_final = 'CE';
  elseif dept_code = '05' then
      set dept_final = 'DD';
  elseif dept_code = '06' then
      set dept_final = 'BSBE';
  elseif dept_code = '07' then
      set dept_final = 'CL';
  elseif dept_code = '08' then
      set dept_final = 'EEE';
  elseif dept_code = '21' then
      set dept_final = 'EPH';
  elseif dept_code = '22' then
      set dept_final = 'CST';
  else
      set dept_final = 'M & C';
  end if;
  return dept_final;
end $$
DELIMITER ;


DELIMITER |
create trigger student_trigger after insert on hss_electives
for each row
begin
insert into student_details (roll_number, sname, joined_year, joined_program, joined_dept)
values (new.roll_number, new.sname, stud_year(new.roll_number), stud_program_conversion(stud_program(new.roll_number)), stud_dept_conversion(stud_dept(new.roll_number)));
end;
|
DELIMITER ;

-- Task 6
load data local infile 'C:/Users/cchan/Downloads/hss_elective_allocation_2018_batch.csv' into table hss_electives fields terminated by '#' lines terminated by '\n' ignore 4 lines;

-- Task 7.1
insert into hss_electives values('1234567881981','Someone','HS 245','something');
insert into hss_electives values('45678987976818','Someone','HS 245','something');

-- Task 7.2
insert into hss_electives values('123','Someone','HS 245','something');
insert into hss_electives values('18235','chnadra','HS 227','something returns');

-- Task 7.3
insert into hss_electives VALUES('145432','chandra','HS 265','somenthin');
insert into hss_electives VALUES('219006','sun','HS 123','something');

-- Task 7.4
insert into hss_electives values(10000,'random',NULL,'campus return');
insert into hss_electives values(180101001,'someone','HS 223','somathing random');

-- Task 8

DELIMITER |
create trigger student_trigger_update after update on hss_electives
for each row
begin
update student_details set roll_number = new.roll_number, sname  = new.sname, joined_year = stud_year(new.roll_number),
joined_program = stud_program_conversion(stud_program(new.roll_number)),joined_dept = stud_dept_conversion(stud_dept(new.roll_number)) where roll_number = old.roll_number;
end;
|
DELIMITER ;


-- Task 9

DELIMITER |
create trigger student_trigger_delete after delete on hss_electives
for each row
begin
delete from student_details where roll_number = old.roll_number;
end;
|
DELIMITER ;