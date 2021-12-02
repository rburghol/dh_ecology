-- find duplicate GENBANK numbers
select * from(select acquisition_num,count(*) from dh_ecology_isolate group by acquisition_num) as foo where count > 1;
