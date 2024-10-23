//DEMO VERSION
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>

void print_matrix(int *mat, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", mat[i*size + j]);
        }
        printf("\n");
    }
}

void multiply_matrices(int *mat1, int *mat2, int *result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i*size + j] = 0;
            for (int k = 0; k < size; k++) {
                result[i*size + j] += mat1[i*size + k] * mat2[k*size + j];
            }
        }
    }
}
//scanf matrix with size
void read_matrix(int *mat, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &mat[i*size + j]);
        }
    }
}
int main() {
    int *mat = (int*)mmap(NULL,4096,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    pid_t pids[2];
    pids[0] = fork();
    if (pids[0] < 0) {
        exit(1);
    } else if (pids[0] == 0) {
        int size;
        printf("Enter size of the matrix: ");
        scanf("%d", &size);

        read_matrix(mat, size);
        int *result = (int*)malloc(size*size*sizeof(int));
        multiply_matrices(mat, mat, result, size);
        print_matrix(result, size);
        free(result);
        
    } else {
        wait(NULL);
    }

    return 0;
}
