#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* lexPalindromicPermutation(char* s, char* target) {
    int n = strlen(s);
    int cnt[26] = {0};

    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    /* Check whether a palindromic permutation is possible */
    int oddCount = 0;
    char middle = '\0';

    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2) {
            oddCount++;
            middle = 'a' + i;
        }
    }

    if (oddCount > 1) {
        char* ans = malloc(1);
        ans[0] = '\0';
        return ans;
    }

    int m = n / 2;
    int half[26];

    for (int i = 0; i < 26; i++) {
        half[i] = cnt[i] / 2;
    }

    char* left = malloc(m + 1);
    char* candidate = malloc(n + 1);

    /*
     * Try the smallest possible character at every position.
     * Keep it only if the largest possible completion can
     * still be greater than target.
     */
    for (int pos = 0; pos < m; pos++) {
        bool found = false;

        for (int c = 0; c < 26; c++) {
            if (half[c] == 0)
                continue;

            half[c]--;
            left[pos] = 'a' + c;

            int k = 0;

            /* Fixed prefix */
            for (int i = 0; i <= pos; i++) {
                candidate[k++] = left[i];
            }

            /* Largest possible remaining left half */
            for (int ch = 25; ch >= 0; ch--) {
                for (int x = 0; x < half[ch]; x++) {
                    candidate[k++] = 'a' + ch;
                }
            }

            /* Middle */
            if (n % 2 == 1) {
                candidate[k++] = middle;
            }

            /* Mirror */
            int leftLen = m;
            for (int i = leftLen - 1; i >= 0; i--) {
                candidate[k++] = candidate[i];
            }

            candidate[k] = '\0';

            if (strcmp(candidate, target) > 0) {
                found = true;
                break;
            }

            half[c]++;
        }

        if (!found) {
            free(left);
            free(candidate);

            char* ans = malloc(1);
            ans[0] = '\0';
            return ans;
        }
    }

    /* Build final answer */
    int k = 0;

    for (int i = 0; i < m; i++) {
        candidate[k++] = left[i];
    }

    if (n % 2 == 1) {
        candidate[k++] = middle;
    }

    for (int i = m - 1; i >= 0; i--) {
        candidate[k++] = left[i];
    }

    candidate[k] = '\0';

    free(left);

    if (strcmp(candidate, target) <= 0) {
        free(candidate);

        char* ans = malloc(1);
        ans[0] = '\0';
        return ans;
    }

    return candidate;
}