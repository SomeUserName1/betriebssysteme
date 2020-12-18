#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_palindrome(char* str);

int main(void) {
    char test0[] = "a";
    char test1[] = "aa";
    char test2[] = "ana";
    char test3[] = "anna";
    char test4[] = "amanaplanacanalpanama";
    printf("test0: %s\n", is_palindrome(test0) ? "true" : "false");
    printf("test1: %s\n", is_palindrome(test1) ? "true" : "false");
    printf("test2: %s\n", is_palindrome(test2) ? "true" : "false");
    printf("test3: %s\n", is_palindrome(test3) ? "true" : "false");
    printf("test4: %s\n", is_palindrome(test4) ? "true" : "false");
    printf("Should be wrong: %s\n", is_palindrome("abc") ? "true" : "false");
    return 0;
}

bool is_palindrome(char* str) {
    char *end = str + strlen(str);

    for (; str < --end; ++str) {
        if (*str != *end) {
            return false;
        }
    }
    return true;
}
