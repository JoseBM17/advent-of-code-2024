#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <assert.h>
#include "../include/utils.h"
#include "../include/day_01/location.h"


static void process_input(char* content_input, location_list_t* left_list, location_list_t* right_list) {
    char* regex_pattern = "^([0-9]+) +([0-9]+)$";
    regex_t rgex;
    assert(regcomp(&rgex, regex_pattern, REG_EXTENDED) == 0);

    int n_matches = 3;
    regmatch_t matches[n_matches];

    char* line = strtok(content_input, "\n");
    while (line != NULL) {
        int ret = regexec(&rgex, line, n_matches, matches, 0);

        if (ret) {
            fprintf(stderr, "Line does not match pattern");
            exit(1);
        }

        long loc_id_left  = strtol(line + matches[1].rm_so, NULL, 10);
        long loc_id_right = strtol(line + matches[2].rm_so, NULL, 10);

        insert_sorted(left_list, loc_id_left);
        insert_sorted(right_list, loc_id_right);

        // Next line
        line = strtok(NULL, "\n");
    }

    regfree(&rgex);
}

int main() {
    
    char* content = read_file("inputs/day_01.txt");
    if (content == NULL) {
        exit(1);
    }

    location_list_t* left_list = create_location_list();
    location_list_t* right_list = create_location_list();

    process_input(content, left_list, right_list);
    
    // Calculate the distance between left list and right
    long distance = 0;
    location_t* current_left_loc = left_list->head;
    location_t* current_right_loc = right_list->head;

    while (current_left_loc->next != NULL && current_right_loc->next != NULL)
    {
        distance += labs(current_left_loc->id - current_right_loc->id);
        current_left_loc = current_left_loc->next;
        current_right_loc = current_right_loc->next;
    }

    distance += labs(current_left_loc->id - current_right_loc->id);

    current_left_loc = left_list->head;
    current_right_loc = right_list->head;
    long similarity = 0;
    long same_number_ocrr = 1;
    while (current_left_loc != NULL) {
        
        if (current_left_loc->next != NULL && 
                current_left_loc->id == current_left_loc->next->id) {
            
            current_left_loc = current_left_loc->next;
            same_number_ocrr++;
            continue;
        }

        while (current_right_loc != NULL && current_left_loc->id > current_right_loc->id ) {
            current_right_loc = current_right_loc->next;
        }

        long location_occurrence = 0;

        while (current_right_loc != NULL && current_left_loc->id == current_right_loc->id) {
            location_occurrence++;
            current_right_loc = current_right_loc->next;
        }

        similarity = similarity + (current_left_loc->id * location_occurrence * same_number_ocrr);

        same_number_ocrr = 1;
        current_left_loc = current_left_loc->next;
    }
      
    printf("Distance %ld\n", distance);
    printf("Similarity %ld\n", similarity);

    return 0;
}