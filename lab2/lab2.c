#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next; // указ на некст узел в 1 списке
    struct node *alt;  // указ на узел во 2 списке
};

// создания нью узла
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->alt = NULL;
    return newNode;
}

// добавка узла в конец списка
void append(struct node** head, int data) {
    struct node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// выводим список погулять
void printList(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// движемся по списку
void navigate(struct node* start) {
    struct node* current = start;
    char command;
    printf("Используйте W/S/A/D или 2/4/6/8 для навигации. Нажмите Q для выхода.\n");
    while (1) {
        printf("Текущий узел: %d\n", current->data);
        command = getchar();
        while (getchar() != '\n') {} // прочищаем буфер ввода
        if ((command == 'D' || command == '6') && current->next != NULL) {
            current = current->next;
        } else if ((command == 'S' || command == '2')) {
            printf("Вниз нельзя, конец списка. Вернуться в начало? (Y/N)\n");
            char choice = getchar();
            while (getchar() != '\n') {}
            if (choice == 'Y' || choice == 'y') {
                current = start;
            }
        } else {
            printf("Переместиться туда нельзя, скорее всего конец списка. Вернуться в начало? (Y/n)\n");
	    char choice = getchar();
	    while (getchar()!='\n'){}
	    if (choice == 'Y' || choice == 'y'){
	    	current = start;
	    }
        }
    }
}

int main() {
    struct node* mainList = NULL;
    struct node* secondList = NULL;
    int num, count;
    // заводить в вольер 1 список
    printf("Введите числа для первого списка (завершите ввод 0):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) break;
        append(&mainList, num);
    }
    // докупаем в волер второй список (генерим автоматически)
    printf("Введите количество элементов второго списка:\n");
    scanf("%d", &count);
    for (int i = 1; i <= count; i++) {
        append(&secondList, i * 10);
    }
    // Поводок на первый и второй (по варику нельзя вниз двигаться)
    if (mainList != NULL && secondList != NULL) {
        mainList->alt = secondList;
    }
    // Выводим списки на всеобщее обозрение
    printf("Основной список:\n");
    printList(mainList);
    printf("Второй список:\n");
    printList(secondList);
    // Запуск навигации
    navigate(mainList);
    return 0;
}
