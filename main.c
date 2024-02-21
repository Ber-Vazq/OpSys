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
#include <unistd.h>;
#include <sys/types.h>;
#include <sys/wait.h>;

#define MAX_ARGS 10

void showpid(int idList[])
{
    int i = 0;
    for (i = 0; i < idList[i]; i++)
    {
        printf("%d\n", idList[i]);
    }
    return;
}
void chgDir(char *path, char *currDir)
{
    if (chdir(path) == -1)
    {
        printf("Error: cannot change directory\n");
        return;
    }
    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd() error");
    }
    setenv("pwd", currDir, 1);
}

int main(int argc, char **argv)
{
    char str[1000];
    char currDir[1000];
    char *command;
    char *tokenArr; // token array
    char *argList[MAX_ARGS];
    int i;

    // get current directory
    if ((getcwd(currDir, 1000)) == NULL)
    {
        perror("getcwd"); // print error if necessary
        return 1;         // error indication
    }

    for (i = 0; i < 10; i++) // malloc pointer w length 81 then init it to null
    {
        argList[i] = (char *)malloc(sizeof(char) * 81);
        argList[i] = NULL;
    }

    while (1)
    {
        // making the prompt better
        printf("\033[0;31m%s$ ", currDir);
        printf("\033[0m");
        // this is so we can read the input from user
        if (fgets(str, sizeof(str), stdin) != NULL)
        {
            fprintf(stderr, "Error reading input, please fix.\n");
            break; // exit if error
        }
        str[strcspn(str, "\n")] = '\0'; // remove traling newline if there

        tokenArr = strtok(str, " ");
        int argCount = 0;
        while (tokenArr != NULL)
        {
            if (i == 0)
            {
                command = strdup(tokenArr);
            }
            argList[i] = strdup(tokenArr);
            tokenArr = strtok(NULL, " ");
            i++;
        }
        if (strncmp(str, "exit", 4) == 0) // from lecture, checking if input matches exit cmd
        {
            printf("EXITING!\n");
            break;
        }
        if (strcmp(command, "cd") == 0)
        {
            chgDir(argList[1], currDir);
        }
        else if (strcmp(command, "showpid") == 0)
        {
            showpid(NULL);
        }
        else
        {
            int execStatus; // just to make it work because it was yelling at me
            pid_t pid = fork();
            if (pid == 0)
            {
                execStatus = execvp(command, argList);
                if (execStatus == -1)
                {
                    printf("Error: Command could not be executed\n");
                    exit(1);
                }
                else
                {                          // parent
                    waitpid(pid, NULL, 0); // wait for your child please
                }
                kill(pid, SIGTERM);
            }
        }

        for (int i = 0; i < argCount; i++)
        {
            free(argList[i]);
        }
    }
    for (int i = 0; i < MAX_ARGS; i++)
    {
        free(argList[i]);
    }
    return 0;
}