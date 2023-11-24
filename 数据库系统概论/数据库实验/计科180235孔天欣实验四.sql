
/*	1、	查询全体学生的学号、姓名、所在系，并为结果集的各列设置中文名称 */
SELECT Student_id '学号' ,Student_name '姓名' ,department '所在系' FROM student

/*	2、	查询全体学生的选课情况，并为所有成绩加5分。*/
SELECT Student_id,Course_id FROM Score
UPDATE score SET Grade=Grade+5

/*	3、	显示所有选课学生的学号，去掉重复行。 */
SELECT DISTINCT Student_id FROM score

/*	4、	查询选课成绩大于80分的学生。 */
SELECT DISTINCT Student_id FROM score WHERE Grade>80

/*	5、	查询年龄在20到30之间的学生学号，姓名，所在系 */
SELECT Student_id,Student_name,department FROM student WHERE age BETWEEN 20 AND 30

/*  6、	查询数学系、计算机系、艺术系的学生学号，姓名。 */
SELECT Student_id,Student_name FROM student WHERE department IN ('Math','Computer','Art')

/*  7、	查询姓名第二个字符为u并且只有3个字符的学生学号，姓名 */
SELECT Student_id,Student_name FROM student WHERE Student_name LIKE'_u_'

/*  8、	查询所有以S开头的学生。 */
SELECT * FROM student WHERE Student_name LIKE 'S%'

/*  9、	查询姓名不以S、D、或J开头的学生 */
--SELECT * FROM student WHERE Student_name LIKE '[^SDJ]%'

/*  10、查询没有考试成绩的学生和相应课程号（成绩值为空） */
SELECT Student_id,Course_id FROM score WHERE Grade IS NULL

/*  11、求年龄大于19岁的学生的总人数 */
SELECT COUNT(*) FROM student WHERE age>19

/*  12、分别求选修了c语言课程的学生平均成绩、最高分、最低分学生。 */
SELECT AVG(Grade) FROM score WHERE Course_id=(SELECT Course_id FROM course WHERE Course_name='Cprogram')
SELECT TOP 1  Student_id FROM score WHERE Course_id=(SELECT Course_id FROM course WHERE Course_name='Cprogram') ORDER BY Grade DESC
SELECT TOP 1 Student_id FROM score WHERE Course_id=(SELECT Course_id FROM course WHERE Course_name='Cprogram') ORDER BY Grade

/*  13、求学号为20010102的学生总成绩 */
SELECT SUM(Grade) FROM score WHERE Student_id=20010102

/*  14、求每个选课学生的学号，姓名，总成绩 */
SELECT student.Student_id,Student_name,SUM(Grade) 'SumGrade' FROM score,student 
WHERE student.Student_id=score.Student_id GROUP BY student.Student_id,Student_name
/*  15、求课程号及相应课程的所有的选课人数 */
SELECT Course_id,COUNT(*) FROM score GROUP BY Course_id

/*  16、查询选修了3门以上课程的学生姓名学号 */
SELECT Student_name,student.Student_id  FROM student,score WHERE student.Student_id=score.Student_id 
GROUP BY student.Student_id,Student_name HAVING COUNT(*)>3

/*  多表连接查询 */

/*  1、	查询每个学生基本信息及选课情况  */
SELECT student.Student_id,Student_name,sex,age,department,Course_name
FROM student,score,course 
WHERE student.Student_id=score.Student_id AND score.Course_id=course.Course_id

/*  2、	查询每个学生学号姓名及选修的课程名、成绩  */
SELECT student.Student_id,Student_name,Course_name,Grade 
FROM student,score,course 
WHERE student.Student_id=score.Student_id AND score.Course_id=course.Course_id

/*	3、求计算机系选修课程超过2门课的学生学号姓名、平均成绩并按平均成绩降序排列 */
SELECT student.Student_id,Student_name,AVG(Grade) FROM student,score 
WHERE department='Computer' AND student.Student_id=score.Student_id
GROUP BY student.Student_id,Student_name
HAVING COUNT(*)>2
ORDER BY AVG(Grade) DESC

/* 4、	查询与sue在同一个系学习的所有学生的学号姓名 */
SELECT Student_id,Student_name FROM student
WHERE department=(SELECT department FROM student WHERE Student_name='sue')

/* 5、  查询所有学生的选课情况，要求包括所有选修了课程的学生和没有选课的学生，显示他们的姓名学号课程号和成绩（如果有）*/
SELECT st.Student_id,Student_name,Course_id,Grade 
FROM student st 
LEFT JOIN score sc ON st.Student_id=sc.Student_id 