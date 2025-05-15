// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

//--- Задание 1 ---
// Структура для представления очереди (Задание 1)
typedef struct {
    char *data;
    int capacity;
    int front;
    int rear;
    int size;
} CharQueue;

//--- Задание 2 ---
// Структура дека (Задание 2)
typedef struct {
    char *data;
    int front, rear, size, count, turn;
} Deque;

//--- Задание 3 ---
// Структура узла для очереди (Задание 3)
typedef struct Node {
    char *chunk;
    struct Node *next;
} Node;

// Структура очереди (Задание 3)
typedef struct {
    Node *front, *rear;
    int chunk_size;
} Queue;

//--- Общие функции ---
int correct_choice(); // Функция для проверки корректности ввода целого числа
int get_valid_task_number(); // Функция для проверки корректности выбора задания
char read_single_char();
char read_first_char();

//--- Функции Задания 1 ---
bool initQueue_1(CharQueue *queue, int capacity);
void freeQueue_1(CharQueue *queue);
bool isEmpty_1(const CharQueue *queue);
bool isFull_1(const CharQueue *queue);
bool enqueue_1(CharQueue *queue, char value);
char dequeue_1(CharQueue *queue);
void printQueue_1(const CharQueue *queue);
char getValidChar_1(const char *prompt);

//--- Функции Задания 2 ---
Deque* createDeque_2(int maxSize);
int isEmpty_2(Deque *deque);
int isFull_2(Deque *deque);
void push_2(Deque *deque, char elem);
void printDeque_2(Deque *deque);
void freeDeque_2(Deque *deque);

//--- Функции Задания 3 ---
Queue* createQueue_3(int chunk_size);
void enqueue_3(Queue *queue, const char *chunk);
void splitStringIntoQueue_3(Queue *queue, const char *input);
void displayQueue_3(Queue *queue);
void freeQueue_3(Queue *queue);

#endif
