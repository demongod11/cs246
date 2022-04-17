create database assignment04;
use assignment04;
create table hss_electives (roll_number int primary key, sname varchar(1000) not null, cid varchar(100) not null, cname varchar(1000) not null);
load data local infile 'C:/Users/cchan/Downloads/database-31-jan-2022/database-31-jan-2022/HSS_ELECTIVE_ALLOCATION_2018_BATCH.csv' into table hss_electives fields terminated by '#' lines terminated by '\n' ignore 4 lines;
insert into hss_electives(roll_number,sname,cid,cname) values (180101058,"Pranav Gupta","HS 236","Sociological Perspectives on Modernity");
insert into hss_electives(roll_number,sname,cid,cname) values (null,"Pranav Gupta","HS 236","Sociological Perspectives on Modernity");
insert into hss_electives(roll_number,sname,cid,cname) values ( 180102158,null,"HS 236","Economics of Uncertainty and Information");
insert into hss_electives(roll_number,sname,cid,cname) values ( 180103158,"Pranav Gupta",null,"Economics of Uncertainty and Information");
insert into hss_electives(roll_number,sname,cid,cname) values ( 180104158,"Pranav Gupta","HS 424",null);
update hss_electives set roll_number = null where roll_number =  180123047;
update hss_electives set roll_number = 180123045 where roll_number = 180123046;
update hss_electives set sname = null;
update hss_electives set cid = null where cid = "HS 211";
update hss_electives set cname = null where cid = "HS 245";
delete from hss_electives where cid = "HS 225";
delete from hss_electives where sname like "%Ajay%";
load data local infile 'C:/Users/cchan/Downloads/database-31-jan-2022/database-31-jan-2022/HS225.csv' into table hss_electives fields terminated by '#' lines terminated by '\n';
load data local infile 'C:/Users/cchan/Downloads/database-31-jan-2022/database-31-jan-2022/ajay.csv' into table hss_electives fields terminated by '#' lines terminated by '\n';
show warnings;
-- After executing the above command we get a message in the terminal as "Warning | 1062 | Duplicate entry '180107005' for key 'hss_electives.PRIMARY'"
-- We get this duplicate entry error while loading ajay.csv because in the table there is already an entry present with roll_number 180107005 as soon as we've loaded HS225.csv file
-- This is a violation of primary key constraint on the column roll_number. So this line gets skipped during the load operation on ajay.csv file
alter table hss_electives drop primary key;
insert into hss_electives(roll_number,sname,cid,cname) values (180123001,"Aditi Bihade","HS 225","Inventing the Truth: The Art and Craft of Autobiography");
alter table hss_electives add constraint my_roll_number primary key(roll_number);
-- After executing the above command we get a message in the terminal as "ERROR 1062 (23000): Duplicate entry '180123001' for key 'hss_electives.PRIMARY'"
-- We get this error because there are already 2 entries with the roll_number 180123001. But primary key constraint on a row requires all the contents of that row to be unique and not null.
-- So primary key constraint does not get added and thus shows a duplicate entry error.
insert into hss_electives(roll_number,sname,cid,cname) values (180123001,"Aditi Bihade","HS 225","Inventing the Truth: The Art and Craft of Autobiography");
load data local infile 'C:/Users/cchan/Downloads/database-31-jan-2022/database-31-jan-2022/old-hss-electives-allotment.csv' into table hss_electives fields terminated by ',' lines terminated by '\n' ignore 1 lines;
select cid from hss_electives;
select * from hss_electives where roll_number like '____01___' or roll_number like '____23___';
select * from hss_electives where roll_number like '____23___' and cname = "Sociological Perspectives on Modernity";
select distinct cid, cname from hss_electives;
select cid, cname from hss_electives order by cname desc;
select sname from hss_electives where cname = "Human Resource Management" order by sname, roll_number;