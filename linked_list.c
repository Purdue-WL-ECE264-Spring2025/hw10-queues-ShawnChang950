#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (!node){
      return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    if (!list->head) {
        list->head = new_node(0); //head node points to null if list not initialized
    }
    
    struct list_node *node = new_node(value);
    if (!list->head->next) { // Empty list case, so my new node becomes the head and the tail
        list->head->next = node;
        list->head->value = (size_t)node;
        return;
    }
    
    node->next = list->head->next;//new node pts to first node current
    list->head->next = node; //new ->first node
}

void insert_at_tail(struct linked_list *list, size_t value) {
    if (!list->head) { //IF its not initial, then create head node that points to NULL
        list->head = new_node(0);
    }
    
    struct list_node *node = new_node(value);
    if (!list->head->next) { // Empty list case
        list->head->next = node;

        list->head->value = (size_t)node;
        return;
    }
    
    struct list_node *tail = (struct list_node *)list->head->value;
    tail->next = node;
    list->head->value = (size_t)node; // Update tail reference
}

// Remove and return the value of the head node
size_t remove_from_head(struct linked_list *list) {
    if (!list->head || !list->head->next) {
      return 0; 
    }                 //chekc for NULL conditions, return 0 if NULL
    
    struct list_node *old = list->head->next;
    size_t value = old->value;
    list->head->next = old->next;
    free(old);
    
    if (!list->head->next) {
        list->head->value = 0; // Reset tail
    }
    return value;
}

// Remove and return the value of the tail node
size_t remove_from_tail(struct linked_list *list) {
    if (!list->head || !list->head->next)
    { 
      return 0; //empty list
    }
    
    struct list_node *current = list->head->next;
    struct list_node *prev = list->head;
    
   
    if (!current->next) {  //case wehre there is 1 element
        size_t value = current->value;
        free(current);
        list->head->next = NULL;
        list->head->value = 0;
        return value;
    }

    while (current->next) { //this blcok finds the second to last
        prev = current;
        current = current->next;
    }
    
    size_t value = current->value; //free aray
    free(current);
    prev->next = NULL;
    list->head->value = (size_t)prev; 
    return value;
}

// Free all nodes in the linked list
void free_list(struct linked_list list) {
    struct list_node *current = list.head;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
