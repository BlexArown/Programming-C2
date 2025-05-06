#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_PHONE 15

// Запись сотрудников
typedef struct {
    char name[MAX_NAME];
    float salary;
    char phone[MAX_PHONE];
} Employee;

void createFile(const char *filename, int n) {
    FILE *file = fopen(filename, "wb");

    Employee emp;
    char buffer[50];
    for (int i = 0; i < n; i++) {
        printf("Введите данные для сотрудника %d\n", i + 1);
        printf("ФИО: ");
        fgets(emp.name, MAX_NAME, stdin);
        emp.name[strcspn(emp.name, "\n")] = '\0';
        printf("Среднемесячный заработок: ");
        fgets(buffer, sizeof(buffer), stdin);
        emp.salary = strtof(buffer, NULL);
	buffer[strcspn(buffer, "\n")] = '\0';
        printf("Номер телефона: ");
        fgets(emp.phone, MAX_PHONE, stdin);
        emp.phone[strcspn(emp.phone, "\n")] = '\0';
        fwrite(&emp, sizeof(Employee), 1, file);
    }

    fclose(file);
}

void searchFileBySalary(const char *filename) {
    char buffer[50];
    float searchSalary;

    printf("Введите среднемесячный заработок для поиска: ");
    fgets(buffer, sizeof(buffer), stdin);
    searchSalary = strtof(buffer, NULL);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return;
    }

    Employee emp;
    int found = 0;

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.salary == searchSalary) {
            printf("Сотрудник найден:\n");
            printf("ФИО: %s\n", emp.name);
            printf("Среднемесячный заработок: %.2f\n", emp.salary);
            printf("Номер телефона: %s\n", emp.phone);
            found = 1;
        }
    }

    if (found == 0) {
        printf("Сотрудник с заработком %.2f не найден.\n", searchSalary);
    }

    fclose(file);
}

int main() {
    const char *filename = "Work.dat";
    int choice, n;
    char buffer[10];

    do {
        printf("\nМеню:\n");
        printf("1. Создать файл\n");
        printf("2. Поиск в файле по заработку\n");
        printf("3. Выход\n");
        printf("Ваш выбор: ");
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                printf("Введите количество сотрудников: ");
                fgets(buffer, sizeof(buffer), stdin);
                n = atoi(buffer);
                createFile("Work.dat", n);
                break;
            case 2:
                searchFileBySalary("Work.dat");
                break;
            case 3:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Некорректный выбор! Попробуйте снова.\n");
        }
    } while (choice != 3);

    return 0;
}

