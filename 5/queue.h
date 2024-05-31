#ifndef INC_5_QUEUE_H
#define INC_5_QUEUE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue{
    uint64_t n, maxn, head, tail;
    void* *data;
} Queue;

uint64_t push_back(Queue*, void*);
void* pop_front(Queue*);
uint64_t make_queue(Queue** info, uint64_t num);
uint64_t free_queue(Queue* queue, void (*free_func) (void* data));
uint64_t empty(Queue* queue);
uint64_t print_elements(Queue* queue, void (*print_func) (void* data));


#endif //INC_5_QUEUE_H
