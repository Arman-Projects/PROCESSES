#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t num;
    printf("PRINT PID: ");
    scanf("%d", &num);
    int n;
    scanf("%d", &n);
    int tmp;
    int i = 31;
    while(i) {
        tmp = n%2;
        if(tmp == 0) {
            kill(num, SIGUSR1); 

        } else if(tmp == 1) {
            kill(num, SIGUSR2);
        }
        usleep(100);
        n = n/2;
        --i;
    }
    
    return 0;
}
