/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    int firstIdx = -1;
    int prevIdx = -1;
    long minDist = INT_MAX; // use long/large sentinel to avoid overflow issues

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;
    int idx = 1;

    while (curr && curr->next) {
        if ((curr->val > prev->val && curr->val > curr->next->val) ||
            (curr->val < prev->val && curr->val < curr->next->val)) {
            if (firstIdx == -1) {
                firstIdx = idx;
            } else {
                int dist = idx - prevIdx;
                if (dist < minDist) minDist = dist;
            }
            prevIdx = idx;
        }

        prev = curr;
        curr = curr->next;
        idx++;
    }

    if (firstIdx == -1 || prevIdx == firstIdx) {
        result[0] = -1;
        result[1] = -1;
        return result;
    }

    result[0] = (int)minDist;
    result[1] = prevIdx - firstIdx;
    return result;
}