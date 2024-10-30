#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int res = 0;
int ind = 0;

void  alarm_handler (int ) {
    printf ("CHLP \n");
}

void sign(int sig) {
    if(sig == SIGUSR1) {
        printf("SIGNAL: %d SIGUSR1\n", sig);
        ++ind;
    } else if (sig == SIGUSR2) {
        printf("SIGNAL: %d SIGUSR2\n", sig);
        res |= 1 << ind;
        ++ind;
    }
    return;
}

int main () {
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid == 0) {
        signal(SIGUSR1,sign);
        signal(SIGUSR2,sign);
        for (int i = 0; i < 32;  i++) {
            pause();
            kill (getppid(), SIGALRM);
        }
        printf("Result is: %d \n", res);
        
    } else {
        int num;
        printf("print num: \n");
        signal (SIGALRM, alarm_handler);
        scanf("%d", &num);
        printf ("num=%d \n", num);
        int i = 31;
        while(i != -1) {
            int tmp = num % 2;
            if(tmp) {
                kill(pid,SIGUSR2);
            } else {
                kill(pid, SIGUSR1);
            }
            pause ();
            num /= 2;
            --i;
        }
    wait(NULL);
    }

    return 0;
}
