// 7.Գրել ծրագիր, որը զանգված ի մեջ կպահի ֆայլի պարունակությունը և արդյունքը կտպի էկրանին։
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int file = open("file.txt", O_RDWR | O_APPEND, 0777);
    if (file == -1) {
        return 1;
    }
    char buff[100];
    read(file, buff, sizeof(buff));
    printf("%s", buff);
}