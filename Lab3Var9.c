#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** read_matrix_from_file(const char* filename, int* n, int* m) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("opening failed %s\n", filename);
        return NULL;
    }
    
   
    if (fscanf(file, "%d %d", n, m) != 2) {
        printf("error\n");
        fclose(file);
        return NULL;
    }
    
  
    if (*n <= 0 || *m <= 0) {
        printf("error0");
        fclose(file);
        return NULL;
    }
    

    int matrix = (int)malloc(*n * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc(*m * sizeof(int));
    }
    

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("error1");
                fclose(file);
               
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return NULL;
            }
        }
    }
    
    fclose(file);
    return matrix;
}

int find_row_with_min_element(int** matrix, int n, int m) {
    int min_row = 0;
    int min_value = matrix[0][0];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
                min_row = i;
            }
        }
    }
    
    return min_row;
}

void swap_rows(int** matrix, int row1, int row2, int m) {
    for (int j = 0; j < m; j++) {
        int temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}


int sum_rows(int** matrix, int row1, int row2, int m) {
    int sum = 0;
    
 
    for (int j = 0; j < m; j++) {
        sum += matrix[row1][j];
    }
    
    
    for (int j = 0; j < m; j++) {
        sum += matrix[row2][j];
    }
    
    return sum;
}


void print_matrix(int** matrix, int n, int m) {
    printf("Матрица %dx%d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char* argv[]) {
   
    if (argc != 2) {
        printf("0");
        return 1;
    }
    
    const char* filename = argv[1];
    int n, m;
    
   
    int** matrix = read_matrix_from_file(filename, &n, &m);
    if (matrix == NULL) {
        return 1;
    }
    
    printf("Исходная матрица:\n");
    print_matrix(matrix, n, m);
   
    int min_row = find_row_with_min_element(matrix, n, m);
    printf("\nСтрока с минимальным элементом: %d\n", min_row + 1);
    
  
    if (n >= 4) {
        if (min_row != 3) { 
            swap_rows(matrix, min_row, 3, m);
            printf("string %d already changed\n", min_row + 1);
        } else {
            printf("already 4 string\n");
        }
    } else {
        printf("error\n");
        free_matrix(matrix, n);
        return 1;
    }
    
    printf("\nМатрица после обмена строк:\n");
    print_matrix(matrix, n, m);
   
    int sum = sum_rows(matrix, 1, 3, m); 
    printf("\nСумма элементов 2 и 4 строк: %d\n", sum);
    free_matrix(matrix, n);
    
    return 0;
}
