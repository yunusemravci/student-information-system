
#include "PR_111044040.h"

void menu(int userType, char *userID,int sizeOfcourse)
{
    int selection;
    char skip;
    user_t user;
    instructor_t instructor;
    student_t student;
    
    
    if(userType == 0)
    {
        if(getStudent(userID,&student) == 0)
        {
            system("clear");
            
            printf("\n\n\t#############################################################");
            printf("\n\t##                                                         ##");        
            printf("\n\t##\t\t\tSTUDENT MODE                       ##");
            printf("\n\t##                                                         ##");
            printf("\n\t#############################################################");
            printf("\n\t##                                                         ##"); 
            printf("\n\t##   STUDENT ID:\t%s                        ##",student.TCnum);
            printf("\n\t##   NAME      :\t%s                                ##",student.name);
            printf("\n\t##   SURNAME   :\t%s                              ##",student.surname);
            printf("\n\t##                                                         ##"); 
            printf("\n\t#############################################################");
	        printf("\n\t\t1. Add Course                                     \n");
	        printf("\t\t2. Remove Course                                  \n");
	        printf("\t\t3. List Courses                                   \n");
	        printf("\t\t4. Exit                                           \n");
            printf("\t#############################################################");
            do
	        {
  
	        
	            printf("\n\t\t# select an operation: ");
	            scanf("%d%c",&selection,&skip);
                
                switch(selection)
                {
                    case 1:
                        addCourse(&student);
                        break;
                    case 2:
                        removeCourse(&student);
                        break;
                    case 3:
                        listCourses(&student);
                        break;
                    case 4:
                        break;
                    default:
                    {
                        printf("\n\tWrong Choise!!");
                    }
                }
            }while(selection!=4);
        }
        else
        {
            printf("User didn't find in Database!!\n");
        }      
    }
    else if(userType == 1)
    {
        if(getIns(userID,&instructor) == 1)
        {
            system("clear");
            
            printf("\n\n\t#############################################################");
            printf("\n\t##                                                         ##");                   
	        printf("\n\t##\t\t\tINSTRUCTOR MODE                    ##");
            printf("\n\t##                                                         ##");
            printf("\n\t#############################################################");
            printf("\n\t##                                                         ##"); 
            printf("\n\t  \tINSTRUCTOR ID: %s                            ",instructor.TCnum);
            printf("\n\t  \tNAME-SURNAME : %s %s",instructor.name,instructor.surname);
            printf("\n\t##                                                         ##");
            printf("\n\t#############################################################"); 
	        printf("\n\t\t1. Open Course 			\n");
	        printf("\t\t2. Finalize Course		\n");
	        printf("\t\t3. Grade a Course	    \n");
	        printf("\t\t4. List Opened Courses	\n");
	        printf("\t\t5. List Grades			\n");
	        printf("\t\t6. Exit			        \n");
	        printf("\t#############################################################");
            
            do
	        {
	            printf("\n\t\t*** Select an operation: ");
	            scanf("%d%c",&selection,&skip);
	    
	            switch(selection)
                {
                    case 1:
                        openCourse(&instructor);
                        break;
                    case 2:
                        finalizeCourse(&instructor);
                        break;
                    case 3:
                        assignGrade(&instructor);
                        break;
                    case 4:
                        listOpCourse(&instructor,sizeOfcourse);
                        break;
                    case 5:
                        listGrades(&instructor);
                        break;
                    case 6:
                        break;
                    default:
                    {
                        printf("\n\t\t** Wrong Choice!!");
                    }
                }
            }while(selection!=6);
        }
        else
        {
            printf("\n\t\t* User wasn't found in Database!!\n");
        }
    }
}
int controlBinFiles(int sizeOfcourse)
{
    FILE *inp, *inp1, *inp2, *inp3;
    int sizeOfIns,i,sizeOfuser, sizeOfStu;
    course_t *course;
    int flag=-1; 
    
    inp=fopen(INS_BIN,"rb");
    inp1=fopen(STD_BIN,"rb");
    inp2=fopen(USER_BIN,"rb");
    inp3=fopen(COURS_BIN,"rb");
    
    if(inp==NULL)
    {
        flag=readInstructorStruct(&sizeOfIns);   
    }
    else
        fclose(inp);
    
    if(inp1==NULL)
    {   
        flag=readStudentStruct(&sizeOfStu);
    }
    else
        fclose(inp1);

    if(inp2==NULL)
    {
        flag=readUserStruct(&sizeOfuser);
    }
    else
        fclose(inp2);

    if(inp3 == NULL)
    {
        flag=readCourseStruct(course,&sizeOfcourse);
    }
    else
        flag=fclose(inp3);  

    return flag;
}
int readInstructorStruct(int *sizeOfIns)
{
	FILE *Inscsv;
	FILE *Insbin;
	instructor_t *instructor;
	int i=0,j=0, flag=1;
	char *cp,*status;
	char rowArr[MAX_LINE];
	
	Inscsv=fopen(INS_FILE,"r");
	Insbin=fopen(INS_BIN,"wb");
	
	instructor=(instructor_t *)malloc(sizeof(instructor_t));
	
	if(Inscsv == NULL)
	{
		printf("\n\t\t** File error!\n");
		flag=0;
	}
	else if(instructor==NULL)
	{
	    printf("\n\t\t** Memory is not created!!");
	    flag=-1;
	}
	else{
	    status=fgets(rowArr,MAX_LINE,Inscsv);
		while(status!=NULL){

			strcpy(instructor->TCnum,strtok(rowArr,","));
			instructor->TCnum[strlen(instructor->TCnum)]='\0';
			strcpy(instructor->name,strtok(NULL,","));
			instructor->name[strlen(instructor->name)]='\0';
			strcpy(instructor->surname,strtok(NULL,","));
			instructor->surname[strlen(instructor->surname)]='\0';
			instructor->numOpCourse=0;
			fwrite(instructor,sizeof(instructor_t),1,Insbin);    /*databese created*/
			status=fgets(rowArr,MAX_LINE,Inscsv);
			i++;	
		}
		
		*sizeOfIns=i;
	}
	fclose(Inscsv);
	fclose(Insbin);
	free(instructor);
}
int readUserStruct(int *sizeOfuser)
{
	FILE *Usercsv;
	FILE *Userbin;
	user_t *user;
	int flag=1;
	int i=0,numOfValue,j=0;
	char rowArr[MAX_LINE];
	char *status;
	
	Usercsv=fopen(USER_FILE,"r");
	Userbin=fopen(USER_BIN,"wb");
	
	user=(user_t *)malloc(sizeof(user_t));
	if(Usercsv == NULL)
	{
		printf("\n\t\t** File error");
		flag=0;
	}
	else if(user == NULL)
	{
	    printf("\n\t\t** Memory is not created!!");
	    flag=-1;
	}
	else{
		status=fgets(rowArr,MAX_LINE, Usercsv);
		
		while(status!=NULL)
		{
			strcpy(user->userID,strtok(rowArr,","));
			strcpy(user->userType,strtok(NULL,","));
			strcpy(user->userName,strtok(NULL,","));
			strcpy(user->password,strtok(NULL,","));

			fwrite(user,sizeof(user_t),1,Userbin);    /*databese created*/
			status=fgets(rowArr,MAX_LINE, Usercsv);
			i++;	
		}
	}
	
	*sizeOfuser=i;		
	fclose(Usercsv);
	fclose(Userbin);
	free(user);

	return flag;
}
int readStudentStruct(int *sizeOfStu)
{
	FILE *stucsv;
	FILE *stubin;
	student_t *students;
	
	int i=0, j=0,flag=1;
	char rowArr[MAX_LINE];
	char *status;
	
	stucsv=fopen(STD_FILE,"r");
	stubin=fopen(STD_BIN,"wb");
	
	students=(student_t *)malloc(sizeof(student_t));
	if(stucsv == NULL)
	{
		printf("\n\t\t** File error");
		flag=0;
	}
	else if(students == NULL)
	{
	    printf("\n\t\t** Memory is not created!!");
	    flag=-1;
	}
	else
	{
	    status=fgets(rowArr, MAX_LINE, stucsv);
	    while(status!=NULL)
		{
		    strcpy(students->TCnum,strtok(rowArr,","));
		    students[i].TCnum[strlen(students[i].TCnum)]='\0';
		    strcpy(students->name,strtok(NULL,","));
		    strcpy(students->surname,strtok(NULL,","));
		    strcpy(students->studentNum,strtok(NULL,","));
		    students->studentNum[strlen(students->studentNum)]='\0';
		    strcpy(students->startYear,strtok(NULL,","));
		    students->startYear[strlen(students->startYear)]='\0';
		    students->numOfEnCourse=0;
		    students->numOfPreCourse=0;
		    fwrite(students,sizeof(student_t),1,stubin);    /*databese created*/
			status=fgets(rowArr, MAX_LINE, stucsv);
		    i++;
		}
		
	}
	
	*sizeOfStu=(i-1);
	
	free(students);
	fclose(stucsv);
	fclose(stubin);
	
}
int readCourseStruct(course_t *course, int *sizeOfcourse)
{
	FILE *corscsv;
	FILE *corsbin;
	
	int i=0, j=0,k,numOfsprt,flag=1;
	char rowArr[MAX_LINE];
	char *op, *op1,*status;
	
	corscsv=fopen(COURS_FILE,"r");
	corsbin=fopen(COURS_BIN,"wb");
	
	course=(course_t *) malloc(sizeof(course_t));
	if(corscsv == NULL)
	{
	    printf("\n\t\t** File error!!");
	    flag=0;
	}
	else if(course==NULL)
	{
	    printf("\n\t\t** Memory is not created!!");
	    flag=-1;
	}
	else
	{
	    status=fgets(rowArr,MAX_LINE,corscsv);
	    while(status!=NULL)
		{
		    
		    strcpy(course->courseID,strtok(rowArr,","));
		    course->courseID[strlen(course->courseID)]='\0';
		    strcpy(course->courseName,strtok(NULL,","));
		    op=strtok(NULL,",\n");
		    strcpy(course->courseInstructor,op);
		    op=strtok(NULL,"\n");
		
		    if(op!=NULL)
		    {   
		        j=0;
		        op1=strtok(op,",");
		        while(op1!=NULL)
		        {   
				    strcpy(course->prequisites[j],op1);
				    course->prequisites[j][strlen(course->prequisites[j])]='\0';
				    j++;
				    op1=strtok(NULL,",");
		        }
		    }
		    
		    course->numOfPrequisites=j;
		    course->mode='C';
		    course->grades=-1.0;
		    fwrite(course,sizeof(course_t),1,corsbin);    /*databese created*/
		    status=fgets(rowArr,MAX_LINE,corscsv);
		    i++;
		    j=0;
		}	

	}
	
	*sizeOfcourse=i;

	fclose(corscsv);
	fclose(corsbin);
	free(course);
	
	return flag;
}
int seperateStr(char command[], char operation[][MAX_LINE])
{
	int i=0;
	char *tok;
	
	tok=strtok(command,",");	/*to get first token*/
	
	while(tok!=NULL){
		strcpy(operation[i],tok);
		/*operation[strlen(operation[i])-1]='\0';*/
		tok=strtok(NULL,",");
		
		++i;
	}
	
	return i;		/*number of commands*/
}
int getUser(char *userID, user_t *user)
{
    int flag = -1,status;
    user_t tempUser;
    FILE *userbin;
    
    userbin = fopen(USER_BIN,"rb");
    do
    {
	    status = fread(&tempUser,sizeof(user_t),1,userbin);
	
	    if(status != 0)
	    {
	        if(strcmp(tempUser.userID,userID) == 0)
	        {
	            
		        if(strcmp(tempUser.userType,"2") == 0)
		        {
		            flag = 1;
		            *user = tempUser;
		        }
		        else if(strcmp(tempUser.userType,"1") == 0)
		        {
		            flag = 0;
	                *user = tempUser;
	            }
		        if(flag != -1)
		            status = 0;
	        }
	    }       
    
    }while(status != 0);
    
    fclose(userbin);
    return flag;
}
int getIns(char *insID, instructor_t *instrct)
{
    FILE *inp;
    instructor_t ins;
    int i,count=0;
    
    inp=fopen(INS_BIN,"rb");
    
    do{
        i=fread(&ins,sizeof(instructor_t),1,inp);

        if(strcmp(ins.TCnum,insID)==0)
        {
            *instrct=ins;
            fclose(inp);
            return 1;
        }

    }while(i!=0);
    
    fclose(inp);  
    return -1;
}
int getCourse(char *coursID, course_t *course)
{
    FILE *inp;
    course_t temp;
    int count=0,i;
    
    inp=fopen(COURS_BIN,"rb");
    
    do{
        i=fread(&temp,sizeof(course_t),1,inp);
        
        if((strcmp(temp.courseID,coursID))==0)
        {
            *course=temp;
            fclose(inp);
            return 1;
        }

    }while(i!=0);
    
    fclose(inp);
    return -1;
}
int getStudent(char *userID, student_t *student)
{
    FILE *inp;
    student_t stu;
    int i,count=0;
    
    inp=fopen(STD_BIN,"rb");
    
    do{
        i=fread(&stu,sizeof(student_t),1,inp);

        if(strcmp(stu.TCnum,userID)==0)
        {
            *student=stu;
            return 0;
        }
           
        count++;
    }while(i!=0);
    
    fclose(inp);  
    return -1;
}
void listCourse(course_t *course)
{
    FILE *inp;
    int i,j=0;
    
    inp=fopen(COURS_BIN,"rb");
    
    printf("\n\t\t      List of courses");
	printf("\n\t\t-----------------------------------");
    do
    {
        i=fread(course,sizeof(course_t),1,inp);
        
        if(course->isOpen==1)
            printf("\n\t\t%d).%s\t%s\tOPEN",j+1,course->courseID, course->courseName);
        else
            printf("\n\t\t%d).%s\t%s\tCLOSE",j+1,course->courseID, course->courseName);
        
        j++;
    }while(i!=0);
    
    fclose(inp);
}
int openCourse(instructor_t *instructor)
{
	FILE *corsbin;
	FILE *insbin;
	instructor_t ins, instr;
	course_t cors,course;
	user_t user;
	char select[MAX_NAME];
	int status,i=0,j=0;
	int flag=0;


	listCourse(instructor->openCourse);
		
	do{
	
		printf("\n\t\t%s, select a course ID: ",instructor->name);
		scanf("%s",select);
		
		if(getCourse(select,&cors)<0)
		    printf("\n\t\t* The selected course is not found in Database!!");
		
	}while(getCourse(select,&cors)<0);

    if(cors.isOpen==1)
    {
        printf("\n\t\t* Selected course has already opened!!");
        flag=-1;
    }
    if(flag!=-1)
    {
        if(strcmp(cors.courseInstructor,instructor->TCnum)!=0)
        {
            printf("\n\t\t* The selected course is not yours, You can't open it!!");
        }
        else
        {
            corsbin=fopen(COURS_BIN,"rb+");
            fseek(corsbin, 0, SEEK_SET);
	        
            cors.isOpen=1;
            cors.mode='O';
            instructor->openCourse[instructor->numOpCourse]=cors;
            instructor->numOpCourse++;

            do{ 	
	            status = fread(&course,sizeof(course_t),1,corsbin);
	            ++i;
	            if(strcmp(course.courseID,cors.courseID) == 0)
	            { 	

	                fseek(corsbin,sizeof(course_t)*(i-1), SEEK_SET );
	                fwrite(&cors,sizeof(course_t),1,corsbin);
	                flag =1;
	                status=0; 
	            }
                
            }while(status != 0);
            fclose(corsbin);
            
            i=0;
            status=1;
            
            insbin=fopen(INS_BIN,"rb+");
            fseek(insbin, 0, SEEK_SET);
        
            do{
                status=fread(&ins, sizeof(instructor_t),1,insbin);
                if(strcmp(ins.TCnum,instructor->TCnum)==0)
                {
                    fseek(insbin,sizeof(course_t)*(i),SEEK_SET);
                    fwrite(instructor,sizeof(instructor_t),1,insbin);
                    flag++;
                    status=0;
                    fclose(insbin);
                }
            
                ++i;
            }while(status!=0);
            printf("\n\t\t* Course was opened.\n");
        }
    }    


	return flag;
}
void listOpCourse(instructor_t *instructor, int sizeOfCourse)
{
    FILE *opCourse;
    int i,count;
    char answer[MAX_NAME];
    char skip;
    char fname[MAX_LINE];
    
    /*Listing of instructor's open courses*/
    count=listOpenedCourse(instructor);
    
    if(count<=0)
    {
        printf("\n\t\t* Yours course(s) hadn't been opened!!");
    }
    else
    {
        do{
		    /*Ask to instructor to save his/her open courses into csv file*/
    	    printf("\n\t\t* Do you want to save your open courses into csv file>(Y/N):");
    	    scanf("%s%c",answer,&skip);
	    }while(toupper(answer[0])!='Y' && toupper(answer[0])!='N');
	
	    if(toupper(answer[0])=='Y')
        {
            sprintf(fname,"%s_%s",instructor->name,instructor->surname);
            fname[strlen(fname)-1]='\0';
            strcat(fname,"_openCourses.csv");
            opCourse=fopen(fname,"w");
        
		    for(i=0; i<count; i++)
    	    {
   			    fprintf(opCourse,"%s %s %s",instructor->TCnum,instructor->openCourse[i].courseID,
									instructor->openCourse[i].courseName);
    	    }
    
        }
    }
}
int listOpenedCourse(instructor_t *instructor)
{
    int status,i, count=0;

    for(i=0; i<instructor->numOpCourse; i++)
    {
        if(instructor->openCourse[i].isOpen==1)
        {
            printf("\n\t\t*** %s %s OPEN\n",instructor->openCourse[i].courseID
                                       ,instructor->openCourse[i].courseName);
            count++;
        }
    }
    return count;
}
int finalizeCourse(instructor_t *instructor)
{
    FILE *stdbin;
    FILE *crsbin;
    char courseID[MAX_NAME];
    course_t course;
    course_t crs;
    student_t student;
    instructor_t ins;
    int status,i, notGraded=0, index, flag=0, numOfCourse;
    
    numOfCourse=listOpenedCourse(instructor);

    if(numOfCourse==0)
    {
        printf("\n\t\t* There isn't any Opened course!!");
        return -1;
    }
    
    printf("\n\t\t* Enter course ID which you want to finalize: ");
    scanf("%s",courseID);
        		
	if(getCourse(courseID,&course)<0)
	{
	    printf("\n\t\t* The selected course is not found in Database!!");
        return -1;
    }
    else
    {
        if(strcmp(course.courseInstructor,instructor->TCnum)==0)
        {
            if(course.isOpen!=1 && course.mode!='O')
            {
                printf("\n\t\t* The course isn't open, You can't finalize it.");
                return -1;
            }
            else
            {   
                stdbin=fopen(STD_BIN,"rb");
                do{        
                    status=fread(&student, sizeof(student_t),1,stdbin);
        
                    for(i=0; i<student.numOfEnCourse; i++)
                    {
                        if(strcmp(student.enrolCourse[i].courseID,courseID) == 0)
                        {
                            printf("\n\t\t*  %s %s %.2f\n",student.TCnum, student.name,
                                                 student.enrolCourse[i].grades);
                            if(student.enrolCourse[i].grades == -1)
                            notGraded++;
                        }
                    }   
                }while(status != 0);
                fclose(stdbin);
        
                if(notGraded != 0)
                {
                    printf("\n\t\t* You can't finalize this course;\n\t\t"
                                        " Some of student hadn't been graded!!");
                    return -1;
                }
                else if(notGraded == 0)
                {
                    for(i=0; i<instructor->numOpCourse; i++)
                    {
                        if(strcmp(student.enrolCourse[i].courseID,course.courseID) == 0)
                            index=i;
                    }
                    crsbin=fopen(COURS_BIN,"rb+");
                    fseek(crsbin, 0, SEEK_SET);
            
                    course.isOpen=0;
                    course.mode='C';
            
                    i=0;
                    do{
                        status=fread(&crs, sizeof(course_t),1,crsbin);
                        if(strcmp(crs.courseID,course.courseID)==0)
                        {
                            fseek(crsbin,sizeof(course_t)*(i),SEEK_SET);
                            fwrite(&course,sizeof(course_t),1,crsbin);
                            status=0;
                            printf("\n\t\t* Course is finalized.");
                        }
                
                        ++i;
                    }while(status!=0);
            
                    fclose(crsbin);
                    
                }
            }
        }
        else
            printf("\n\t\t* That course is not yours!!\n");
 
    }
    return 0;
}
void listCourses(student_t *student)
{
    FILE *encourse;
    char fname[MAX_NAME], answer[MAX_NAME], skip;
    int i;
    
    if(student->numOfEnCourse != 0)
    {
        printf("\n\t\t--- List of student's courses that enrolled ---\n");
        for(i=0; i<student->numOfEnCourse; i++)
        {
            printf("\t\t* %s %s %s\n",student->TCnum,student->enrolCourse[i].courseID,
                                 student->enrolCourse[i].courseName);
        }
    
        do{
            printf("\t\t%s, Do you want to save enrolled course into file <Y/N>? ",student->name);
            scanf("%s%c",answer,&skip);
        }while(toupper(answer[0])!='Y' && toupper(answer[0])!='N');
    
        if(toupper(answer[0])=='Y')
        {
            sprintf(fname,"%s",student->studentNum);
            fname[strlen(fname)-1]='\0';
            strcat(fname,"_courses.csv");
            encourse=fopen(fname,"w");
            
            for(i=0; i<student->numOfEnCourse; i++)
            {
                fprintf(encourse,"%s %s %s\n",student->TCnum,student->enrolCourse[i].courseID,
                                 student->enrolCourse[i].courseName);
            }
            fclose(encourse);
        }
    }
    else if(student->numOfEnCourse == 0)
    {
        printf("\n\t\t** Student has not enrolled any course\n");
    }

}
int addCourse(student_t *student)
{
	FILE *stubin;
	course_t cours;
	course_t *course;
	student_t std;
	int i,j=0,k=0,count=0;
	int status;
	char select[MAX_NAME];
	char isDone;
	int userNum;
	int flag=-1;
	
	listCourse(&cours);

	do{

		printf("\n\t\tAccording to list enter a open course ID which you want to enrol: ");
		scanf("%s",select);
		
		if(getCourse(select,&cours)<0)
		    printf("\n\t\t** The selected course was not found in Database!!\n");

	}while(getCourse(select,&cours)<0);
	
	for(i=0; i<student->numOfEnCourse; i++)
	{

    	if(strcmp(student->enrolCourse[i].courseID,cours.courseID)==0)
    	{
    	    printf("\n\t\t* Selected course has been already added!!");
    	    return -1;
    	}
	}
	
    if(cours.isOpen==1 && cours.mode=='O')
    {
        if(cours.numOfPrequisites==0)
        {
            strcpy(student->enrolCourse[student->numOfEnCourse].courseID,cours.courseID);
            strcpy(student->enrolCourse[student->numOfEnCourse].courseName,cours.courseName);
            student->numOfEnCourse++;
        }
        else
        {
            for(i=0; i<cours.numOfPrequisites; i++)
            {
                for(j=0; j<student->numOfEnCourse; j++)
                {
                    if(strcmp(cours.prequisites[i],student->previousCourse[j].courseID) == 0)
                    {
                        count++;
                    }
                }
            }
            
            if(count==cours.numOfPrequisites)
            {
                
                strcpy(student->enrolCourse[student->numOfEnCourse].courseID,cours.courseID);
                strcpy(student->enrolCourse[student->numOfEnCourse].courseName,cours.courseName);
                student->numOfEnCourse++;
            }
            else
            {
                printf("\n\t\t* You hadn't enrolled previous course of the selected course!!");
                return -1;
        	}
        }
    
        stubin=fopen(STD_BIN,"rb+");
        fseek(stubin,0,SEEK_SET);
        
        do{ 	
            status = fread(&std,sizeof(student_t),1,stubin);
            	
            if(strcmp(student->TCnum,std.TCnum) == 0)
	        { 	

	            fseek(stubin,sizeof(student_t)*(k), SEEK_SET);
	            fwrite(student,sizeof(student_t),1,stubin);
	            flag = 1;
	            status = 0;
	            printf("\n\t\t* Course was added to enrolment course");
	                  
	        }
            ++k;
        }while(status != 0);
                
        fclose(stubin);

    }
    else
    {
        printf("\n\t\t** The selected course is not open for enrolment!!");
        flag=-1;
    } 

	return flag;
}
int removeCourse(student_t *student)
{
    FILE *stubin;
    char courseID[MAX_NAME];
    int i,status,k=0,index=-1;
    course_t course;
    student_t std;
    int flag=-1;
    
    if(student->numOfEnCourse==0)
    {
        printf("\n\t\t* You haven't any enrolled course!!");
    }
    else
    {
        printf("\n\t\t*** LIST of ENROL COURSES ***\n");
        for(i=0; i<student->numOfEnCourse; i++)
        {
            printf("\n\t\t  * %s %s ",student->enrolCourse[i].courseID,
                                    student->enrolCourse[i].courseName);
        }
        
        do{
            printf("\n\t\t* Enter course ID that you want to remove: ");
            scanf("%s",courseID);
            
            if(getCourse(courseID,&course)<0)
		        printf("\n\t\t* The selected course was not found in Database!!\n");
        
        }while(getCourse(courseID,&course)<0);
        
        for(i=0; i<student->numOfEnCourse; i++)
        {
            if(strcmp(student->enrolCourse[i].courseID,course.courseID) == 0)
                index=i;
        }
        if(index==-1)
        {
            printf("\n\t\tYou aren't enrol %s!!",courseID);
        }
        else
        {
            if(index==student->numOfEnCourse-1)
            {
                student->numOfEnCourse--;
            }
            else
            {
                for(i=index; i<student->numOfEnCourse; i++)
                {
                    if((i+1)!=student->numOfEnCourse)
                        student->enrolCourse[i]=student->enrolCourse[i+1];
                }
                student->numOfEnCourse--;
            }
        
            /*update database*/
            stubin=fopen(STD_BIN,"rb+");
            fseek(stubin,0,SEEK_SET);
        
            do{ 	
	            status = fread(&std,sizeof(student_t),1,stubin);
	        
	            if(strcmp(student->TCnum,std.TCnum) == 0)
	            { 	

    	            fseek(stubin,sizeof(student_t)*(k), SEEK_SET);
    	            fwrite(student,sizeof(student_t),1,stubin);
    	            flag =1;
    	            status=0;
    	            fclose(stubin);
    	            
    	        }
                ++k;
            }while(status != 0);
        
            if(flag == 1)
            {
                printf("\n\t\t* Course was removed!!");
            }
        }
    }
    return flag;
}
int assignGrade(instructor_t *instructor)
{
    FILE *stdbin;
    int status=0,i,j=0;
    int numOfCourse=0,stdCount=0;
    char studentID[TC], courseID[TC];
    char skip;
    course_t course;
    student_t STD;
    student_t student;
    
    /*Acık olan dersler listelendi*/
    numOfCourse=listOpenedCourse(instructor);
    
    
    if(numOfCourse==0)
    {
        printf("\n\t\t* There is no open course.");
        return -1;
    }
    
    /*Notlandirilacak dersin secimi*/
    do{
    
        printf("\n\t\t* Plase enter course ID which you want to assign grade: ");
        scanf("%s",courseID);
        
        status=getCourse(courseID,&course);
        if(status==-1)
	        printf("\n\t\t* The selected course is not found in Database!!\n");

    }while(status<0);
    
    if(course.isOpen!=1 && course.mode!='O')
    {
        printf("\n\t\t* The course is not open, You can't assigning grade at that course.");
        return -1;
    }
    else
    {
        /*derse kayitli ogrencilerin listesi*/
        stdbin=fopen(STD_BIN,"rb");
        do{
            status=fread(&STD,sizeof(student_t),1,stdbin);
            
            for(i=0; i<STD.numOfEnCourse; i++)
            {
                if(strcmp(STD.enrolCourse[i].courseID,courseID)==0)
                {
                    printf("\n\t\t* %s %s %s",STD.TCnum, STD.name,STD.surname);
                    stdCount++;
                }
        
            }
            
            i=0;
        }while(status!=0);
        fclose(stdbin);
        
        if(stdCount==0)
        {
            printf("\n\t\t* There is no enrolment student in that course!!");
            return -1;
        }
        
        else
        {
            do{
        
                printf("\n\t\t- Enter student ID which enrolled course: ");
                scanf("%s%c",studentID,&skip);
        
                status=getStudent(studentID,&student);
                if(status!=0)
                {
                    printf("\n\t\t* Student wasn't found!!");
                }
            
            }while(status<0);
        

            for(i=0; i<student.numOfEnCourse; i++)
            {
                if(strcmp(student.enrolCourse[i].courseID,courseID) == 0)
                {
                    printf("\n\t\t* Enter student's grade: ");
                    scanf("%lf",&student.enrolCourse[i].grades);
                    
                    stdbin=fopen(STD_BIN,"rb+");
                    fseek(stdbin, 0, SEEK_SET);
                
                    do{ 	
	                    status = fread(&STD,sizeof(student_t),1,stdbin);
	        
	                    if(strcmp(student.TCnum,STD.TCnum) == 0)
	                    { 	

    	                    fseek(stdbin,sizeof(student_t)*(j), SEEK_SET);
    	                    fwrite(&student,sizeof(student_t),1,stdbin);
    	                    status=0;
    	                    
    	                } 
                
                        ++j;
                    }while(status != 0);
                    
                    fclose(stdbin);
                    i=student.numOfEnCourse;
                }
            }       
        }
    }    
      
    return 0;
}
int listGrades(instructor_t *instructor)
{
    FILE *stdbin;
    FILE *crsgrade;
    student_t student;
    course_t course;
    char courseID[MAX_NAME], answer[MAX_NAME],
         fname[MAX_NAME], skip;
    int status,numStd=0,i;
    
    listOpenedCourse(instructor);
    
   	do{
	
	    printf("\n\t\t* Please, enter course ID for listing grades of students: ");
        scanf("%s",courseID);
		
	    if(getCourse(courseID,&course)<0)
	        printf("\n\t\t* The selected course is not found in Database!!\n");
    
    }while(getCourse(courseID,&course)<0);
    
    stdbin=fopen(STD_BIN,"rb");
    do{        
        status=fread(&student, sizeof(student_t),1,stdbin);
        
        for(i=0; i<student.numOfEnCourse; i++)
        {
            if(strcmp(student.enrolCourse[i].courseID,courseID) == 0)
            {
                printf("\n\t\t  *  %s %s %.2f\n",student.TCnum, student.name, student.enrolCourse[i].grades);
                ++numStd;
            }
        }   
    }while(status != 0);
    fclose(stdbin);
        
    if(numStd==0)
    {
        printf("\n\t\t** There is not found enrolment student in that course!!\n");
        return -1;
    }
    else
    {    
        do{
       
            printf("\n\t\t%s, Do you want to save students grade into file<Y/N> ",instructor->name);
            scanf("%s%c",answer,&skip);
            
        }while(toupper(answer[0])!='Y' && toupper(answer[0])!='N');

        if(toupper(answer[0])=='Y')
        {
            sprintf(fname,"%s",courseID);
            fname[strlen(fname)]='\0';
            strcat(fname,"_grades.csv");
            crsgrade=fopen(fname,"w");
            
            stdbin=fopen(STD_BIN,"rb");
            do{
        
                status=fread(&student, sizeof(student_t),1,stdbin);
        
                for(i=0; i<student.numOfEnCourse; i++)
                {
                    if(strcmp(student.enrolCourse[i].courseID,courseID) == 0)
                    {
                        fprintf(crsgrade,"%s %s %.2f",student.TCnum, student.name, student.enrolCourse[i].grades);
                    }
                }   
            }while(status != 0);
        
            fclose(crsgrade);
            fclose(stdbin);
        }
    }
    
    return 0;
}

