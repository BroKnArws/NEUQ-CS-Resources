

/*  （1）	建立数学系的学生视图； */
CREATE VIEW student_from_math AS 
SELECT * FROM student WHERE department='Math'

/* （2）	建立计算机系选修了课程名为database的学生的视图，
视图名为compStudentview，该视图的列名为学号、姓名、成绩  */
CREATE VIEW compStudentview AS 
SELECT student.Student_id,Student_name,Grade FROM student,score 
WHERE student.Student_id=score.Student_id AND Course_id=(SELECT Course_id From course WHERE Course_name='database' )

/* （3）	.创建一个名为studentSumview的视图，包含所有学生学号和总成绩  */
CREATE VIEW studentSumview AS
SELECT student.Student_id,SUM(Grade) 'Sum_of_grade' FROM student,score 
WHERE student.Student_id=score.Student_id GROUP BY student.Student_id

/*  （4）	建立一个计算机系学生选修了课程名为database并且成绩大于80分的学生视图，
视图名为CompstudentView1，视图的列为学号姓名成绩。  */
CREATE VIEW CompstudentView1 AS
SELECT student.Student_id,Student_name,Grade FROM student,score WHERE student.Student_id=score.Student_id AND Grade>80 
AND Course_id=(SELECT Course_id From course WHERE Course_name='database' ) AND department='Computer'


/*		（5）	使用sql语句删除compstudentview1视图。  */
DROP VIEW compstudentview1


/*创建针对studentInfo数据库表student 进行插入、修改和删除的三个存储过程：
insertStudent 、updateStudent 和deleteStudent  */

CREATE PROCEDURE insertStudent 
	@Student_id  VARCHAR (10),
    @Student_name VARCHAR (10),
    @sex       VARCHAR (1),
    @age         TINYINT,
    @department   VARCHAR(15)
AS
INSERT INTO student VALUES(@Student_id,@Student_name,@sex,@age,@department)

CREATE PROCEDURE updateStudent
	@Student_id  VARCHAR (10),
    @Student_name VARCHAR (10),
    @sex       VARCHAR (1),
    @age         TINYINT,
    @department   VARCHAR(15)
AS
UPDATE student SET  
	Student_name=@Student_name
	,sex=@sex
	,age=@age
	,department=@department
WHERE Student_id=@Student_id

CREATE PROCEDURE deleteStudent
	@Student_id  VARCHAR (10)
AS
DELETE FROM student WHERE Student_id=@Student_id 




	