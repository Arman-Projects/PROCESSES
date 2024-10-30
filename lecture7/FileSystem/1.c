// 1.Գրել ծրագիր, որը կստեղծի ֆայլ և ֆայլի մեջ կլցնի 1-ից 15-ը միջակայքում եղած բոլոր պարզ թվերը։
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int file = open("nums.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    char buffer[50];
    memset(buffer,0,sizeof(buffer));
    for (int number = 1; number <= 15; number++) {
        if (is_prime(number)) {
            int len = snprintf(buffer, sizeof(buffer), "the %d\n", number);
            printf("%d ", len);
            write(file, buffer, len);
        }
    }

    close(file);
    printf("Finish\n");
    return 0;
}

