// 6.Գրել ծրագիր, որը կհաշվի ֆայլում եղած թվերի միջին թվաբանականը և կավելացնի ֆայլի վերջից։
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main () {
    int file = open("file.txt", O_RDWR | O_APPEND, 0777);
    if (file == -1) {
        return 1;
    }
    char *delimeter = "\n ";
    char buf[50];
    memset(buf,0,50);

    if(read(file, buf, sizeof(buf)) == -1) {
        printf("Failed Write\n");
        return 1;
    }

    char * token = strtok(buf, delimeter);
    int res = 0;
    
int c = 0;
        while (token != NULL) {
        ++c;
            int number = atoi(token); 
               printf("%s ", token);
            res += number;
            token = strtok(NULL, delimeter); 
        }
    printf("Result is : %d\n", res/c);
    
    memset(buf, 0, sizeof(buf));
    int size = snprintf(buf, sizeof(buf), "%d\n", res/c);
    write(file, buf, size);
    
    close(file);
    return 0;
}