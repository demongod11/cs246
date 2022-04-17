create database assignment06;
use assignment06;
create table course(cid varchar(100) primary key, cname varchar(500), l int , t int , p int , c int);
create table course_coordinator(cid varchar(100) primary key, cstart varchar(100), cend varchar(100) , gsubmission varchar(100), coordinator varchar(500) , exam_date varchar(100));
create table course_eligibility(cid varchar(100) not null, program varchar(500), batch_year varchar(20) , batch_month varchar(100) , eligibility varchar(500) );
create table course_instructor(cid varchar(100), instructor varchar(500));
create table faculty(dept varchar(250), instructor varchar(500), primary key(dept, instructor));
load data local infile 'C:/Users/cchan/Downloads/database-14-feb-2022/database-14-feb-2022/course.csv' into table course fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-14-feb-2022/database-14-feb-2022/course_coordinator.csv' into table course_coordinator fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-14-feb-2022/database-14-feb-2022/course_eligibility.csv' into table course_eligibility fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-14-feb-2022/database-14-feb-2022/course_instructor.csv' into table course_instructor fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-14-feb-2022/database-14-feb-2022/faculty.csv' into table faculty fields terminated by '#' lines terminated by '\n';

	-- Task 4.1

#Nested:
select cname,(select count(program) from course_eligibility as d1 where c1.cid=d1.cid) from course as c1 group by cid;

#Correlated Nested:
select cname,count(program) from (select c1.cid,c1.cname,d1.program from course as c1 left outer join course_eligibility as d1 on c1.cid=d1.cid) as s group by cid;


	-- Task 4.2

create table temp1 as (select cid,cname,count(instructor) as cnt,instructor from course natural join course_instructor group by cid);
create table temp2 as (select cid,cname,instructor from temp1 where cnt = (select max(cnt) from temp1));

#Nested:
select temp2.cid,temp2.cname,course_instructor.instructor from temp2,course_instructor where temp2.cid in (select temp2.cid  from temp2 where temp2.cid=course_instructor.cid );

#Correlated Nested:
select t1.cid,t1.cname,ci.instructor from temp2 as t1,course_instructor as ci where exists (select * from course_instructor  where t1.cid=ci.cid );


	-- Task 4.3



CREATE TABLE course_with_faculty
AS (
    SELECT *
    FROM course
);

ALTER TABLE course_with_faculty ADD COLUMN instructor CHAR(50);

UPDATE course_with_faculty
SET instructor = (
    SELECT coordinator
    FROM course_coordinator
    WHERE course_with_faculty.cid = course_coordinator.cid
);

SELECT DISTINCT cname, dept 
FROM (
    (
        SELECT * 
        FROM course_with_faculty
        WHERE (
            (cid NOT LIKE "%H" AND c <> (2*l + 2*t + p))
            OR (cid LIKE "%H" AND c <> (2*l + 2*t + p)/2)
        )
    ) AS tmp
    JOIN faculty 
    ON tmp.instructor = faculty.instructor
);

/*2*/
SELECT DISTINCT table1.cname, faculty.dept
FROM course_with_faculty
AS table1
JOIN faculty
ON table1.instructor = faculty.instructor
WHERE EXISTS (
    SELECT cname
    FROM course
    WHERE
    (
        (
            c <> 2*l + 2*t + p AND NOT cid LIKE '%H'
        )
        OR
        (
            c <> (2*l + 2*t + p)/2 AND cid LIKE '%H'
        )
    )
    AND course.cname = table1.cname
);
	-- Task 4.4

#Nested:
select cname,coordinator from course natural join course_coordinator where ((cid,coordinator) not in (select * from course_instructor));

#Correlated Nested:
select cname,coordinator from (select cname,cid,coordinator from course natural join course_coordinator) as t where not exists (select cid,instructor from course_instructor as i where (t.cid,t.coordinator) = (i.cid,i.instructor));


	-- Task 4.5

#Nested:
select c.cname, cc.gsubmission from course AS c natural join course_coordinator AS cc WHERE c.cid IN (SELECT cc2.cid FROM course_coordinator AS cc2);

#Correlated Nested:
select c.cname, cc.gsubmission FROM course AS c natural join course_coordinator AS cc WHERE EXISTS(SELECT * FROM course_coordinator AS cc2 WHERE c.cid = cc2.cid);


	-- Task 4.6

#Nested:
select cname , P.exam_date from course join (select cid, gsubmission as exam_date  from course_coordinator )as P where P.cid = course.cid and course.cid not like "%H" ;

#Correlated Nested:
select cname , gsubmission from course join course_coordinator as cc on course.cid = cc.cid where exists (select cid from course_coordinator as cc where cc.cid not like "%H" and cc.cid = course.cid );


	-- Task 4.7

#Nested:
select cid,cname,instructor from course_instructor natural join course where cid in (select cid from (select cid,count(cid) as counter from course_eligibility group by cid) as temp7 where counter >= 10);

#Correlated Nested:
select cid,cname,instructor from course_instructor natural join course as c where exists (select * from (select cid,count(cid) as cnt from course_eligibility group by cid) as t where t.cnt >=10 and t.cid = c.cid);


	-- Task 4.8

#Nested:
Select distinct S.instructor , R.dept , S.cid from course_instructor as S , faculty as R where (S.instructor,R.dept) in (select Q.instructor, Q.dept from  faculty as Q,course_instructor as P where Q.instructor = P.instructor );

#Correlated:
Select  S.instructor , R.dept , S.cid from course_instructor as S , faculty as R where exists (select * from  faculty as Q where ( Q.instructor = S.instructor ) and ( Q.instructor = R.instructor ));


	-- Task 4.9

#Netsed:
select instructor,dept from faculty where instructor not in (select instructor from course_instructor);

#Correlated Nested:
select instructor,dept from faculty as FACULTY where not exists (select instructor from course_instructor as INSTRUCTOR  where INSTRUCTOR.instructor = FACULTY.instructor);


	-- Task 5.1

create view view_51 as select cname,(select count(program) from course_eligibility as d1 where c1.cid=d1.cid) from course as c1 group by cid;



	-- Task 5.2

create view view_52 as select temp2.cid,temp2.cname,course_instructor.instructor from temp2,course_instructor where temp2.cid in (select temp2.cid  from temp2 where temp2.cid=course_instructor.cid );



	-- Task 5.3

create view view_53 as 
SELECT DISTINCT cname, dept 
FROM (
    (
        SELECT * 
        FROM course_with_faculty
        WHERE (
            (cid NOT LIKE "%H" AND c <> (2*l + 2*t + p))
            OR (cid LIKE "%H" AND c <> (2*l + 2*t + p)/2)
        )
    ) AS tmp
    JOIN faculty 
    ON tmp.instructor = faculty.instructor
);

	-- Task 5.4

create view view_54 as select cname,coordinator from course natural join course_coordinator where ((cid,coordinator) not in (select * from course_instructor));



	-- Task 5.5

create view view_55 as select c.cname, cc.gsubmission from course AS c natural join course_coordinator as cc where c.cid in (select cc2.cid from course_coordinator as cc2);



	-- Task 5.6

create view view_56 as select cname , P.exam_date from course join (select cid, gsubmission as exam_date  from course_coordinator )as P where P.cid = course.cid and course.cid not like "%H";



	-- Task 5.7

create view view_57 as select cid,cname,instructor from course_instructor natural join course where cid in (select cid from (select cid,count(cid) as counter from course_eligibility group by cid) as temp7 where counter >= 10);



	-- Task 5.8

create view view_58 as Select distinct S.instructor , R.dept , S.cid from course_instructor as S , faculty as R where (S.instructor,R.dept) in (select Q.instructor, Q.dept from  faculty as Q,course_instructor as P where Q.instructor = P.instructor );



	-- Task 5.9

create view view_59 as select instructor,dept from faculty where instructor not in (select instructor from course_instructor);