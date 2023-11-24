/*		计科180235孔天欣实验三		*/

USE studentInfo

--0、  实验二数据准备
INSERT INTO student VALUES (20010101,'Jone','M',19,'Computer'),(20010102,'Sue','F',20,'Computer')
,(20010103,'Smith','M'	,19,'Math'),(20030101,'Allen','M',18,'Automation'),(20030102,'deepa','F',21,'Art')
,(20010104,'Stefen','F',20,'Computer')

INSERT INTO course VALUES ('C1','English',NULL,4), ('C2','Math','C1',2), ('C3','Cprogram','C2',2), ('C4','database','C2',2)

INSERT INTO score VALUES (20010101,'C1',90),(20010102,'C1',87),(20010103,'C1',88),(20010102,'C2',90),(20010104,'C2',94),
(20010102,'C3',62),(20030101,'C3',80),(20010103,'C4',77)

--1、  添加一个学生记录
INSERT INTO student VALUES (20010112,'stefen','M',25,'Art')

--2、  添加一个选课记录
INSERT INTO score VALUES (20010112,'C2',NULL)
--3、  	建立临时表tempstudent
SELECT * INTO tempstudent FROM student

--4、	将所有学生的成绩加5分
UPDATE score SET Grade=Grade+5

--5、	将姓名为sue的学生所在系改为电子信息系
UPDATE student SET department='电子信息系' WHERE Student_name='Sue'

--6、	将选课为database的学生成绩加10分
UPDATE score SET Grade=Grade+5 WHERE Course_id IN (SELECT Course_id FROM course WHERE Course_name='database')

--7、	删除所有成绩为空的选修记录
DELETE FROM score WHERE Grade IS NULL

--8、	删除学生姓名为deepa的学生记录
DELETE FROM student WHERE Student_name='deepa'

--9、	删除计算机系选修成绩不及格的学生的选修记录。
DELETE FROM score WHERE Grade<60
