// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h" // Подключаем общий заголовочный файл

int main() {
    int choice;

    while (1) {
        printf("\nВыберите задание:\n");
        printf("1. Очередь для символов\n");
        printf("2. Дек для символов\n");
        printf("3. Очередь для строк (чанки)\n");
        printf("Ваш выбор: ");

        choice = get_valid_task_number(); // Используем функцию для проверки номера задания

        switch (choice) {
            case 1:
                //--- Задание 1: Очередь для символов ---
                {
                    int queueCapacity;
                    CharQueue myQueue;

                    printf("Введите максимальный размер очереди: ");
                    queueCapacity = correct_choice(); // Используем correct_choice для ввода

                    if (!initQueue_1(&myQueue, queueCapacity)) {
                        printf("Ошибка: не удалось инициализировать очередь.\n");
                        break;
                    }

                    char inputChar;
                    int elementCount = 0;

                    printf("Начинаем ввод символов в очередь.\n");

                    while (1) {
                        inputChar = getValidChar_1("Введите символ (или '0' для выхода): ");

                        if (inputChar == '0') {
                            printf("Завершение ввода.\n");
                            break;
                        }

                        if (enqueue_1(&myQueue, inputChar)) {
                            elementCount++;
                            printf("Символ '%c' добавлен в очередь.\n", inputChar);

                            if (elementCount >= 3) {
                                printf("Крайний левый символ: '%c'\n", myQueue.data[myQueue.front]);
                            }
                        } else {
                            printf("Ошибка: очередь полна. Символ '%c' не добавлен.\n", inputChar);
                        }

                        printf("Текущее содержимое очереди: ");
                        printQueue_1(&myQueue);
                    }

                    printf("Содержимое очереди перед завершением: ");
                    printQueue_1(&myQueue);

                    freeQueue_1(&myQueue);
                }
                break;

            case 2:
                //--- Задание 2: Дек для символов ---
                {
                    int maxSize;
                    printf("Введите максимальный размер дека: "); // Запрос размера дека
                    maxSize = correct_choice();

                    Deque *deque = createDeque_2(maxSize);
                    char choice, elem;

                    printf("Введите операции для дека (a - добавить, p - просмотр, q - выход):\n"); // Запрос операций
                    while (1) {
                        choice = read_first_char();

                        if (choice == 'q') break;
                        else if (choice == 'a') {
                            printf("Введите символ для добавления: ");  // Запрос символа для добавления
                            elem = read_single_char();
                            push_2(deque, elem);
                        } else if (choice == 'p') {
                            printDeque_2(deque);
                        }
                    }

                    freeDeque_2(deque);
                }
                break;

            case 3:
                //--- Задание 3: Очередь для строк (чанки) ---
                {
                    int chunk_size;
                    printf("Введите размер чанка: "); // Запрос размера чанка
                    chunk_size = correct_choice();

                    Queue *queue = createQueue_3(chunk_size);
                    char input[256];

                    printf("Введите строку для разбиения на чанки:\n"); // Запрос строки
                    fgets(input, sizeof(input), stdin);
                    size_t len = strlen(input);
                    if (input[len - 1] == '\n') {
                        input[len - 1] = '\0';
                    }

                    splitStringIntoQueue_3(queue, input);
                    displayQueue_3(queue);
                    freeQueue_3(queue);
                }
                break;

            case 0:
                printf("Выход из программы.\n");
                return 0;

            default:
                printf("Некорректный выбор. Пожалуйста, повторите.\n");
        }
    }

    return 0;
}
