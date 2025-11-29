#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void SP(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
void SV(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
void SS(int arr[], int n) {
    if (n <= 1) return;
    int mid = n / 2;
    int left[mid];
    int right[n - mid];
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = 0; i < n - mid; i++) {
        right[i] = arr[mid + i];
    }
    SS(left, mid);
    SS(right, n - mid);
    int i = 0, j = 0, k = 0;
    while (i < mid && j < n - mid) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < mid) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n - mid) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
double TS(void (*sortFunc)(int[], int), int arr[], int n) {
    int copy[n];
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    clock_t start = clock();
    sortFunc(copy, n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}
int main() {
    srand(time(NULL));
    int sizes[] = {10, 1000, 10000, 100000};
    int numSizes = 4;
    printf("comparison of sorts:\n");
    printf("_________________________\n\n");
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int arr[n];
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 10000;
        }
        printf("Massiv`s size: %d\n", n);
        printf("__________________\n");
        double time1 = TS(SP, arr, n);
        printf("Пузырьком:    %.6f сек\n", time1);
        double time2 = TS(SV, arr, n);
        printf("Вставками:    %.6f сек\n", time2);
        double time3 = TS(SS, arr, n);
        printf("Слиянием:     %.6f сек\n", time3);
        printf("\n");
    }
    return 0;
}