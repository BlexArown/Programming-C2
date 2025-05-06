#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define THREADS 4
#define MESSAGES 5
#define ARR_SIZE 10

typedef struct {
    int thread_num;
    const char *messages[MESSAGES];
    pthread_mutex_t *mutex;
} thread_data_t;

typedef struct {
    int value;
    pthread_mutex_t *mutex;
} sleepsort_arg_t;

typedef struct {
    int thread_id;
    int num_threads;
    int N;
    int **A;
    int **B;
    int **C;
    int rows_per_thread;
    int extra_rows;
} matrix_thread_data_t;

pthread_mutex_t main_mutex = PTHREAD_MUTEX_INITIALIZER;
int current_thread = 0;

void cleanup_handler(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    printf("Поток %d: Выполняется очистка перед завершением\n", data->thread_num);
}

void* thread_func(void* arg) {
    thread_data_t *data = (thread_data_t *)arg;

    pthread_cleanup_push(cleanup_handler, data);

    for (int i = 0; i < MESSAGES; i++) {
        pthread_mutex_lock(data->mutex);
        while (current_thread != data->thread_num - 1) {
            pthread_mutex_unlock(data->mutex);
            usleep(100);
            pthread_mutex_lock(data->mutex);
        }
        printf("Поток %d: %s\n", data->thread_num, data->messages[i]);
        current_thread = (current_thread + 1) % THREADS;
        pthread_mutex_unlock(data->mutex);
        sleep(1);
    }

    pthread_cleanup_pop(0);
    printf("Поток %d: завершение работы\n", data->thread_num);
    return NULL;
}


void* sleepsort_thread(void* arg) {
    sleepsort_arg_t* sleept = (sleepsort_arg_t*)arg;
    sleep(sleept->value);
    pthread_mutex_lock(sleept->mutex);
    printf("%d ", sleept->value);
    fflush(stdout);
    pthread_mutex_unlock(sleept->mutex);
    free(sleept);
    return NULL;
}

void run_sleepsort(int arr[], int n) {
    if (n <= 0) {
        printf("Некорректный размер массива!\n");
        return;
    }

    pthread_t sleep_threads[ARR_SIZE];

    printf("\n\n\n  --- Запуск Sleepsort ---\n\n");

    printf("Исходный массив:        ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Отсортированный массив: ");
    fflush(stdout); // Сброс после заголовка

    for (int i = 0; i < n; i++) {
        sleepsort_arg_t* arg = malloc(sizeof(sleepsort_arg_t));
        if (!arg) {
            perror("Ошибка выделения памяти");
            exit(EXIT_FAILURE);
        }
        arg->value = arr[i];
        arg->mutex = &main_mutex;

        int res = pthread_create(&sleep_threads[i], NULL, sleepsort_thread, arg);
        if (res != 0) {
            perror("Ошибка создания потока");
            free(arg); // важно!
        }
    }

    for (int i = 0; i < n; i++) {
        pthread_join(sleep_threads[i], NULL);
    }

    printf("\n\n--- Sleepsort завершен ---\n\n\n\n");
}

int main(int argc, char* argv[]) {

    srand(time(NULL));
    pthread_t threads[THREADS];
    thread_data_t thread_data[THREADS];

    const char *messages[THREADS][MESSAGES] = {
        {"Сообщение 1 потока 1", "Сообщение 2 потока 1",
         "Сообщение 3 потока 1", "Сообщение 4 потока 1",
         "Сообщение 5 потока 1"},

        {"Сообщение 1 потока 2", "Сообщение 2 потока 2",
         "Сообщение 3 потока 2", "Сообщение 4 потока 2",
         "Сообщение 5 потока 2"},

        {"Сообщение 1 потока 3", "Сообщение 2 потока 3",
         "Сообщение 3 потока 3", "Сообщение 4 потока 3",
         "Сообщение 5 потока 3"},

        {"Сообщение 1 потока 4", "Сообщение 2 потока 4",
         "Сообщение 3 потока 4", "Сообщение 4 потока 4",
         "Сообщение 5 потока 4"}
    };

    printf("--- Запуск потоков с Сообщениями ---\n  ");
    for (int i = 0; i < THREADS; i++) {
        thread_data[i].thread_num = i + 1;
        memcpy(thread_data[i].messages, messages[i], sizeof(messages[i]));
        thread_data[i].mutex = &main_mutex;
        pthread_create(&threads[i], NULL, thread_func, &thread_data[i]);
    }

    printf("\n\n  Ожидание 2 секунды...\n\n");
    sleep(2);

    printf("Отменяем все потоки с сообщениями...\n");
    for (int i = 0; i < THREADS; i++) {
        pthread_cancel(threads[i]);
    }

    printf("Ожидаем завершения потоков с сообщениями...\n  \n");
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- Все потоки с сообщениями завершили работу ---");

    int sleeparr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        sleeparr[i] = rand() % 10;
    }
    run_sleepsort(sleeparr, ARR_SIZE);

}
