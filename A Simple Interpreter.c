/*************************************
* Lab 2 Exercise 3
* Name:
* Matric No:
* Lab Group:
*************************************/

//Note that the spcific header files may be different across Linux,
//Solaris or BSD (Mac OS). do a "man XXXX" to check what are the correct
//header files on your system. The given header files are for Linux.

//Remember to use the Linux version in your submission as we will mark
//your assingmnet on Linux :-)

#include <stdio.h>
#include <fcntl.h>      //For stat()
#include <sys/types.h>   
#include <sys/stat.h>
#include <unistd.h>     //for fork(), wait()

int main()
{
    char request;
    char leftover[40];  //for cleaning up the left over inputs
    char input[40], commandPath[20], command[20], arg1[20], arg2[20], arg3[20], arg4[20];
    struct stat status;
    int job_pid;
    int job_pids[10], count = 0;
    int i, j, y, nbytes = 40, args = 0;
    //read user input
    printf("YWIMC > ");
    scanf("%c", &request);
    while (request != 'Q'){
        // Handle 'R' request
        
        if(request == 'R' || request == 'B'){
            fgets(input, 40, stdin);
            for(i = 0; input[i] == ' '; i++);   //clean the white space
            for(j = 0; input[i] != ' ' && input[i] != '\n'; i++, j++){
                commandPath[j] = input[i];
            }
            commandPath[j] = '\0';
            if(stat(commandPath, &status) != 0){
                printf("%s not found\n", commandPath);
            }
            else{
                y = fork();
                if(y == 0){
                    int k;
                    for(k = 0; commandPath[k] != '\0'; k++);
                    for(k--; k >= 0 && commandPath[k] != '/'; k--);
                    for(j = 0, k++; commandPath[k] != '\0'; k++){
                        command[j++] = commandPath[k];
                    }
                    command[j] = '\0';
                    
                    for(; input[i] == ' '; i++);   //clean the white space
                    if(input[i] == '\n')
                        execl(commandPath, command, NULL);
                        
                    for(j = 0; input[i] != ' ' && input[i] != '\n'; i++, j++){
                        arg1[j] = input[i];
                    }
                    arg1[j] = '\0';
                    for(; input[i] == ' '; i++);   //clean the white space
                    if(input[i] == '\n')
                        execl(commandPath, command, arg1, NULL);
                        
                    for(j = 0; input[i] != ' ' && input[i] != '\n'; i++, j++){
                        arg2[j] = input[i];
                    }
                    arg2[j] = '\0';
                    for(; input[i] == ' '; i++);   //clean the white space
                    if(input[i] == '\n')
                        execl(commandPath, command, arg1, arg2, NULL);
                        
                    for(j = 0; input[i] != ' ' && input[i] != '\n'; i++, j++){
                        arg3[j] = input[i];
                    }
                    arg3[j] = '\0';
                    for(; input[i] == ' '; i++);   //clean the white space
                    if(input[i] == '\n')
                        execl(commandPath, command, arg1, arg2, arg3, NULL);
                        
                    for(j = 0; input[i] != ' ' && input[i] != '\n'; i++, j++){
                        arg4[j] = input[i];
                    }
                    arg4[j] = '\0';                   
                    execl(commandPath, command, arg1, arg2, arg3, arg4, NULL);
                        
                }
                if(request == 'R'){
                    wait(NULL);
                }
                else if(request == 'B'){
                    job_pids[count++] = y;
                    printf("Child %d in background\n", y);
                }
            }
            
        }
        else if(request == 'W'){
            scanf("%d", &job_pid);
            for(i = 0; i <= count; i++){
                if(job_pids[i] == job_pid)
                    break;
            }
            if(i > count){
                printf("%d not a valid child\n", job_pid);
            }
            else{
                waitpid(job_pid, NULL, 0);
            }
            
            fgets(leftover, 40, stdin); //clean up left over to ready for
                                    // next input
        }
        
        
        
        
        

        printf("YWIMC > ");
        scanf("%c", &request);
    }
    
    printf("Goodbye!\n");
    return 0;

}
