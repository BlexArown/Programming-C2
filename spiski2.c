#include <stdio.h>
#include <stdlib.h>

// Структура узла
struct node
{
    int data;
    struct node *next;
    struct node *prev; // Добавлен указатель на предыдущий узел
};
typedef struct node node_t;

// Функция для создания нового узла
node_t *newNode(int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    node->prev = NULL; // Инициализация нового указателя
    return node;
}

// Функция для вывода списка на экран
void printList(node_t *head)
{
    node_t *cur = head;
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// Функция для добавления узла в конец списка
void addLast(node_t **head, int data)
{
    node_t *new = newNode(data);
    if (*head == NULL)
    {
        *head = new;
        return;
    }

    node_t *cur = *head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new;
    new->prev = cur; // Устанавливаем связь с предыдущим узлом
}

// Функция для создания второго списка и связывания с первым
void createSecondList(node_t **head1, node_t **head2, int n)
{
    for (int i = 1; i <= n; i++)
    {
        addLast(head2, i * 10); // Пример данных для второго списка
    }

    // Связываем узлы второго списка с узлами первого списка
    node_t *cur1 = *head1;
    node_t *cur2 = *head2;
    while (cur1 != NULL && cur2 != NULL)
    {
        node_t *temp1 = cur1->next; // Сохраняем следующий узел первого списка
        node_t *temp2 = cur2->next; // Сохраняем следующий узел второго списка

        cur1->next = cur2; // Связываем текущий узел первого списка с текущим узлом второго списка
        cur2->prev = cur1; // Устанавливаем связь с предыдущим узлом

        if (temp1 != NULL)
        {
            cur2->next = temp1; // Связываем текущий узел второго списка с следующим узлом первого списка
            temp1->prev = cur2; // Устанавливаем связь с предыдущим узлом
        }

        cur1 = temp1;
        cur2 = temp2;
    }
}

// Функция для навигации по списку
void navigateList(node_t *head)
{
    node_t *current = head;
    char input;

    while (1)
    {
        printf("\nТекущее значение: %d\n", current->data);
        printf("Введите команду (W/A/S/D или 2/4/6/8): ");
        scanf(" %c", &input);

        switch (input)
        {
        case 'D': // Вправо
        case '6':
            if (current->next != NULL)
            {
                current = current->next;
            }
            else
            {
                printf("Достигнут конец списка. Вернуться в начало? (Y/N): ");
                scanf(" %c", &input);
                if (input == 'Y' || input == 'y')
                {
                    current = head;
                }
            }
            break;

        case 'A': // Влево
        case '4':
            if (current->prev != NULL)
            {
                current = current->prev;
            }
            else
            {
                printf("Достигнуто начало списка. Вернуться в конец? (Y/N): ");
                scanf(" %c", &input);
                if (input == 'Y' || input == 'y')
                {
                    while (current->next != NULL)
                    {
                        current = current->next;
                    }
                }
            }
            break;

        case 'W': // Вверх (переход к началу списка)
        case '8':
            current = head;
            break;

        case 'S': // Вниз (переход к концу списка)
        case '2':
            while (current->next != NULL)
            {
                current = current->next;
            }
            break;

        default:
            printf("Неверная команда. Попробуйте снова.\n");
            break;
        }
    }
}

int main()
{
    node_t *head1 = NULL; // Первый список
    node_t *head2 = NULL; // Второй список
    int n;

    // Ввод первого списка
    while (1)
    {
        printf("Введите число (0 для завершения): ");
        scanf("%d", &n);
        if (n == 0)
        {
            break;
        }
        addLast(&head1, n);
    }

    printf("Первый список: ");
    printList(head1);

    // Создание второго списка и связывание с первым
    printf("Введите количество элементов для второго списка: ");
    scanf("%d", &n);
    createSecondList(&head1, &head2, n);

    printf("Объединенный список: ");
    printList(head1);

    // Навигация по списку
    printf("\nНавигация по списку:\n");
    navigateList(head1);

    return 0;
}
