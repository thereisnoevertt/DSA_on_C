//
// Created by Никита on 13.01.2026.
// Реализация алгоритма сортировки слиянием
#include <stdio.h>
#define N 10

void merge(int arr[], int l, int m, int r){

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[], int l, int r) {
    if (l<r) {
        int mid = l + (r - l) / 2;
        mergesort(arr, l, mid);
        mergesort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

void print_arr(const int *arr, const int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
}


int main() {
    int arr[N] = {9, 4, 6, 3, 5, 2, 8, 1, 7, 0};
    int size_of_arr = sizeof(arr) / sizeof(arr[0]);
    mergesort(arr, 0, size_of_arr - 1);
    print_arr(arr, N);
    return 0;
}