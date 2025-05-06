#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

int main() {
    const char *filename = "Work.dat";
    int choice, n;
    float minSalary; // Объявляем переменную заранее

    do {
        printf("\nМеню:\n");
        printf("1. Создать файл сотрудников\n");
        printf("2. Поиск сотрудников по зарплате\n");
        printf("3. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Создание файла
                printf("Введите количество сотрудников: ");
                scanf("%d", &n);
                createFile(filename, n);
                break;

            case 2: // Поиск по зарплате
                printf("Введите минимальную зарплату для поиска: ");
                scanf("%f", &minSalary);
                searchFileBySalary(filename, minSalary);
                break;

            case 3: // Выход
                printf("Выход из программы.\n");
                break;

            default: // Неверный ввод
                printf("Некорректный выбор! Попробуйте снова.\n");
        }
    } while (choice != 3);

    return 0;
}