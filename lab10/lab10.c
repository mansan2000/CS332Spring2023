//I, __Emanuel Sanders_____, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.
//
//Student Signature/Initials: ___JES_________
//
//        Date: __4/5/2023__________

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

void parseCommand(char *command, char ***array, int *numTokens) {
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL) {
        *array = realloc(*array, (i + 1) * sizeof(char *));
        (*array)[i] = malloc(strlen(token) + 1);
        strcpy((*array)[i], token);
        i++;
        token = strtok(NULL, " ");
    }
    *numTokens = i;
}

void forkFunc(char *command) {
    // pass *command to parseCommand and return argsArray with space seperated commands in the array
    int len = strlen(command);
    char *cmd = malloc((len + 1) * sizeof(char));
    strcpy(cmd, command);
    char **argsArray = NULL;
    int numTokens;
    parseCommand(cmd, &argsArray, &numTokens);

    // now append the target file and the null character to the argsArray
    argsArray = realloc(argsArray, (numTokens + 2) * sizeof(char *));
    argsArray[numTokens + 1] = NULL;

    pid_t pid;
    int status;


    pid = fork();
    if (pid == 0) { /* this is child process */
        char outFile [40];
        char errFile [40];
        sprintf(outFile, "%d.out", getpid());
        sprintf(errFile, "%d.err", getpid());
        int fdout = open(outFile, O_WRONLY | O_CREAT);
        int fderr = open(errFile, O_WRONLY | O_CREAT);
        dup2(fdout, STDOUT_FILENO);
        dup2(fderr, STDERR_FILENO);
        close(fdout);
        close(fderr);
        execvp(argsArray[0], argsArray);
        printf("If you see this statement then execl failed ;-(\n");
        perror("execv");
        exit(-1);
    } else if (pid > 0) { /* this is the parent process */
//        printf("Wait for the child process to terminate\n");
        wait(&status); /* wait for the child process to terminate */
        if (WIFEXITED(status)) { /* child process terminated normally */
//            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else { /* child process did not terminate normally */
//            printf("Child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine
               how the child process was terminated */
        }
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }

//    printf("[%ld]: Exiting program .....\n", (long)getpid());
}


int main(int argc, char **argv) {
    FILE *fp;
    FILE *fp2;
    char buff [BUFSIZ];
    fp = fopen(argv[1], "r");
    fp2 = fopen("output.log", "w");
    // Read each line from the file
    while(fgets(buff, BUFSIZ, (FILE*)fp)){
        if (strlen(buff) > 0 && buff[strlen(buff)-1] == '\n'){
            buff[strlen(buff)-1] = 0;
        }
        // start timer
        time_t start_time = time(NULL);
        // call fork function
        forkFunc(buff);
        // end timer
        time_t end_time = time(NULL);

        // format start and end timer by removing the newline char from the end
        char *startDate = ctime(&start_time);
        startDate[strlen(startDate)-1] = '\0';
        char *endDate = ctime(&end_time);
        endDate[strlen(endDate)-1] = '\0';

        //write to the output file
        fprintf(fp2,"%s    %s    %s\n",buff, startDate,endDate);
    }

    fclose(fp2);
    fclose(fp);

    return 0;
}
