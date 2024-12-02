#include <stdio.h>
#include "../include/day_01/location.h"

static location_t* create_location_node(long location_id) {
    location_t* node = (location_t*)malloc(sizeof(location_t));
    node->id = location_id;
    node->next = NULL;
    return node;
}

location_list_t* create_location_list() {
    location_list_t* list = (location_list_t*)malloc(sizeof(location_list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insert_sorted(location_list_t* l, long location_id) {
    location_t* new_loc = create_location_node(location_id);

    // Empty list
    if (l->head == NULL) {
        l->head = new_loc;
        l->tail = new_loc;
        return;
    }

    // Insert at the beginning
    if (new_loc->id <= l->head->id) { 
        new_loc->next = l->head;
        l->head = new_loc;
        return;
    }

    // Insert at the end
    if (new_loc->id >= l->tail->id )
    {
        l->tail->next = new_loc;
        l->tail = new_loc;
        return;
    }

    // Insert in the middle
    location_t* current = l->head;

    while (current->next != NULL && current->next->id <= new_loc->id) {
        current = current->next;
    }
    new_loc->next = current->next;
    current->next = new_loc;
}

void free_location_list(location_list_t* list) {
    location_t* current = list->head;
    location_t* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(list);
}

void print_list(location_list_t* list) {
    location_t* current = list->head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%ld -> ", current->id);
        current = current->next;
    }
    printf("NULL\n");
}
