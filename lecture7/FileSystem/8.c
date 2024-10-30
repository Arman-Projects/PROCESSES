#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
void caesar_encode(char *plaintext, int shift, char *ciphertext) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            char base = isupper(*plaintext) ? 'A' : 'a';
            *ciphertext++ = (char)(((*plaintext - base + shift) % 26) + base);
        } else {
            *ciphertext++ = *plaintext; 
        }
        plaintext++;
    }
    *ciphertext = '\0'; 
}

void caesar_decode(char *ciphertext, int shift, char *plaintext) {
    caesar_encode(ciphertext, 26 - (shift % 26), plaintext); 
}

int main() {

    int file = open("./hello.txt", O_RDWR, 0777);
    int file1 = open("./hello1.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    int file2 = open("./hello2.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    if (file == -1 && file1 == -1) {
        return 1;
    }

    char buff[100];
    memset(buff, 0, 100);
    read(file,buff,100);
    printf("%s\n", buff);
    caesar_encode(buff, 5, buff);
    write(file1,buff,strlen(buff));
    memset(buff, 0, sizeof(buff));
    lseek(file1, 0, SEEK_SET);
    read(file1, buff, sizeof(buff));
    caesar_decode(buff, 5, buff);
    write(file2, buff, strlen(buff));



    close(file);
    close(file1);
    close(file2);
    return 0;
}