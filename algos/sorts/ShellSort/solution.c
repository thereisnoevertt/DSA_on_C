//
// Created by Никита on 23.12.2025.
// Реализация алгоритма сортировки Шелла
#include <stdio.h>
#define N 10

void shell_sort(int* arr, const int count) {
    for (int gap = count/2; gap > 0; gap /=2) {
        for (int i = gap; i < count; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j-gap] > temp) {
                arr[j] = arr[j - gap];
                j -=gap;
            }
            arr[j] = temp;
        }
    }

}

void print_arr(const int *arr, const int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[N] = {9, 4, 6, 3, 5, 2, 8, 1, 7, 0};
    shell_sort(arr, N);
    print_arr(arr, N);
    return 0;
}