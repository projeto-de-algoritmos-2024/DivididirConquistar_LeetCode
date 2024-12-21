#include <stdio.h>
#include <stdlib.h>


void merge(int* nums, int left, int mid, int right) {
    int n1 = mid - left + 1; 
    int n2 = right - mid;    

    int* leftArray = malloc(n1 * sizeof(int));
    int* rightArray = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        leftArray[i] = nums[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = nums[mid + 1 + j];
    }

    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            nums[k] = leftArray[i];
            i++;
        } else {
            nums[k] = rightArray[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        nums[k] = leftArray[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        nums[k] = rightArray[j];
        j++;
        k++;
    }

    
    free(leftArray);
    free(rightArray);
}


void mergeSort(int* nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; 

        
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        
        merge(nums, left, mid, right);
    }
}


int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize; 
    mergeSort(nums, 0, numsSize - 1);
    return nums; 
}