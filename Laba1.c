#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100

struct Student {
    char name[64];
    int math;
    int phy;
    int info;
    int total;
};

struct Student addStudent(const char *name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, 64);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.info = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Name: %s, Math: %d, Physics: %d, Informatics: %d, Total: %d\n",
           student.name, student.math, student.phy, student.info, student.total);
}

void selectionSort(struct Student arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j].total > arr[maxIndex].total) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            struct Student temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }
}

int getMax(struct Student arr[], int size) {
    int max = arr[0].total;
    for (int i = 1; i < size; i++) {
        if (arr[i].total > max) {
            max = arr[i].total;
        }
    }
    return max;
}

void radixSort(struct Student arr[], int size) {
    int max = getMax(arr, size);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[size];
        int count[10] = {0};

        for (int i = 0; i < size; i++) {
            count[(arr[i].total / exp) % 10]++;

        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for(int i = size - 1; i >= 0; i--) {
            output[count[(arr[i].total / exp) % 10] - 1] = arr[i].total;
            count[(arr[i].total / exp) % 10]--;
        }

        for(int i = 0; i < size; i++) {
            arr[i].total = output[i];
        }
    }
}

int main() {
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, 64, "Student_%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    printf("До сортировки:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    clock_t start, end;
    double time_used;

    start = clock();
    selectionSort(students, N);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время сортировки Selection Sort: %f секунд\n", time_used);

    printf("\nПосле сортировки Selection Sort:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    for (int i = 0; i < N; i++) {
        students[i] = addStudent(students[i].name, rand() % 101, rand() % 101, rand() % 101);
    }

    start = clock();
    radixSort(students, N);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Время сортировки Radix Sort: %f секунд\n", time_used);

    printf("\nПосле сортировки Radix Sort:\n");
    for (int i = 0; i < N; i++) {
        printStudentInfo(students[i]);
    }

    system("cat /proc/cpuinfo | grep 'model name' | head -1");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | head -1");

    return 0;
}