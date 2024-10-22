#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
int main() {
	pid_t pids[2];
	pids[0] = fork();
	
	if(pids[0] < 0) {
		return 1;
	} else if (!pids[0]) {
		char * command = (char*)malloc(sizeof(char) * 20);
		scanf("%[^\n]", command);
		getchar();
		system(command);
	} else {
		wait(NULL);
		printf("CHILD IS FINISHED");
	}
return 0;
}
