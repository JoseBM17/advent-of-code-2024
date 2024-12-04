
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../include/utils.h"

typedef struct report {
    int* levels; // Dynamic array of levels
    int count;
} report_t;

report_t create_report(int* levels, int count) {
    report_t report;

    // Allocate memory for levels in the report
    report.levels = (int*)malloc(count * sizeof(int));
    if (!report.levels) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the levels to the report
    for (int i = 0; i < count; i++) {
        report.levels[i] = levels[i];
    }

    report.count = count;

    return report;
}

static void process_lines(const char* file_content, report_t** report_list, int* report_count) {
    char* content_copy = strdup(file_content);
    char* saveptr; // For preserving strtok state
    char* line = strtok_r(content_copy, "\n", &saveptr);

    // Process each line
    while (line != NULL) {

        // Count the numbers in the line
        int count = 0;
        char* temp_line = strdup(line);
        char* token = strtok(temp_line, " ");
        while (token != NULL) {
            count++;
            token = strtok(NULL, " ");
        }
        free(temp_line);

        // Allocate memory for the numbers array
        int* numbers = (int*)malloc(count * sizeof(int));
        if (!numbers) {
            fprintf(stderr, "Memory allocation failed\n");
            free(content_copy);
            exit(EXIT_FAILURE);
        }

        // Extract numbers from the line
        int index = 0;
        token = strtok(line, " ");
        while (token != NULL) {
            numbers[index++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Create the report
        report_t report = create_report(numbers, count);

        // Add the report to the report list
        *report_list = (report_t*)realloc(*report_list, (*report_count + 1) * sizeof(report_t));
        if (!*report_list) {
            fprintf(stderr, "Memory allocation failed for report_list\n");
            free(numbers);
            free(content_copy);
            exit(EXIT_FAILURE);
        }

        (*report_list)[*report_count] = report;
        (*report_count)++;

        // Free memory for numbers
        free(numbers);

        // Move to the next line
        line = strtok_r(NULL, "\n", &saveptr);
    }

    // Clean up
    free(content_copy);
}

static int check_level_direction(int i, int j) {
    return (i > j) - (i < j);
}

static bool is_safe_report(int* report_levels, int count) {
    int direction = 0;
    
    for (size_t i = 1; i < count; i++) {
        if (i==1) {
            direction = check_level_direction(report_levels[i-1], report_levels[i]);
        }

        if (direction == 0) { // Neither increasing nor decreasing
            return false;
        }

        if (direction != check_level_direction(report_levels[i-1], report_levels[i])) {
            return false;
        }

        if (abs(report_levels[i-1] - report_levels[i]) > 3) {
            return false;
        }   
    }
    return true;
}

static int check_safe_reports(report_t* report_list, int report_count) {
    int safe_reports = 0;
    for (size_t i = 0; i < report_count; i++)
    {
        if (is_safe_report(report_list[i].levels, report_list[i].count)) safe_reports++;
    }

    return safe_reports;
    
}

static bool is_safe_report_by_skiping_level(int* report_levels, int count) {
    bool safe = false;
    for (size_t skip_lvl = 0; skip_lvl < count; skip_lvl++) {
        int* skip_arr = (int*)malloc((count - 1) * sizeof(int));
        if (!skip_arr) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        int index = 0;
        for (int i = 0; i < count; i++) {
            if (i != skip_lvl) {
                skip_arr[index++] = report_levels[i];
            }
        }
    
        safe |= is_safe_report(skip_arr, count-1);
            
        free(skip_arr);    
    }
    return safe;
}

static int check_safe_reports_part2(report_t* report_list, int report_count) {
    int safe_reports = 0;
    for (size_t i = 0; i < report_count; i++)
    {
        if (is_safe_report(report_list[i].levels, report_list[i].count)) {
            safe_reports++;
        } else { 
            // Unsafe reports
            if (is_safe_report_by_skiping_level(report_list[i].levels, report_list[i].count)) {
                safe_reports++;
            }
        }
    }
    return safe_reports;
}

int main() {
    char* content = read_file("inputs/day_02.txt");
    if (content == NULL) {
        exit(1);
    }

    report_t* report_list = NULL;
    int report_count = 0;

    // Process the file content
    process_lines(content, &report_list, &report_count);

    int p1 = check_safe_reports(report_list, report_count);
    int p2 = check_safe_reports_part2(report_list, report_count);
    printf("Part 1: %d\nPart 2: %d\n", p1, p2);
    return 0;
}