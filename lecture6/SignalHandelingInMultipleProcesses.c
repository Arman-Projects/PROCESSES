#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <signal.h>
void foo(int sig) {
    if(sig == SIGUSR1){
        printf("signal SIGUSR1 number %d finished\n", sig);
    } else if (sig == SIGUSR2) {
        printf("signal SIGUSR2 number %d finished\n", sig);
    } else if (sig == SIGTERM) {
        printf("signal SIGTERM number %d finished\n", sig);
    } else {
        printf("other signal number %d finished\n", sig);
    }
    exit(0);
}

int main() { 
    pid_t pids[3];
    pids[0] = fork();

    if (pids[0] < 0) {
        exit(1);
    } else if (pids[0] == 0) {
        struct sigaction s0;
        s0.sa_flags = 0;
        s0.sa_handler = foo;
        sigemptyset(&s0.sa_mask);
        sigaction(SIGUSR1, &s0, NULL);
       // signal(SIGUSR1, foo0);
        pause();
    } else {
        sleep(1);
        kill(pids[0], SIGUSR1);
        wait(NULL);
        pids[1] = fork();
        if (pids[1] < 0) {
            exit(0);
        } else if (pids[1] == 0) {
            struct sigaction s1;
            s1.sa_flags = 0;
            s1.sa_handler = foo;
            sigemptyset(&s1.sa_mask);
            sigaction(SIGTERM, &s1, NULL);
            pause();
        } else {
            sleep(1);
            kill(pids[1], SIGTERM);
            wait(NULL);
            pids[2] = fork();
            if(pids[2] < 0) {
                exit(0);
            } else if (!pids[2]) {
                signal(SIGUSR2, foo);
                pause();
            } else {
                sleep(1);
                kill(pids[2], SIGUSR2);
                wait(NULL);
            }
        }
    }
}
