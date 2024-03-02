/*
 * A simple wrapper to execute init after loading some modules.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        if (execlp("modprobe", "modprobe", "hv_vmbus", NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
        // Should never reach here if execlp succeeds
    } else {
        // Parent process
        int status;
        // Wait for the child to finish
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // If modprobe succeeds, replace the current process with /init
            if (execv("/init", argv) == -1) {
                perror("execv failed");
                exit(EXIT_FAILURE);
            }
            // Should never reach here if execv succeeds
        } else {
            printf("modprobe failed\n");
        }
    }

    return 0;
}
