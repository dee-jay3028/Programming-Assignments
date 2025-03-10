//Homework 1- Daxton Johnson

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

//Function Declarations

int parseInput(char*, char splitWords[][500], int);

int executeCommand(char* const*, const char*, const char*);

void changeDirectories(const char*);

//Main function for the shell, continually loops for user input until "exit" is entered. Prints my netid followed by the current working directory and a $, then prompts for input. 

int main(){

    //Setting up character arrays:
    char rawInput[1000];
    char parsedInput[100][500];
    char currentDirectory[500];
    int numArgs;

    //Main program loop:
    while(1){
        getcwd(currentDirectory, 100);
        printf("daxtonj:%s$ ", currentDirectory);
        fgets(rawInput, 1000, stdin);
        size_t length = strlen(rawInput);
        if(rawInput[length - 1] == '\n'){
            rawInput[length - 1] = '\0';
        }

        //Parse user input and store number of arguments
        numArgs = parseInput(rawInput, parsedInput, 100);

        //Handle directory changes
        if(strcmp(parsedInput[0], "cd") == 0){
            if(numArgs != 2){
                printf("Path Not Formatted Correctly!\n");
                continue;
            }
            changeDirectories(parsedInput[1]);
            continue;
        }

        //Handle exit command
        if(strcmp(parsedInput[0], "exit") == 0){
            break;
        }

        //File redirection handling
        char* outfile = "";
        char* infile = "";
        int fileRedir = 0;
        int i = 0;
        while(i < numArgs){
            if(strcmp(parsedInput[i], ">") == 0 && fileRedir == 0){
                fileRedir = 1;
                i++;
                outfile = parsedInput[i];
                continue;
            }
            if(strcmp(parsedInput[i], "<") == 0 && fileRedir == 0){
                fileRedir = 1;
                i++;
                infile = parsedInput[i];
                continue;
            }
            i++;
        }

        //Once we have determined whether there is file redirection, we create a dynamic array to pass to executeCommand:
        int trueSize = (numArgs-(fileRedir*2)+1);
        char** userCommand = (char**)malloc(trueSize*sizeof(char*));
        i=0;
        while(i < trueSize){
            userCommand[i] = (char*)malloc(strlen(parsedInput[i])*sizeof(char));
            strcpy(userCommand[i], parsedInput[i]);
            i++;
        }
        userCommand[trueSize-1] = NULL;

        /*i=0;
        while(i < trueSize-1){
            printf("%s\n",userCommand[i]);
            i++;
        }*/
        //printf("Outfile: %s\nInfile: %s\n", outfile, infile);

        executeCommand(userCommand, infile, outfile);

        //Free memory used by userCommand and loop back to start
        i=0;
        for(i = 0; i < trueSize-1; i++){
            free(userCommand[i]);
        }
        free(userCommand);
    }
    return 0;
}

//Parse c string of raw user input using strtok() to break into tokens
int parseInput(char* input, char splitWords[][500], int maxWords){
    char* currentToken;
    int i = 0;
    currentToken = strtok(input, " ");
    while(currentToken != NULL && i < maxWords){
        strcpy(splitWords[i], currentToken);
        currentToken = strtok(NULL, " ");
        i++;
    }
    return i;
}

//Function to create a child process to execute user commands
int executeCommand(char* const* enteredCommand, const char* infile, const char* outfile){

    //Fork Program and disambiguate based on return value of fork()
    int childStatus;
    int forkResult = fork();

    //IN CHILD PROGRAM:
    if(forkResult == 0){
        //printf("Child Process Running with PID: %d\n", getpid());

        //Handle file redirection
        //printf("Outfile: %s\nInfile: %s\n", outfile, infile);
        int fd;
        if(strcmp(infile, "") != 0){
            fd = open(infile, O_RDONLY, 0666);
            if(fd == -1){
                printf("file Error: %s\n", strerror(errno));
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
        } else if (strcmp(outfile, "") != 0){
            fd = open(outfile, O_WRONLY|O_CREAT|O_TRUNC, 0666);
            if(fd == -1){
                printf("file Error: %s\n", strerror(errno));
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
        }

        //Execute user command, pass args, & handle errors
        if(execvp(enteredCommand[0], enteredCommand) == -1){
                printf("exec Failed: %s\n", strerror(errno));
                exit(1);
        }
        close(fd);

        //Exit child process and return status 0
        exit(0);

    //IF FORK FAILED:
    } else if (forkResult == -1){
        printf("fork Failed: %s\n", strerror(errno));
    }

    //IN PARENT PROGRAM:
    else{
        //printf("Parent Process Waiting with PID: %d\n", getpid());
        wait(&childStatus);
        printf("Child finished with error status: %d\n", childStatus);
    }
    return childStatus;
}

//Function to handle changing current working directory of shell
void changeDirectories(const char* path){
    if(chdir(path) == -1){
        printf("chdir Failed: %s\n", strerror(errno));
    }
}