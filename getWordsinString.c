#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#define size 4096

int main() {
	pid_t pids[2];
	char  *strings = (char*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	scanf("%[^\n]", strings);
	getchar();
	pids[0] = fork();
	if (pids[0] < 0) {
		return 1;
	} else if (pids[0] == 0) {
		int count = 0;
		int isword = 0;
		int i;
		for(i = 0; strings[i]; ++i) {			
			if (strings[i] != ' ' && strings[i+1] != 0) {
			++isword;	
			} else {
				if(isword) {
					++count;
					isword = 0;
				}
			}		
		}
		int *a = (int*)(strings + i + 1);
		*a = count;
		printf("count words %d\n", strings[i+1]);
	} else {
		wait(NULL);
		pids[1] = fork();
		if (pids[1] < 0) {
			return 1;
		} else if (pids[1] == 0) {
			int c = 0;
			int i;
			for(i = 0; strings[i]; ++i) {
				if (strings[i] != ' ') {
					++c;
				}
			}
			int *a = (int*)(strings + i + 1 + 4);
			*a = c;
			printf("lexem count %d\n", strings[i+5]);
		} else {
			wait(NULL);
			printf("%s\n", strings);
		}
	}

	int i = 0;
		
	return 0;
}
