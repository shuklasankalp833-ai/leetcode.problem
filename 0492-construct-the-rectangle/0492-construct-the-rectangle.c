#include <math.h>

int* constructRectangle(int area, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    int w = (int)sqrt((double)area);
    while (area % w != 0) {
        w--;
    }

    result[0] = area / w; // L
    result[1] = w;        // W

    return result;
}