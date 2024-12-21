#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int x;   
    int h;   
} Point;


Point* mergeSkylines(Point* left, int leftSize, Point* right, int rightSize, int* returnSize) {
    Point* merged = malloc((leftSize + rightSize) * sizeof(Point));
    int i = 0, j = 0, k = 0;
    int h1 = 0, h2 = 0; 
    
    while (i < leftSize && j < rightSize) {
        int x, maxH;
        if (left[i].x < right[j].x) {
            x = left[i].x;
            h1 = left[i].h;
            i++;
        } else if (left[i].x > right[j].x) {
            x = right[j].x;
            h2 = right[j].h;
            j++;
        } else {
            x = left[i].x;
            h1 = left[i].h;
            h2 = right[j].h;
            i++;
            j++;
        }
        maxH = (h1 > h2) ? h1 : h2;
        if (k == 0 || merged[k - 1].h != maxH) {
            merged[k].x = x;
            merged[k].h = maxH;
            k++;
        }
    }

    while (i < leftSize) {
        merged[k++] = left[i++];
    }

    while (j < rightSize) {
        merged[k++] = right[j++];
    }

    *returnSize = k;
    return merged;
}


Point* divideAndConquer(int** buildings, int start, int end, int* returnSize) {
    if (start == end) {
        Point* skyline = malloc(2 * sizeof(Point));
        skyline[0].x = buildings[start][0];
        skyline[0].h = buildings[start][2];
        skyline[1].x = buildings[start][1];
        skyline[1].h = 0;
        *returnSize = 2;
        return skyline;
    }

    int mid = (start + end) / 2;

    int leftSize, rightSize;
    Point* leftSkyline = divideAndConquer(buildings, start, mid, &leftSize);
    Point* rightSkyline = divideAndConquer(buildings, mid + 1, end, &rightSize);

    return mergeSkylines(leftSkyline, leftSize, rightSkyline, rightSize, returnSize);
}


int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize, int* returnSize, int** returnColumnSizes) {
    if (buildingsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int pointSize;
    Point* points = divideAndConquer(buildings, 0, buildingsSize - 1, &pointSize);

    int** result = malloc(pointSize * sizeof(int*));
    *returnColumnSizes = malloc(pointSize * sizeof(int));
    for (int i = 0; i < pointSize; i++) {
        result[i] = malloc(2 * sizeof(int));
        result[i][0] = points[i].x;
        result[i][1] = points[i].h;
        (*returnColumnSizes)[i] = 2;
    }

    *returnSize = pointSize;
    free(points);
    return result;
}