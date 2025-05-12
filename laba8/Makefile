# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
CHECK_LIBS = -lcheck -lsubunit -lm

# Исходники и объектные файлы
SRC = quicksort.c
TEST = test_quicksort.c
OBJS = quicksort.o test_quicksort.o
TARGET = test_quicksort

# Цель по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CHECK_LIBS)

# Компиляция отдельных .o файлов
quicksort.o: quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c quicksort.c -o quicksort.o

test_quicksort.o: test_quicksort.c quicksort.h
	$(CC) $(CFLAGS) -c test_quicksort.c -o test_quicksort.o

# Запуск тестов
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f *.o $(TARGET)
