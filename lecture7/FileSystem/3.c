// 3.Իրականացնել ֆունկցիա, որը կստեղծի ֆայլ և որպես արգումենտ կստանա տեքստ, կավելացնի տեքստը ֆայլում առկա տեքստի վերջից։
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int file = open("nums1.txt", O_RDWR | O_APPEND | O_CREAT , 0644);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }
    char buffer[100];
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0; i < argc; ++i) {
        int len = snprintf(buffer, sizeof(buffer), "%s\n", argv[i]);
        write(file,buffer,len);
    }
    close(file);
    printf("Finish\n");

    return 0;
}