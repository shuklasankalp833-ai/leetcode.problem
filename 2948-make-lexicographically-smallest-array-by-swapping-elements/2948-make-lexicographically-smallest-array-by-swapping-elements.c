#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Pair;

int cmpVal(const void* a, const void* b) {
    return ((Pair*)a)->val - ((Pair*)b)->val;
}

int cmpInt(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int* lexicographicallySmallestArray(int* nums, int numsSize, int limit, int* returnSize) {
    Pair* pairs = (Pair*)malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        pairs[i].val = nums[i];
        pairs[i].idx = i;
    }
    qsort(pairs, numsSize, sizeof(Pair), cmpVal);

    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    int i = 0;
    while (i < numsSize) {
        int j = i;
        // extend the group while consecutive sorted values are within limit
        while (j + 1 < numsSize && pairs[j + 1].val - pairs[j].val <= limit) {
            j++;
        }
        int groupSize = j - i + 1;

        // collect indices of this group and sort them
        int* indices = (int*)malloc(groupSize * sizeof(int));
        for (int k = 0; k < groupSize; k++) {
            indices[k] = pairs[i + k].idx;
        }
        qsort(indices, groupSize, sizeof(int), cmpInt);

        // assign sorted values to sorted indices
        for (int k = 0; k < groupSize; k++) {
            result[indices[k]] = pairs[i + k].val;
        }

        free(indices);
        i = j + 1;
    }

    free(pairs);
    return result;
}