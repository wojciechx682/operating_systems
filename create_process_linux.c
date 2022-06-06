#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int input_argument; 

int global=0;

int main(int argc, char *argv[])
{
    int status;
    int status1;
    int count = argc;    
    
    if(count-1 != 1)
    {
        fprintf(stderr,"\nNależy podać dokładnie jeden argument! \n\n");        
        return 1;        
    }

    input_argument = atoi(argv[1]);   

    if(input_argument == 0)
    {
        fprintf(stderr,"\nPodaj liczbę naturalną! \n\n");        
        return 2;
    }

    if(!(input_argument > 0 && input_argument < 14))
    {
        fprintf(stderr,"\nPodaj liczbę z przedziału <1,...,13> !\n\n");        
        return 3;
    }

    if(input_argument == 1 || input_argument == 2)
    {        
        return 1;
    }
    else
    {
        pid_t parent = getpid();
        pid_t pid = fork();       
        
        if(pid==0) 
        {            
            int argument = atoi(argv[1]);
            argument=argument-1;
            char str[10];
            sprintf(str, "%d \n", argument);

            char *argv[3] = {"./a", str, NULL};    
           
            return execvp("./a", argv);    
        }

        pid_t pid1 = fork();
          
        if(pid1==0) 
        {
            int argument = atoi(argv[1]);
            argument=argument-2;
            char str[10];
            sprintf(str, "%d \n", argument);
            char *argv[3] = {"./a", str, NULL};  
            
            return execvp("./a", argv); 
        }  
           waitpid(pid, &status, 0);
           waitpid(pid1, &status1, 0);
           if (pid >0)
           {
                printf("%d %d %d %d \n", getpid(), pid, input_argument-1,WEXITSTATUS(status));
           }
           
            int sum = WEXITSTATUS(status)+WEXITSTATUS(status1);
            if (pid >0)
            {
                printf("%d %d %d %d \n", getpid(), pid1, input_argument-2,WEXITSTATUS(status1));
            }

            printf("%d        %d \n", getpid(), sum);
            printf("\n");
            
    }  
    int sum = WEXITSTATUS(status)+WEXITSTATUS(status1);
    return sum;    
}       

