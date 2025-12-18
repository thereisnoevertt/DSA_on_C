#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} node;

enum {
    LIST_OK     = 0,
    LIST_EINVAL = -1,
    LIST_ENOMEM = -2,
    LIST_EEMPTY = -3,
    LIST_ERANGE = -4
};

//создаём узел
static node* node_new(const int data) {
    node* n = (node*)malloc(sizeof(*n));
    if (!n) {
        return NULL;
    }
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

//функция для возвращения размера списка
size_t list_size(const node* head) {
    size_t count = 0;
    for (const node* cur = head; cur != NULL; cur = cur->next) {
        count++;
    }
    return count;
}

//вставка в голову
int insert_in_head(node** head, int data) {
    if (head == NULL) {
        return LIST_EINVAL;
    }

    node* new_node = node_new(data);
    if (new_node == NULL) {
        return LIST_ENOMEM;
    }

    new_node->next = *head;
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;

    return LIST_OK;
}

//вставка в хвост
int insert_in_tail(node** head, int data) {
    if (head == NULL) {
        return LIST_EINVAL;
    }

    node* new_node = node_new(data);
    if (new_node == NULL) {
        return LIST_ENOMEM;
    }

    if (*head == NULL) {
        *head = new_node;
        return LIST_OK;
    }

    node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
    return LIST_OK;
}

/* 0-based, position == size допускаем (вставка в хвост) */
int insert_node(node** head, int position, int data) {
    if (head == NULL || position < 0) {
        return LIST_EINVAL;
    }

    if (position == 0) {
        return insert_in_head(head, data);
    }

    if (*head == NULL) {
        return LIST_ERANGE;
    }

    node* temp = *head;
    for (int i = 0; i < position - 1; i++) {
        if (temp == NULL) {
            return LIST_ERANGE;
        }
        temp = temp->next;
    }
    if (temp == NULL) {
        return LIST_ERANGE;
    }

    node* new_node = node_new(data);
    if (new_node == NULL) {
        return LIST_ENOMEM;
    }

    new_node->next = temp->next;
    new_node->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = new_node;
    }
    temp->next = new_node;

    return LIST_OK;
}

//удаление из головы
int delete_from_head(node** head) {
    if (head == NULL) {
        return LIST_EINVAL;
    }
    if (*head == NULL) {
        return LIST_EEMPTY;
    }

    node* temp = *head;
    *head = temp->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
    return LIST_OK;
}

//удаление из хвоста
int delete_from_tail(node** head) {
    if (head == NULL) {
        return LIST_EINVAL;
    }
    if (*head == NULL) {
        return LIST_EEMPTY;
    }

    node* temp = *head;

    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return LIST_OK;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    free(temp);
    return LIST_OK;
}

/* 0-based */
int delete_at_position(node** head, int position) {
    if (head == NULL || position < 0) {
        return LIST_EINVAL;
    }
    if (*head == NULL) {
        return LIST_EEMPTY;
    }

    node* temp = *head;
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return LIST_ERANGE;
    }

    if (temp->prev == NULL) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
        return LIST_OK;
    }

    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    return LIST_OK;
}

//получение узла по позиции
int get_at(const node* head, int position, int* out_value) {
    if (out_value == NULL || position < 0) {
        return LIST_EINVAL;
    }

    const node* temp = head;
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return LIST_ERANGE;
    }

    *out_value = temp->data;
    return LIST_OK;
}

//печать списка
void list_print(const node* head) {
    printf("Forward List: ");
    for (const node* t = head; t != NULL; t = t->next) {
        printf("%d ", t->data);
    }
    printf("\n");
}

//список в обратном порядке
void list_print_reverse(const node* head) {
    printf("Reverse List: ");

    if (head == NULL) {
        printf("\n");
        return;
    }

    const node* t = head;
    while (t->next != NULL) {
        t = t->next;
    }

    while (t != NULL) {
        printf("%d ", t->data);
        t = t->prev;
    }
    printf("\n");
}

//уничтожение списка
void free_list(node** head) {
    if (head == NULL) {
        return;
    }
    while (*head != NULL) {
        (void)delete_from_head(head);
    }
}
