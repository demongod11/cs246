create database assignment05;
use assignment05;
create table course(cid varchar(100) primary key, cname varchar(500), l int , t int , p int , c int);
create table course_coordinator(cid varchar(100) primary key, cstart varchar(100), cend varchar(100) , gsubmission varchar(100), coordinator varchar(500) , exam_date varchar(100));
create table course_eligibility(cid varchar(100) not null, program varchar(500), batch_year varchar(20) , batch_month varchar(100) , eligibility varchar(500) );
create table course_instructor(cid varchar(100), instructor varchar(500));
create table faculty(dept varchar(250), instructor varchar(500), primary key(dept, instructor));
load data local infile 'C:/Users/cchan/Downloads/database-07-jan-2022/database-07-jan-2022/course.csv' into table course fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-07-jan-2022/database-07-jan-2022/course_coordinator.csv' into table course_coordinator fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-07-jan-2022/database-07-jan-2022/course_eligibility.csv' into table course_eligibility fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-07-jan-2022/database-07-jan-2022/course_instructor.csv' into table course_instructor fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-07-jan-2022/database-07-jan-2022/faculty.csv' into table faculty fields terminated by '#' lines terminated by '\n';

    -- Task 4.1
create table temp1 as (Select * from course_eligibility natural join course);
select cname, count(cid) from temp1 group by cid;


	-- Task 4.2
create table temp2(select cid, count(cid) as counter from course_instructor group by cid);
create table temp3 as select max(counter) as counter2 from temp2; 
create table temp4(select * from temp2 where counter in (select counter2 from temp3));
create table temp5(select * from course_instructor natural join temp4);
create table temp6(select * from course natural join temp5);
select cid, cname, instructor from temp6;

	-- Task 4.3
create table temp7(select cid,cname from course where ((c <> (2*l + 2*t + p) and cid not like '%H') or (c <> (2*l + 2*t + p )/2 and cid like '%H' )));
create table temp8 as (select * from course_instructor natural join temp7);
create table temp9 as (select * from faculty natural join temp8);
select distinct cname,dept from temp9;
			
	-- Task 4.4
select cname,coordinator from course natural join course_coordinator where ((cid,coordinator) not in (select * from course_instructor));

	-- Task 4.5   
create table temp10 as (select * from course_coordinator natural join course);
select cname,gsubmission from temp10;

	-- Task 4.6
select cname,cend from temp10 where (cid not like '%H');

	-- Task 4.7
create table temp11(select cid,count(cid) as counter from course_eligibility group by cid);
select cid,cname,instructor from course_instructor natural join course where cid in (select cid from temp11 where counter >= 10);
  
	-- Task 4.8  
create table temp12(select * from course_instructor natural join faculty);
select instructor, dept, cid from temp12;
	
	-- Task 4.9
select dept, instructor from faculty where ((dept,instructor) not in (select dept,instructor from temp12));