#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *commands[] = {"ls", "pwd", "whoami", "date"};
    pid_t pids[4];
    for (int i = 0; i < 4; i++) {
        pids[i] = fork();
        if (pids[i] < 0) return 1;
            else if (pids[i] == 0) {
                execl("/bin/zsh", "zsh", "-c", commands[i], NULL);
                perror("exex failed\n");
                return 1;
            } else {
                wait(NULL);
                printf("%d child is finsihed\n", pids[i]);
            }
    }    
    return 0;
}
