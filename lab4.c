#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void SP(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int x = 0; x < n-i-1; x++) {
            if (arr[x] > arr[x+1]) {
                int ass = arr[x];
                arr[x] = arr[x+1];
                arr[x+1] = ass;
            }
        }
    }
}
void SS(int arr[], int n) {
    if (n <= 1) return;
    int seredina = n / 2;
    int levo[seredina];
    int pravo[n - seredina];
    for (int i = 0; i < seredina; i++) {
        levo[i] = arr[i];
    }
    for (int i = 0; i < n - seredina; i++) {
        pravo[i] = arr[seredina + i];
    }
    SS(levo, seredina);
    SS(pravo, n - seredina);
    int i = 0, x = 0, k = 0;
    while (i < seredina && x < n - seredina) {
        if (levo[i] <= pravo[x]) {
            arr[k] = levo[i];
            i++;
        } else {
            arr[k] = pravo[x];
            x++;
        }
        k++;
    }
    while (i < seredina) {
        arr[k] = levo[i];
        i++;
        k++;
    }
    while (x < n - seredina) {
        arr[k] = pravo[x];
        x++;
        k++;
    }
}
void SV(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int z = arr[i];
        int x = i-1;
        while (j >= 0 && arr[x] > z) {
            arr[x+1] = arr[x];
            x--;
        }
        arr[x+1] = z;
    }
}
double TS(void (*sortFunc)(int[], int), int arr[], int n) {
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
    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int arr[n];
        for (int x = 0; x < n; x++) {
            arr[x] = rand() % 10000;
        }
        printf("Massiv`s size: %d\n", n);
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
