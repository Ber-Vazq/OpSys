/*
Requirements for Project 1:
-Prompt the user
--make prompt different color from command
-able to parse commands from command line
-execute commands
-built ins
---Exit
---cd[PATH]
---showpid()
*/

#include <stdio.h>;
#include <stdlib.h>;
#include <string.h>;

#define MAX_ARGS 10

int main(int argc, char **argv){
    char str[1000];
    char currDir[1000];
    char *command;
    char* tokenArr; //token array
    char* argList[MAX_ARGS];
    int i;

    //get current directory
    if((getcwd(currDir,1000))== NULL){
        perror("getcwd"); //print error if necessary
        return 1;//error indication
    }

    for (i = 0; i < 10; i++)//malloc pointer w length 81 then init it to null
    {
        argList[i] = (char*)malloc(sizeof(char)*81);
        argList[i] = NULL;
    }
    

    while(1){
        //making the prompt better
        printf("\033[0;31m%s$ ", currDir);
        printf("\033[0m");
        //this is so we can read the input from user
        if(fgets(str, sizeof(str), stdin)!= NULL){
            fprintf(stderr, "Error reading input, please fix.\n");
            break;//exit if error
        }
        str[strcspn(str, "\n")] = '\0';//remove traling newline if there

        tokenArr = strtok(str, " ");
        int argCount = 0;
        while (tokenArr != NULL){
            if (i == 0){
                command = strdup(tokenArr);
            }
            argList[i] = strdup(tokenArr);
            tokenArr = strtok(NULL," ");
            i++;
        }

        

        if (strncmp(str, "exit",4)==0)//from lecture, checking if input matches exit cmd
        {
            printf("EXITING!\n");
            break;
        }
        for (int i = 0; i < argCount; i++){
            free(argList[i]);
        }
    }
    for (int i = 0; i < MAX_ARGS; i++){
        free(argList[i]);
    }
    return 0;
}