//
// Created by Никита on 17.12.2025.
// Реализация динамического массива

/*В проект представлены функции для создания, удаления массива
 *добавления элементов, вставки,
 *удаления элементов,
 *утилитарные функции: очищение, проверка на пустоту, получение по элементу */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct darray {
    int *data; //указатель на блок памяти
    size_t size; //размер
    size_t capacity; //вместимость
} intdarr;

enum {
    DARR_OK = 0,
    DARR_ERR = 1,
};

//инициализация массива
int da_init(intdarr *darr) {
    if (!darr) {
        return DARR_ERR;
    }
    darr->size = 0;
    darr->capacity = 10;
    darr->data = (int*)(malloc(darr->capacity * sizeof(int)));

    if (!darr->data) {
        darr->data = NULL;
        darr->size = 0;
        darr->capacity = 0;
        return DARR_ERR;
    }
    return DARR_OK;
}

//уничтожение массива
void da_destroy(intdarr *darr) {
    if (!darr) return;
    free(darr->data);
    darr->data = NULL;
    darr->size = 0;
    darr->capacity = 0;
}

//перераспределение памяти в два раза
int da_reserve(intdarr *darr) {
    if (!darr) {
        return DARR_ERR;
    }

    const size_t new_cap = darr->capacity * 2;
    int *tmp = realloc(darr->data, new_cap * sizeof(int));
    if (!tmp) {
        return DARR_ERR;
    }

    darr->data = tmp;
    darr->capacity = new_cap;
    return DARR_OK;
}

//добавление в конец массива
int da_push(intdarr *darr, const int elem) {
    if (!darr) {
        return DARR_ERR;
    }

    if (darr->size == darr->capacity) {
        if (da_reserve(darr) != DARR_OK) {
            return DARR_ERR;
        }
    }

    darr->data[darr->size] = elem;
    darr->size += 1;
    return DARR_OK;
}

//удаление последнего элемента
int da_pop(intdarr *darr) {
    if (!darr) {
        return DARR_ERR;
    }

    if (darr->size > 0) {
        darr->size -= 1;
    }
    return DARR_OK;
}

//добавление элемента по индексу массива
int da_push_by_index(intdarr *darr, const size_t index, const int elem) {
    if (!darr) return DARR_ERR;
    if (index > darr->size) {
        return DARR_ERR;
    }  // можно index == size (в конец)

    if (darr->size == darr->capacity) {
        if (da_reserve(darr) != DARR_OK) {
            return DARR_ERR;
        }
    }

    // сдвиг вправо: от конца к началу, чтобы не перезаписать данные
    for (size_t i = darr->size; i > index; --i) {
        darr->data[i] = darr->data[i - 1];
    }

    darr->data[index] = elem;
    darr->size += 1;
    return DARR_OK;
}

//вставка по индексу без сдвига
int da_set(intdarr *darr, const size_t index, const int elem) {
    if (!darr) {
        return DARR_ERR;
    }
    if (index >= darr->size) {
        return DARR_ERR;   // только существующие элементы
    }
    darr->data[index] = elem;
    return DARR_OK;
}

//удаление по индексу со сдвигом
int da_pop_by_index(intdarr *darr, const size_t index) {
    if (!darr) {
        return DARR_ERR;
    }
    if (darr->size == 0) {
        return DARR_ERR;
    }
    if (index >= darr->size) {
        return DARR_ERR;
    }

    // сдвиг влево
    for (size_t i = index; i + 1 < darr->size; ++i) {
        darr->data[i] = darr->data[i + 1];
    }
    darr->size -= 1;
    return DARR_OK;
}

//очищение массива
void da_clear(intdarr *darr) {
    darr->size = 0;
    darr->data = NULL;
    darr->capacity = 0;
}

//получение по индексу
int da_get(const intdarr *darr, const size_t index, int *out) {
    if (!darr || !out) {
        return DARR_ERR;
    }
    if (index >= darr->size) {
        return DARR_ERR;
    }

    *out = darr->data[index];
    return DARR_OK;
}

//проверка на пустоту
int da_is_empty(const intdarr *darr, int *out_empty) {
    if (!darr || !out_empty) {
        return DARR_ERR;
    }
    *out_empty = (darr->size == 0);
    return DARR_OK;
}
int main() {
    intdarr darr;
    da_init(&darr);
    da_push(&darr, 10);
    da_push(&darr, 11);
    da_push(&darr, 12);

    int a;
    da_get(&darr, 2, &a);
    printf("%d", a);
    return 0;
}