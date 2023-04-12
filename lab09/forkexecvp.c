/* Simple program to illustrate the use of fork-exec-wait pattern.
 * This version uses execvp and command-line arguments to create a new process.
 * To Compile: gcc -Wall forkexecvp.c
 * To Run: ./a.out <command> [args]
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t childPID;
static void sig_int(int signo) {
    ssize_t n;
    char buf[2];

    printf("%lld\n", childPID);
    printf("%d\n", signo);
    signal(signo, SIG_IGN); /* ignore signal first */
    printf("Do you really want to do this: [Y/N]? ");
    fflush(stdout);
    n = read(STDIN_FILENO, buf, 2);
    if ( buf[0] == 'Y' ) {
//        raise(SIGTERM, childPID); // or kill(0, SIGTERM); // or exit (-1);
        int ret = kill(childPID, SIGTERM);
        printf("Ret: %d\n", ret);
    } else {
        printf("Ignoring signal, be careful next time!\n");
        fflush(stdout);
    }
    signal(signo, sig_int); /* reinstall the signal handler */
}

int main(int argc, char **argv) {
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("Unable to catch SIGINT\n");
        exit(-1);
    }
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    childPID = fork();
    if (childPID == 0) { /* this is child process */
        execvp(argv[1], &argv[1]);
        printf("If you see this statement then execl failed ;-(\n");
        perror("execvp");
        exit(-1);
    } else if (childPID > 0) { /* this is the parent process */
        while (childPID != 0){
            printf("Wait for the child process to terminate\n");
            sleep(1);

        }
        wait(&status); /* wait for the child process to terminate */
        if (WIFEXITED(status)) { /* child process terminated normally */
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else { /* child process did not terminate normally */
            printf("Child process did not terminate normally!\n");
            /* look at the man page for wait (man 2 wait) to determine
               how the child process was terminated */
        }
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }

    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}