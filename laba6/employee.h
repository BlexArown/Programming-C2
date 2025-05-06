#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME 100
#define MAX_PHONE 15

// Структура данных для сотрудника
typedef struct {
    char name[MAX_NAME];
    float salary;
    char phone[MAX_PHONE];
} Employee;

// Функции
void createFile(const char *filename, int n);
void searchFileBySalary(const char *filename, float minSalary);

#endif

