// 4.Գրել ծրագիր, որը կկարդա արդեն իսկ ստեղծված ֆայլի առաջին թիվը և կտպի էկրանին։
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    int file = open("file.txt", O_RDWR, 0777);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }
    char buffer[50];
    memset(buffer, 0, sizeof(buffer));
    if(read(file,buffer,50) == -1) {
        printf("Failed Write\n");
        return  1;
    }

    int i;
    for (i = 0; buffer[i] != '\n'; i++){
        /* code */
    }
    buffer[i] = 0;
    
    printf("%s", buffer);

    
    close(file);
    return 0;
}