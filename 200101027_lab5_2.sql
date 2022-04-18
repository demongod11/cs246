create database if NOT EXISTS  assignment07;

use assignment07;

DELIMITER //
create procedure yoj(in rollno int)
begin
 declare year int ;
 set year = 2000 + rollno/10000000;
 select year;
end //
DELIMITER ;


DELIMITER //
create procedure pcode(in rollno int)
begin
  declare PC int;
  declare PCs varchar(3);
  set PC =rollno/100000;
  set PC =PC%100;
  set PCs = concat('0',PC);
  select PCs;
end //
DELIMITER ;

DELIMITER //
create procedure dcode(in rollNo int)
begin
  declare DC1 int;
  declare DC2 int;
  declare deptcode varchar(2);
  set DC1 = (rollNo/1000)%100;
  set DC2 = (rollNo/10000)%10;
  if DC2 = 0 then
      set deptcode = concat('0',DC1);
  else
      set deptcode = DC1;
  end if;
  select deptcode;
end //
DELIMITER ;



DELIMITER //
create function joinyear(rollno bigint)
returns int deterministic
begin
DECLARE year1 int;
 set year1 = 2000 + rollno/10000000;
return year1;
end; //
DELIMITER ;



DELIMITER //
create function joinprogram(rollno bigint)
returns varchar(10) deterministic
begin
DECLARE var bigint;
DECLARE program varchar(10);
set var =rollno/100000;
set var = var%100;
if(var=1)
then
set program = "B. Tech";
else
begin 
if(var=2)
then
set program = "B. Des";
end if;
end;
end if;
return program;
end ; //
DELIMITER ;


DELIMITER //
create function joindept(rollno bigint)
returns varchar(10)
deterministic
begin
DECLARE depc bigint;
DECLARE dept varchar(10);
set depc = (rollno/1000)%100;
case 
when depc  = 1 then set dept = "CSE";
when depc  = 2 then set dept = "ECE";
when depc  = 3 then set dept = "ME";
when depc  = 4 then set dept = "CE";
when depc  = 5 then set dept = "DD";
when depc  = 6 then set dept = "BSBE";
when depc  = 7 then set dept = "CL";
when depc  = 8 then set dept = "EEE";
when depc  = 21 then set dept = "EPH";
when depc  = 22 then set dept = "CST";
when depc  = 23 then set dept = "M & C";
end case;
return dept;
end; //
DELIMITER ;




create table hss_electives(roll_number int primary key,sname char(100) not null,cid char(20) not null,cname char(100) not null);

create table student_details(roll_number int primary key,sname char(100) not null,joined_year int not null,joined_program char(100) not null,joined_dept char(100) not null);


DELIMITER |
create trigger student_trigger after insert on hss_electives
for each row
begin
	insert into student_details (roll_number, sname, joined_year, joined_program, joined_dept)
	values (new.roll_number, new.sname, joinyear(new.roll_number), joinprogram(new.roll_number), joindept(new.roll_number));
end;
|
DELIMITER ;

load data local infile 'C:/Users/manid/Desktop/cs246lab5/HSS_ELECTIVE_ALLOCATION_2018_BATCH.csv' into table hss_electives fields terminated by '#' lines terminated by '\n' ignore 4 lines;
/*7.1*/
INSERT INTO hss_electives VALUES('100000000000','madeepak','HS 135','bilingual');
INSERT INTO hss_electives VALUES('1800500000','epak','HS 685','success');
/*7.2*/
INSERT INTO hss_electives VALUES('100','manideepak','HS 135','bilingual');
INSERT INTO hss_electives VALUES('18005','deepak','HS 685','success');
/*7.4*/
INSERT INTO hss_electives VALUES(10001,'mani',NULL,'iit guwahati');
INSERT INTO hss_electives VALUES(180101091,'sunny','HS 197','iit');


DELIMITER |
create trigger stu_update after update on 
hss_electives
for each row
begin
	update student_details 
	set roll_number =  new.roll_number, 
	sname = new.sname, 
	joined_year =  joinyear(new.roll_number), 
	joined_program = joinprogram(new.roll_number),
        joined_dept =  joindept(new.roll_number) 
where roll_number = old.roll_number ;
end;
|
DELIMITER ;

DELIMITER //
create trigger delete_student_details
after delete on hss_electives
for each row
begin
    delete from student_details
    where roll_number = old.roll_number;
end //
DELIMITER ;

