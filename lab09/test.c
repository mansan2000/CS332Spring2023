#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid;

void sigint_handler(int sig) {
    if (child_pid != 0) {
        kill(child_pid, SIGTERM);

    }
}
void sigtstp_handler(int sig) {
    if (child_pid != 0) {
        kill(child_pid, SIGTSTP);
    }
}

void sigquit_handler(int sig) {
    kill(child_pid, SIGQUIT);
    exit(EXIT_SUCCESS);
}
int main(int argc, char **argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGQUIT, sigquit_handler);
    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    child_pid = fork(); // create child process

    if (child_pid == 0) {
        // child process code
        signal(SIGINT, SIG_IGN); // ignore SIGINT signal in child process
        signal(SIGTSTP, SIG_IGN);
        execvp(argv[1], &argv[1]); // execute command in child process
        perror("execvp"); // print error message if execvp fails
        exit(-1);
    } else {
        // parent process code
        int status;
        while (child_pid != 0) {
            printf("Parent is still running.\n");
            sleep(1);
            waitpid(child_pid, &status, WNOHANG); // check if child process has terminated
            if (WIFEXITED(status)) { // child process terminated normally
                printf("Child process exited with status = %d\n", WEXITSTATUS(status));
//                child_pid = 0; // set child process ID to 0 to indicate it's not running
            } else if (WIFSIGNALED(status)) { // child process terminated due to a signal
                printf("Child process terminated due to signal %d\n", WTERMSIG(status));
//                child_pid = 0; // set child process ID to 0 to indicate it's not running
            }
        }
    }

    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}
