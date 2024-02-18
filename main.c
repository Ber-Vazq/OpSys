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


int main(int argc, char **argv){
    char str[1000];

    while(1){
        //this is so we can read the input from user
        if(fgets(str, sizeof(str), stdin)!= NULL){
            fprintf(stderr, "Error reading input, please fix.\n");
            break;//exit if error
        }

        str[strcspn(str, "\n")] = '\0';//remove traling newline if there

        if (strncmp(str, "exit",4)==0)
        {
            printf("EXITING!\n");
            break;
        }
        
    }
}