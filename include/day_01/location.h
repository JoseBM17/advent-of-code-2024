#ifndef LOCATION_H
#define LOCATION_H

#include <stdlib.h>

typedef struct location {
    long id;
    struct location* next;
} location_t;


typedef struct location_list {
    location_t* head;
    location_t* tail;
} location_list_t;


location_list_t* create_location_list();
void insert_sorted(location_list_t* l, long location_id);
void free_location_list(location_list_t* list);

#endif