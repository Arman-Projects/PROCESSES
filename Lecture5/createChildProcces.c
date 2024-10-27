#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void create_child_process() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        
        int *ptr = NULL;
        *ptr = 42; 
        
        exit(EXIT_SUCCESS);
    } else { 
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
        
        int status;
        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal: %d\n", WTERMSIG(status));
        } else {
            printf("Child process exited normally.\n");
        }
    }
}

int main() {
    create_child_process();
    return 0;
}


