/*		--- 计科180235 20188068 孔天欣 ---  */

CREATE DATABASE studentInfo

USE studentInfo

/*	创建student表	*/
CREATE TABLE student(  
  Student_id VARCHAR(10) NOT NULL,
  Student_name VARCHAR(10) NOT NULL,
  sex VARCHAR(1) NOT NULL CHECK(sex IN ('M','F')),
  age TINYINT,
  department VARCHAR(15) DEFAULT 'Computer',
  PRIMARY KEY (Student_id)
) 


/*	创建course表	*/
CREATE TABLE course(  
  Course_id VARCHAR(6) NOT NULL,
  Course_name VARCHAR(20) NOT NULL,
  PreCouId VARCHAR(6),
  Credits DECIMAL (3, 1) NOT NULL,
  PRIMARY KEY (Course_id)
)
/*	  创建score表 	*/ 
CREATE TABLE score(  
  Student_id VARCHAR(10) NOT NULL,
  Course_id VARCHAR(6) NOT NULL,
  Grade DECIMAL (3, 1),
  PRIMARY KEY (Student_id, Course_id),
  FOREIGN KEY (Student_id) REFERENCES student(Student_id),
  FOREIGN KEY (Course_id) REFERENCES course(Course_id)
)

/*  （1）  增加一个memo（备注）字段  */
ALTER TABLE student  ADD mono VARCHAR(200) NULL


/*  （2）	将memo字段的数据类型更改为varchar（300）*/
ALTER TABLE student ALTER COLUMN mono VARCHAR(300)


/*  （3）	删除memo字段  */
ALTER TABLE student DROP COLUMN mono;

/*  数据验证约束  */
ALTER TABLE student
ADD CONSTRAINT chkSex CHECK(sex IN ('M','F'))

ALTER TABLE student  
ADD CONSTRAINT defDep DEFAULT 'Computer' FOR department

/*  查询分析器删除表  */
DROP TABLE studentInfo
