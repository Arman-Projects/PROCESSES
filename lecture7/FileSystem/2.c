// 2.Գրել ծրագիր, որը կստեղծի ֆայլ և օգտագործողի կողմից մուտքագրված թվանշանները կլցնի ֆայլի մեջ։
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file = open("nums1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }
    char buffer[50] = {0};

    char num;
    do {
        scanf("%hhd", &num);
        int len = snprintf(buffer, sizeof(buffer), "%d\n", num);
        write(file,buffer,len);
    } while (num != 0);
    

    close(file);
    printf("FINISHED");

    return 0;
}