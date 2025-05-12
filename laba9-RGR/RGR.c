#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// no recursiya
unsigned long long iterative(int n) {
    unsigned long long result = 0;
    for (int i = 1; i <= n; ++i) {
        result += i;
    }
    return result;
}

// recursiya
unsigned long long recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return n + recursive(n - 1);
}

// запись файла
void writetofile(int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            fprintf(file, "* ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Треугольник записан в %s\n", filename);
}

int main(int argc, char *argv[]) {
    // аргументы (./RGR n)
    if (argc != 2) {
        fprintf(stderr, "Введите: %s <n>\n", argv[0]);
        return 1;
    }

    // n в число
    char *endptr;
    long n = strtol(argv[1], &endptr, 10);

    // выборы
    printf("Выберите каким методом вы хотите посчитать треугольное число:\n");
    printf("1. Итеративный метод\n");
    printf("2. Рекурсивный метод\n");
    printf("3. Рекурсивный метод с построением треугольника в отдельном файле\n");
    printf("Введите вариант (1, 2, или 3): ");

    int choice;
    scanf("%d", &choice);
    unsigned long long result;
    const char *filename = "RGRtreug.txt";

    if (choice == 1) {
        result = iterative((int)n);
    } else if (choice == 2) {
        result = recursive((int)n);
    } else {
        result = recursive((int)n);
        writetofile((int)n, filename);
    }

    printf("%ld-ое треугольное число это: %llu\n", n, result);

    return 0;
}

