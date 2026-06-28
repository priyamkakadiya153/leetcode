#include <stdlib.h>

// Merge two sorted halves arr[l..m] and arr[m+1..r]
void merge(int *arr, int l, int m, int r, int *temp) {
    int i = l;      // left index
    int j = m + 1;  // right index
    int k = l;      // merged index

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= m) {
        temp[k++] = arr[i++];
    }
    while (j <= r) {
        temp[k++] = arr[j++];
    }

    for (int p = l; p <= r; p++) {
        arr[p] = temp[p];
    }
}

// Recursive merge sort
void mergeSort(int *arr, int l, int r, int *temp) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, temp);
        mergeSort(arr, m + 1, r, temp);
        merge(arr, l, m, r, temp);
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    int *res = (int*)malloc(numsSize * sizeof(int));
    int *temp = (int*)malloc(numsSize * sizeof(int)); 

    for (int i = 0; i < numsSize; i++) {
        res[i] = nums[i];
    }

    mergeSort(res, 0, numsSize - 1, temp);

    free(temp); 

    *returnSize = numsSize;
    return res;
}
