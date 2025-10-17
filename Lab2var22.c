#include <stdio.h>


void find_pairs(int n, int current, int* count) {

    if (current > n / 2) {
        return;
    }


    printf("%d = %d + %d\n", n, current, n - current);
    (*count)++;


    find_pairs(n, current + 1, count);
}

int main() {
    int n;

    printf("Введите число: ");

    if (scanf("%d", &n) != 1) {
        printf("введите целое число!\n");
        return 1;
    }
    if (n == 0) {
        printf("число не может быть равно 0!\n");
        return 1;
    }
    if (n < 0) {
        printf("число должно быть положительным!\n");
        return 1;
    }
    if (n < 2) {
        printf("Число %d нельзя разбить на 2 положительных слагаемых!\n", n);
        return 1;
    }
    int count = 0;
    find_pairs(n, 1, &count);

    printf("Всего вариантов: %d\n", count);

    return 0;
}
