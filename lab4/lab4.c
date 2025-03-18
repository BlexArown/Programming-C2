#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 500

// Функция для смены первого и последнего слова в строке
void swap_first_last_word(char *line) {
    char temp[MAX_LINE];
    char *words[MAX_LINE / 2]; // Массив указателей на слова
    int count = 0;

    // Разбиваем строку на слова
    char *token = strtok(line, " \n");
    while (token) {
        words[count++] = token;
        token = strtok(NULL, " \n");
    }

    if (count < 2) return; // Если меньше 2 слов, ничего менять не нужно

    // Меняем первое и последнее слово
    char *first = words[0];
    char *last = words[count - 1];

    // Собираем строку обратно
    int offset = snprintf(temp, sizeof(temp), "%s", last);
    for (int i = 1; i < count - 1; i++) {
        offset += snprintf(temp + offset, sizeof(temp) - offset, " %s", words[i]);
    }
    snprintf(temp + offset, sizeof(temp) - offset, " %s", first);

    strcpy(line, temp); // Перезаписываем строку
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Ошибка открытия файла (чтение)");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        perror("Ошибка открытия файла (запись)");
        fclose(inputFile);
        return 1;
    }

    char line[MAX_LINE], longest[MAX_LINE];
    int maxLen = 0;
    
    // Находим самую длинную строку
    while (fgets(line, sizeof(line), inputFile)) {
        int len = strlen(line);
        if (len > maxLen) {
            maxLen = len;
            strcpy(longest, line);
        }
    }
    
    // Обработка самой длинной строки
    swap_first_last_word(longest);
    
    // Перезаписываем файл
    rewind(inputFile);
    while (fgets(line, sizeof(line), inputFile)) {
        if (strlen(line) == maxLen) {
            fputs(longest, outputFile);
        } else {
            fputs(line, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}