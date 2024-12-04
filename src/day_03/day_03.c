#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/utils.h"

static void process_input(char* content_input) {
    // Regex pattern for mul(X,Y)
    char* regex_pattern = "do\\(\\)|don't\\(\\)|mul\\([0-9]{1,3},[0-9]{1,3}\\)";
    regex_t rgex;
    assert(regcomp(&rgex, regex_pattern, REG_EXTENDED) == 0);

    // To store regex match
    regmatch_t match;

    // Process each line
    char* line = strtok(content_input, "\n");

    int p1 = 0;
    int p2 = 0;

    bool do_enable = true;

    while (line != NULL) {
        char* cursor = line;

        while (regexec(&rgex, cursor, 1, &match, 0) == 0 && *cursor != '\0') {
            int start = match.rm_so;
            int end = match.rm_eo;

            // Calculate the match length
            int match_length = end - start;

            // Allocate exact memory for matched_text
            char* matched_text = (char*)malloc(match_length + 1);
            if (!matched_text) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&rgex);
                return;
            }

            // Copy the match into the allocated buffer
            snprintf(matched_text, match_length + 1, "%s", cursor + start);

            if (strcmp(matched_text, "do()") == 0) {
                do_enable = true;
                // Move the cursor forward
                cursor += end;
                continue;
            }

            if (strcmp(matched_text, "don't()") == 0) {
                do_enable = false;
                // Move the cursor forward
                cursor += end;
                continue;
            }

            // Extract the digits X and Y using sscanf
            int x, y;
            if (sscanf(matched_text, "mul(%d,%d)", &x, &y) == 2) {
                p1 += (x*y);
                if (do_enable) p2 +=(x*y);
            } else {
                fprintf(stderr, "Failed to extract digits from: %s\n", matched_text);
            }

            // Free the allocated memory for matched_text
            free(matched_text);

            // Move the cursor forward
            cursor += end;
        }

        // Next line
        line = strtok(NULL, "\n");
    }

    printf("Part 1: %d\nPart 2: %d\n", p1,p2);

    // Free the regex
    regfree(&rgex);
}

int main() {
    char* content = read_file("inputs/day_03.txt");
    if (content == NULL) {
        exit(1);
    }

    process_input(content);

}
