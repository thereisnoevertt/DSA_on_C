//
// Created by Никита on 18.12.2025.
// Реализация стэка

/* Поддерживаются операции
 *
 */

// Все ошибки возвращают интовую единицу,
// но в рамках учебного примера была выбрана данная реализация.

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct stack_node {
    int data;
    struct stack_node* next;
} stack_node;

enum {
    STACK_ERR = 1,
    STACK_OK = 0,
};

//инициализация узла стэка
stack_node* node_init(int data) {
    stack_node* new_node = malloc(sizeof(stack_node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

//уничтожение стэка
int stack_destroy (stack_node** top) {
    if (!top) {
        return STACK_ERR;
    }

    while (*top != NULL) {
        stack_node *next = (*top)->next;
        free(*top);
        *top = next;
    }
    return STACK_OK;
}

//проверка на пустоту стэка
int stack_is_empty(stack_node* top) {
    return (top == NULL);
}

//добавление в стэк
void stack_push(stack_node** top, int data) {
    stack_node* new_node = node_init(data);
    new_node->next = *top;
    *top = new_node; //чтобы новый элемент стал верхним
}

//удаление верхушки стэка
int stack_pop(stack_node **top) {
    if (!top || !*top) {  // стек пуст или указатель NULL
        return STACK_ERR;
    }

    stack_node *temp = *top;
    int popped_data = temp->data;

    *top = temp->next;  // ЗДЕСЬ изменение оригинального указателя
    free(temp);

    return popped_data;  // возвращаем значение
}

//взятие верхушки стэка
int stack_peek(stack_node *top, int *out) {
    if (!top || !out) {
        return STACK_ERR;
    }
    *out = top->data;
    return STACK_OK;
}

//длина стэка
int stack_size(stack_node* top) {
    int count = 0;

    while (top != NULL) {
        count++;
        top = top->next;
    }

    return count;
}

//вывод стэка
void stack_print(stack_node* top) {
    while (top != NULL) {
        top = top->next;
        printf("%d", top->data);
    }
}

int main() {
    stack_node *stack = NULL;

    // 1. Тест пустого стека
    printf("1. Empty stack:\n");
    printf("Size: %d (expected 0)\n", stack_size(stack));
    printf("Empty: %s\n\n", stack_is_empty(stack) ? "yes" : "no");

    // 2. Push нескольких элементов
    printf("2. Add 10, 20, 30:\n");
    stack_push(&stack, 10);
    stack_push(&stack, 20);
    stack_push(&stack, 30);
    printf("Size: %d (expected 3)\n", stack_size(stack));

    // Peek (просмотр вершины)
    int peek_val;
    if (stack_peek(stack, &peek_val) == STACK_OK) {
        printf("Top: %d (expected 30)\n", peek_val);
    }

    // 3. Pop элементов
    printf("\n3. Pop elements:\n");
    printf("Pop1: %d (expected 30)\n", stack_pop(&stack));
    printf("Pop2: %d (expected 20)\n", stack_pop(&stack));
    printf("Pop3: %d (expected 10)\n", stack_pop(&stack));
    printf("Size: %d (expected 1)\n", stack_size(stack));

    // 4. Ошибка pop на пустом стеке
    printf("\n4. Pop empty stack: %d (expected STACK_ERR=1)\n", stack_pop(&stack));

    // 5. Полное уничтожение
    printf("\n5. Destroy stack\n");
    stack_destroy(&stack);
    printf("Size after destroy: %d (expected 0)\n", stack_size(stack));

    return 0;
}
