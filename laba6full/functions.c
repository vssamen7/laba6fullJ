// functions.c
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//--- Общие функции ---
// Функция для проверки корректности ввода целого числа (как было)
int correct_choice() {
    int value;
    char extra;
    while (1) {
        if (scanf("%d%c", &value, &extra) == 2 && extra == '\n' && value > 0) {
            return value;
        } else {
            printf("Некорректный ввод! Введите целое число больше 0.\n");
            while (getchar() != '\n');
        }
    }
}

// Функция для проверки корректности выбора задания
int get_valid_task_number() {
    int value;
    char extra;
    while (1) {
        if (scanf("%d%c", &value, &extra) == 2 && extra == '\n' && value > 0) {
            return value;
        } else {
            printf("Некорректный ввод! Повторите попытку ввода:\n");
            while (getchar() != '\n');
        }
    }
}

char read_single_char() {
    char input, extra;
    while (1) {
        if (scanf(" %c%c", &input, &extra) == 2 && extra == '\n') {
            return input;
        } else {
            printf("Некорректный ввод! Введите только один символ.\n");
            while (getchar() != '\n');
        }
    }
}

char read_first_char() {
    char input, extra;
    while (1) {
        printf("Выберите операцию (a - добавить элемент, p - просмотр, q - выход): ");

        if (scanf(" %c%c", &input, &extra) == 2 && extra == '\n' && isalpha(input)) {
            return input;
        } else {
            printf("Некорректный ввод. Введите только одну букву.\n");
            while (getchar() != '\n');
        }
    }
}

//--- Функции Задания 1 ---
bool initQueue_1(CharQueue *queue, int capacity) {
    if (capacity <= 0) {
        printf("Ошибка: некорректный размер очереди.\n");
        return false;
    }

    queue->data = (char *)malloc(capacity * sizeof(char));
    if (queue->data == NULL) {
        printf("Ошибка: не удалось выделить память для очереди.\n");
        return false;
    }

    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return true;
}

void freeQueue_1(CharQueue *queue) {
    if (queue->data != NULL) {
        free(queue->data);
        queue->data = NULL;
    }
    queue->capacity = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

bool isEmpty_1(const CharQueue *queue) {
    return queue->size == 0;
}

bool isFull_1(const CharQueue *queue) {
    return queue->size == queue->capacity;
}

bool enqueue_1(CharQueue *queue, char value) {
    if (isFull_1(queue)) {
        return false;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
    return true;
}

char dequeue_1(CharQueue *queue) {
    if (isEmpty_1(queue)) {
        printf("Ошибка: очередь пуста.\n");
        return '\0';
    }

    char value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

void printQueue_1(const CharQueue *queue) {
    if (isEmpty_1(queue)) {
        printf("Очередь пуста.\n");
        return;
    }

    printf("[");
    int i = queue->front;
    for (int j = 0; j < queue->size; j++) {
        printf("'%c'", queue->data[i]);
        if (j < queue->size - 1) {
            printf(", ");
        }
        i = (i + 1) % queue->capacity;
    }
    printf("]\n");
}

char getValidChar_1(const char *prompt) {
    char input[100];
    char ch;

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 1) {
            ch = input[0];
            if (!isspace(ch)) {
                return ch;
            } else {
                printf("Ошибка: пробелы не допускаются. Повторите ввод.\n");
            }
        } else {
            printf("Ошибка: нужно ввести ровно один символ. Повторите ввод.\n");
        }
    }
}

//--- Функции Задания 2 ---
Deque* createDeque_2(int maxSize) {
    Deque *deque = (Deque*)malloc(sizeof(Deque));
    deque->data = (char*)malloc(maxSize * sizeof(char));
    deque->front = -1;
    deque->rear = -1;
    deque->size = maxSize;
    deque->count = 0;
    deque->turn = 0;
    return deque;
}

int isEmpty_2(Deque *deque) {
    return deque->count == 0;
}

int isFull_2(Deque *deque) {
    return deque->count == deque->size;
}

void push_2(Deque *deque, char elem) {
    if (isFull_2(deque)) {
        if (deque->turn == 0) {
            printf("Дек переполнен! Удаляем элемент слева: %c\n", deque->data[deque->front]);
            deque->front = (deque->front + 1) % deque->size;
        } else {
            printf("Дек переполнен! Удаляем элемент справа: %c\n", deque->data[deque->rear]);
            deque->rear = (deque->rear - 1 + deque->size) % deque->size;
        }
        deque->count--;
    }

    if (isEmpty_2(deque)) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->turn == 0) {
        deque->rear = (deque->rear + 1) % deque->size;
    } else {
        deque->front = (deque->front - 1 + deque->size) % deque->size;
    }

    deque->data[deque->turn == 0 ? deque->rear : deque->front] = elem;
    deque->count++;
    deque->turn = 1 - deque->turn;
}

void printDeque_2(Deque *deque) {
    if (isEmpty_2(deque)) {
        printf("Дек пуст!\n");
        return;
    }
    printf("Содержимое дека: ");
    int i = deque->front;
    for (int j = 0; j < deque->count; j++) {
        printf("%c ", deque->data[i]);
        i = (i + 1) % deque->size;
    }
    printf("\n");
}

void freeDeque_2(Deque *deque) {
    free(deque->data);
    free(deque);
}

//--- Функции Задания 3 ---
Queue* createQueue_3(int chunk_size) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->chunk_size = chunk_size;
    return queue;
}

void enqueue_3(Queue *queue, const char *chunk) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->chunk = strdup(chunk);
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void splitStringIntoQueue_3(Queue *queue, const char *input) {
    int length = strlen(input);
    char chunk[queue->chunk_size + 1];

    for (int i = 0; i < length; i += queue->chunk_size) {
        strncpy(chunk, input + i, queue->chunk_size);
        chunk[queue->chunk_size] = '\0';
        enqueue_3(queue, chunk);
    }
}

void displayQueue_3(Queue *queue) {
    if (queue->front == NULL) {
        printf("Очередь пуста!\n");
        return;
    }

    printf("Содержимое очереди:\n");
    Node *temp = queue->front;
    while (temp != NULL) {
        printf("%s\n", temp->chunk);
        temp = temp->next;
    }
}

void freeQueue_3(Queue *queue) {
    Node *temp;
    while (queue->front != NULL) {
        temp = queue->front;
        queue->front = queue->front->next;
        free(temp->chunk);
        free(temp);
    }
    free(queue);
}
