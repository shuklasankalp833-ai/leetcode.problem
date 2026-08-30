#include <string.h>
#include <stdbool.h>

bool rotateString(char* s, char* goal) {
    int len_s = strlen(s);
    int len_goal = strlen(goal);

    if (len_s != len_goal) return false;

    // Build s + s
    char doubled[2001]; // constraints: length <= 100, so 200 is enough, but padded
    strcpy(doubled, s);
    strcat(doubled, s);

    // Check if goal is a substring of doubled
    return strstr(doubled, goal) != NULL;
}