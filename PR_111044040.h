
#ifndef AUTOMATION_H
#define AUTOMATION_H

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define TC 12
#define MAX_NAME 30
#define STU_NUM 11
#define MAX_COURSE 50
#define PASSWORD 50
#define MAX_LINE 500

#define INS_FILE "Instructors.csv"
#define STD_FILE "Students.csv"
#define USER_FILE "Users.csv"
#define COURS_FILE "Courses.csv"

#define INS_BIN "Instructors.bin"
#define STD_BIN "Students.bin"
#define USER_BIN "Users.bin"
#define COURS_BIN "Courses.bin"

typedef struct{
	char courseID[TC];					        /*Course's ID					 */
	char courseName[MAX_NAME];			        /*Course's name					 */
	char courseInstructor[MAX_NAME];	        /*course's instructor information*/
	char prequisites[MAX_COURSE][MAX_COURSE];	/*prequisities of course		 */
	int isOpen;							        /*course is open or not			 */
	char mode;						    	    /*add/remove is open or not		 */
	int numOfPrequisites;                       /*number of course's prequisites */
	double grades;				                /*Student's grades			     */
}course_t;

typedef struct{
	char TCnum[TC];						 /*Student's TC number 		 */
	char name[MAX_NAME];				 /*Student's name	  		 */
	char surname[MAX_NAME];			     /*Student's surname		 */
	char studentNum[STU_NUM];			 /*Student number	  		 */
	char startYear[TC];					 /*Student's start year		 */
	course_t enrolCourse[MAX_COURSE];	 /*Enrolled courses	  		 */
	course_t previousCourse[MAX_COURSE]; /*Student's previous courses*/
	int numOfEnCourse;                   /*Number of enrolment course*/
	int numOfPreCourse;                  /*Number of previous course */
}student_t;

typedef struct{
	char TCnum[TC];						/*Instructor's TC number	        */
	char name[MAX_NAME];				/*Instructor's name			        */
	char surname[MAX_NAME]; 			/*Instructor's surname		        */
	course_t openCourse[MAX_COURSE];	/*Instructor's open courses	        */
	int numOpCourse;                    /*Number of Instructor's open course*/
}instructor_t;

typedef struct{
	char userID[TC];					/*User's ID						 */
	char userType[MAX_NAME];			/*User's type(student,instructor)*/
	char userName[MAX_NAME];			/*User's name					 */
	char password[PASSWORD];			/*User's password				 */
}user_t;

/*Read student's information from csv file and write to database*/
int readStudentStruct(int *sizeOfStu);

/*Read instructor's information from csv file and write to database*/
int readInstructorStrcut(int *sizeOfIns);

/*Read user's information from csv file and write to databese*/
int readUserStruct(int *sizeOfuser);

/*Read course's information from csv file and write to database*/
int readCourseStruct(course_t *course, int *sizeOfcourse);

/*Lists the available courses for the student and enables the student to choose courses to enroll*/
int addCourse(student_t *student);

/*Shows the course list of the student and enables the student to remove a course from the list.*/
int removeCourse(student_t *student);

/*Shows the enrolled courses list of the student. Asks the student. The list will be saved into file if student want to save*/
void listCourses(student_t *student);

/*Shows the list of the courses which are given by the instructor and to open a course for enrollment.*/
int openCourse(instructor_t *instructor);

/*Shows the list of the courses which are given by the instructor and the instructor finish the course*/
int finalizeCourse(instructor_t *instructor);

/*Shows the list of the courses which are given by the instructor and enrolment student graded for student's course.*/
int assignGrade(instructor_t *instructor);

/*Lists the students which are enrolled to the course with their grades.*/
int listGrades(instructor_t *instructor);

/*Shows the list of the courses which are given by the instructor and are open*/
void listOpCourse(instructor_t *instructor, int sizeOfCourse);

/*Function to seperate string that read from csv files*/
int seperateStr(char command[], char operation[][MAX_LINE]);

/*Function to open courses add/remove mode*/
int add_remove(course_t *course);

/*Function to find automation system user*/
int getUser(char *userID, user_t *user);

/*Function to find instructor if user is instructor*/
int getIns(char *password, instructor_t *instructor);

/*Function to find student if user is student*/
int getStudent(char *userID, student_t *student);

/*Function to find course that will be made an operation about it*/
int getCourse(char *corsID,course_t *course);

/*Function to list all course*/
void listCourse(course_t *course);

/*Function to list instructors opened courses*/
int listOpenedCourse(instructor_t *instructor);

/*Function that indicate two mode that have some operations according to users*/
void menu(int userType, char *userID, int sizeOfcourse);

/*Function to control binary files was created or not*/
int controlBinFiles(int sizeOfcourse);

#endif
