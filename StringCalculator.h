#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
bool detect_custom_delimiter(const char* str) {
    return str[0] == '/' && str[1] == '/';
}
 
void get_custom_delimiter(const char* str, char* delimiter) {
    const char* start = str + 2; // Skip over "//"
    size_t length = strcspn(start, "\n"); // Find the position of the newline character
    strncpy(delimiter, start, length); // Copy the delimiter
    delimiter[length] = '\0'; // Null-terminate the delimiter
}
 
void tokenize_numbers(const char* str, const char* delimiters, int* nums, int* num_count) {
    char* copy = strdup(str);
    char* token = strtok(copy, delimiters);
    while (token) {
        nums[(*num_count)++] = atoi(token);
        token = strtok(NULL, delimiters);
    }
    free(copy);
}
 
bool find_negatives(int* nums, int num_count, char* error_msg) {
    bool has_negatives = false;
    strcpy(error_msg, "negatives not allowed: ");
    for (int i = 0; i < num_count; i++) {
        if (nums[i] < 0) {
            has_negatives = true;
            char num_str[12];
            snprintf(num_str, sizeof(num_str), "%d ", nums[i]);
            strcat(error_msg, num_str);
        }
    }
    return has_negatives;
}
 
int sum_numbers(int* nums, int num_count) {
    int total = 0;
    for (int i = 0; i < num_count; i++) {
        if (nums[i] <= 1000) {
            total += nums[i];
        }
    }
    return total;
}
 
int process_and_sum(const char* str, const char* delimiters) {
    int nums[1000];
    int num_count = 0;
    tokenize_numbers(str, delimiters, nums, &num_count);
 
    char error_msg[256];
    if (find_negatives(nums, num_count, error_msg)) {
        return -1; // Indicate an error
    }
 
    return sum_numbers(nums, num_count);
}
 
int add(const char* str) {
    if (*str == '\0') {
        return 0;
    }
 
    char delimiter[10] = ",\n";
    if (detect_custom_delimiter(str)) {
        get_custom_delimiter(str, delimiter);
    }
 
    return process_and_sum(str, delimiter);
}
