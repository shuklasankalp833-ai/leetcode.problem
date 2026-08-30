int minimumDeletions(int* nums, int numsSize) {
    int i = 0, j = 0;
    for (int k = 1; k < numsSize; k++) {
        if (nums[k] < nums[i]) i = k;   // index of minimum
        if (nums[k] > nums[j]) j = k;   // index of maximum
    }

    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }

    int opt1 = j + 1;                  // remove both from front
    int opt2 = numsSize - i;           // remove both from back
    int opt3 = (i + 1) + (numsSize - j); // remove from both ends

    int result = opt1;
    if (opt2 < result) result = opt2;
    if (opt3 < result) result = opt3;

    return result;
}
