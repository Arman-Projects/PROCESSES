#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int res = 0;
int ind = 0;

void  alarm_handler (int )
{
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
        struct sigaction s1;
        struct sigaction s2;
        sigfillset(&s1.sa_mask);
        sigfillset(&s2.sa_mask);
        signal(SIGUSR1,sign);
        signal(SIGUSR2,sign);
        for (int i = 0; i < 32;  i++) {
            pause();
            kill (getppid(), SIGALRM);
        }
        printf("Result is: %d \n", res);
        
    } else {
        int num;
        printf("print num: ");
        signal (SIGALRM, alarm_handler);
        //scanf("%d", &num);
        num = (((1 << 10) + 1) << 10) + 1;
        sleep(2);
        printf ("num=%d \n", num);
        int i = 32;
        while(i) {
            int tmp = num % 2;
            if(tmp) {
                kill(pid,SIGUSR2);
                //printf("%d",tmp);
            } else {
                kill(pid, SIGUSR1);
                //printf("%d",tmp);
            }
            pause ();
            num /= 2;
            --i;
        }
                printf("\n");
    wait(NULL);
    }

    return 0;
}

