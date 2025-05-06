#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

// Функция создания файла сотрудников
void createFile(const char *filename, int n) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        exit(1);
    }

    Employee emp;
    for (int i = 0; i < n; i++) {
        printf("Введите данные для сотрудника %d\n", i + 1);
        
        // Ввод имени
        printf("ФИО: ");
        getchar(); // Очистка буфера
        fgets(emp.name, MAX_NAME, stdin);
        emp.name[strcspn(emp.name, "\n")] = '\0';

        // Ввод зарплаты
        printf("Среднемесячный заработок: ");
        scanf("%f", &emp.salary);
        getchar(); // Очистка буфера

        // Ввод номера телефона
        printf("Номер телефона: ");
        fgets(emp.phone, MAX_PHONE, stdin);
        emp.phone[strcspn(emp.phone, "\n")] = '\0';

        // Запись структуры в файл
        fwrite(&emp, sizeof(Employee), 1, file);
    }

    fclose(file);
    printf("Данные успешно записаны в файл \"%s\".\n", filename);
}

// Функция поиска сотрудников по зарплате
void searchFileBySalary(const char *filename, float minSalary) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Ошибка открытия файла для чтения!\n");
        exit(1);
    }

    Employee emp;
    int found = 0;

    // Чтение и вывод сотрудников
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.salary >= minSalary) {
            printf("\nНайден сотрудник:\n");
            printf("ФИО: %s\n", emp.name);
            printf("Среднемесячный заработок: %.2f\n", emp.salary);
            printf("Номер телефона: %s\n", emp.phone);
            found = 1;
        }
    }

    if (!found) {
        printf("\nСотрудники с зарплатой >= %.2f не найдены.\n", minSalary);
    }

    fclose(file);
}