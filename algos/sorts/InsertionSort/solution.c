//
// Created by Никита on 23.12.2025.
// Реализация алгоритма сортировки вставкой

#include <stdio.h>
#define N 10

void insertion_sort(int* arr, const int count) {
    for (int i = 1; i < count; i++) {
        int key = arr[i];
        int j = i - 1;
        while (arr[j] > key && j >= 0) {
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }
}

void print_arr(const int *arr, const int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[N] = {9, 4, 6, 3, 5, 2, 8, 1, 7, 0};
    insertion_sort(arr, N);
    print_arr(arr, N);
    return 0;
}