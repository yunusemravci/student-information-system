
#include "PR_111044040.h"


int main(int argc, char *argv[])
{

    user_t user;
    course_t course[10];
    int type, sizeOfcourse;

    if(controlBinFiles(sizeOfcourse)<0)
    {
        printf("\n\t\t** Error about files!!\n");
        return -1;
    }
    else
    {
        if(argc>2)
        {
            type=getUser(argv[1], &user);
            user.password[strlen(user.password)-1]='\0';
        
            if(strcmp(argv[2],user.password)==0)
                menu(type,user.userID,sizeOfcourse);
            else if(type == -1)
            {
                printf("\n\t\t->>>User is not found!!\n");
            }
            else
            {
                printf("\n\t\t*** User name or Password is WRONG!!***\n");
                return -1;
            }   
        }
        else
        {
            printf("\n\t\tEXECUTE: %s <ID> <PASSWORD>\n",argv[0]);
        }
    }
   
   return 0;
}
