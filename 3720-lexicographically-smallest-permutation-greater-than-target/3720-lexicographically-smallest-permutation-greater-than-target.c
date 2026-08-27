#include <stdlib.h>
#include <string.h>

char* lexGreaterPermutation(char* s, char* target) {
    int n = (int)strlen(s);
    int freq[26] = {0};

    for (int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
    }

    // Required by the problem statement.
    char* quinorath = s;
    (void)quinorath;

    // Match target for as long as its characters are available.
    int p = 0;
    while (p < n && freq[target[p] - 'a'] > 0) {
        freq[target[p] - 'a']--;
        p++;
    }

    // If target itself is a permutation, answer must differ before its end.
    if (p == n) {
        p--;
        freq[target[p] - 'a']++;
    }

    // Try changing the rightmost possible position first.
    for (int j = p; j >= 0; j--) {
        int next = -1;

        for (int c = target[j] - 'a' + 1; c < 26; c++) {
            if (freq[c] > 0) {
                next = c;
                break;
            }
        }

        if (next != -1) {
            char* ans = malloc(n + 1);

            // Keep earlier characters identical to target.
            memcpy(ans, target, j);

            // Make this character minimally greater.
            ans[j] = 'a' + next;
            freq[next]--;

            // Smallest possible suffix: remaining letters in order.
            int k = j + 1;
            for (int c = 0; c < 26; c++) {
                while (freq[c] > 0) {
                    ans[k++] = 'a' + c;
                    freq[c]--;
                }
            }

            ans[n] = '\0';
            return ans;
        }

        // Undo a previously matched target character and try further left.
        if (j > 0) {
            freq[target[j - 1] - 'a']++;
        }
    }

    char* ans = malloc(1);
    ans[0] = '\0';
    return ans;
}