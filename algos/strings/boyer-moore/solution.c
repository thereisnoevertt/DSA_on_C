//
// Created by Никита on 11.12.2025.
// Реализация алгоритма Бойера-Мура
#include <stdio.h>
#include <string.h>

#define ALPHABET 256

void boyer_moore(char *text, char *pattern, int n) {
    int m = (int)strlen(pattern);
    if (m == 0) return;

    // 1. Таблица последних вхождений
    int last[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        last[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        unsigned char c = (unsigned char)pattern[i];
        last[c] = i;
    }

    // 2. Поиск
    int s = 0;      // сдвиг шаблона
    int first = 1;  // для пробелов

    while (s <= n - m) {
        int j = m - 1;

        // сравниваем справа налево
        while (j >= 0 && pattern[j] == text[s + j]) {
            int pos = s + j + 1; // позиции с 1
            if (!first) printf(" ");
            printf("%d", pos);
            first = 0;
            j--;
        }

        if (j < 0) {
            // найдено вхождение
            s += 1;  // можно сдвинуть и больше, но для простоты 1
        } else {
            // неуспешное сравнение на позиции j
            int pos = s + j + 1;
            if (!first) printf(" ");
            printf("%d", pos);
            first = 0;

            unsigned char c = (unsigned char)text[s + j];
            int lo = last[c];
            int shift = j - lo;
            if (shift < 1) shift = 1;
            s += shift;
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char text[100005];
    char pattern[17];

    scanf("%s", text);
    scanf("%16s", pattern);

    int len = (int)strlen(text);
    if (len < n) {
        n = len;
    }

    boyer_moore(text, pattern, n);
    return 0;
}