//
// Created by Никита on 18.12.2025.
// Реализация очереди (FIFO) на односвязном списке
//
// Поддерживаются операции:
// dequeue (pop), enqueue (push), peek,
// init, destroy,
// size, print, is_empty
//

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct queue_node {
    int data;
    struct queue_node* next;
} queue_node;

typedef struct queue {
    queue_node* front;  // откуда извлекаем
    queue_node* rear;   // куда добавляем
} queue;

enum {
    QUEUE_ERR = 1,
    QUEUE_OK  = 0,
};

static queue_node* node_init(int data) {
    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// инициализация очереди
int queue_init(queue* q) {
    if (!q) return QUEUE_ERR;
    q->front = NULL;
    q->rear  = NULL;
    return QUEUE_OK;
}

// уничтожение очереди
int queue_destroy(queue* q) {
    if (!q) return QUEUE_ERR;

    queue_node* cur = q->front;
    while (cur) {
        queue_node* next = cur->next;
        free(cur);
        cur = next;
    }
    q->front = q->rear = NULL;
    return QUEUE_OK;
}

// проверка на пустоту
int queue_is_empty(const queue* q) {
    return (!q || q->front == NULL);
}

// добавление в конец очереди
int queue_enqueue(queue* q, int data) {
    if (!q) return QUEUE_ERR;

    queue_node* n = node_init(data);

    if (q->rear == NULL) {          // очередь пустая
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
    return QUEUE_OK;
}

// удаление из начала очереди
int queue_dequeue(queue* q, int* out) {
    if (!q || !out || q->front == NULL) return QUEUE_ERR;

    queue_node* temp = q->front;
    *out = temp->data;

    q->front = temp->next;
    if (q->front == NULL) {         // стали пустыми -> rear тоже NULL
        q->rear = NULL;
    }

    free(temp);
    return QUEUE_OK;
}

// чтение "головы" без удаления
int queue_peek(const queue* q, int* out) {
    if (!q || !out || q->front == NULL) return QUEUE_ERR;
    *out = q->front->data;
    return QUEUE_OK;
}

// размер очереди
int queue_size(const queue* q) {
    if (!q) return 0;
    int count = 0;
    for (queue_node* cur = q->front; cur != NULL; cur = cur->next) {
        count++;
    }
    return count;
}

// печать очереди (с головы к хвосту)
void queue_print(const queue* q) {
    if (!q) return;
    for (queue_node* cur = q->front; cur != NULL; cur = cur->next) {
        printf("%d ", cur->data);
    }
    printf("\n");
}

int main(void) {
    queue q;
    queue_init(&q);

    // 1. Пустая очередь
    printf("1. Empty queue:\n");
    printf("Size: %d (expected 0)\n", queue_size(&q));
    printf("Empty: %s\n\n", queue_is_empty(&q) ? "yes" : "no");

    // 2. Enqueue нескольких элементов
    printf("2. Add 10, 20, 30:\n");
    queue_enqueue(&q, 10);
    queue_enqueue(&q, 20);
    queue_enqueue(&q, 30);
    printf("Size: %d (expected 3)\n", queue_size(&q));
    printf("Queue: ");
    queue_print(&q);

    // Peek (просмотр головы)
    int peek_val;
    if (queue_peek(&q, &peek_val) == QUEUE_OK) {
        printf("Front: %d (expected 10)\n", peek_val);
    }

    // 3. Dequeue элементов
    printf("\n3. Dequeue elements:\n");
    int x;
    queue_dequeue(&q, &x); printf("Deq1: %d (expected 10)\n", x);
    queue_dequeue(&q, &x); printf("Deq2: %d (expected 20)\n", x);
    queue_dequeue(&q, &x); printf("Deq3: %d (expected 30)\n", x);
    printf("Size: %d (expected 0)\n", queue_size(&q));

    // 4. Ошибка dequeue на пустой очереди
    printf("\n4. Dequeue empty queue: %d (expected QUEUE_ERR=1)\n", queue_dequeue(&q, &x));

    // 5. Уничтожение
    printf("\n5. Destroy queue\n");
    queue_destroy(&q);
    printf("Size after destroy: %d (expected 0)\n", queue_size(&q));

    return 0;
}
