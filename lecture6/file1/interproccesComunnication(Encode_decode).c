//Demo code 
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int res = 0;
int _index = 0;
pid_t pid;

void sig1(int sig) {
    if (sig == SIGUSR1) {
        printf("signal is SIGUSR1");
        ++_index;
    } else if (sig == SIGUSR2) {
        printf("signal is SIGUSR2");
        res |= 1 << _index;
        ++_index;
    }

}

int main(char* argv[], int argc) {
    pid = getpid();
    printf("Current PID: %d\n", getpid());
    signal(SIGUSR1, sig1);
    signal(SIGUSR2, sig1);
    /* Gtnel poxancvac pid-i amboxj tvayiny */ 
    sigqueue (pid, sigalrm, (union sigval) getpid())
    for (int i = 0; i < sizeof(int) * 8; i++) {
        pause(); // Wait for a signal
    }

    printf("RESULT IS %d\n", res);
}
