#include <stdlib.h>
#include <string.h>

char* shortestBeautifulSubstring(char* s, int k) {
    int n = strlen(s);
    int minLen = n + 1;
    int ones = 0, left = 0;

    // Pass 1: sliding window to find the minimal valid length
    for (int right = 0; right < n; right++) {
        if (s[right] == '1') ones++;
        while (ones >= k) {
            int len = right - left + 1;
            if (len < minLen) minLen = len;
            if (s[left] == '1') ones--;
            left++;
        }
    }

    if (minLen > n) {                 // no valid substring exists
        char* res = malloc(1);
        res[0] = '\0';
        return res;
    }

    // Pass 2: among all windows of length minLen with >= k ones,
    // keep the lexicographically smallest
    char* best = NULL;
    ones = 0;
    left = 0;
    for (int right = 0; right < n; right++) {
        if (s[right] == '1') ones++;
        if (right - left + 1 > minLen) {
            if (s[left] == '1') ones--;
            left++;
        }
        if (right - left + 1 == minLen && ones >= k) {
            if (best == NULL || strncmp(s + left, best, minLen) < 0) {
                if (best == NULL) best = malloc(minLen + 1);
                strncpy(best, s + left, minLen);
                best[minLen] = '\0';
            }
        }
    }

    if (best == NULL) {
        best = malloc(1);
        best[0] = '\0';
    }
    return best;
}