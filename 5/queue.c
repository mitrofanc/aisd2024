#include "queue.h"

uint64_t push_back(Queue* queue, void* new){
    if (queue->n == queue->maxn) { return 1; }
    else{
        *(queue->data + queue->tail) = new;
        queue->tail = (queue->tail + 1) % (queue->maxn);
        queue->n++;
    }
    return 0;
}

void* pop_front(Queue* queue){
    if (queue->n == 0) { return NULL; }
    else{
        void* info = *(queue->data + queue->head);
        queue->head = (queue->head + 1) % (queue->maxn);
        queue->n -= 1;
        return info;
    }
}

uint64_t make_queue(Queue** info, uint64_t num){
    *info = (Queue*)calloc(1, sizeof(Queue));
    if (!*info) { return 1; }
    (*info)->data = (void**)calloc(num, sizeof(void*));
    if(!(*info)->data){
        free(*info);
        return 1;
    }
    (*info)->maxn = num;
    (*info)->n = (*info)->head = (*info)->tail = 0;
    return 0;
}

uint64_t free_queue(Queue* queue, void (*free_func) (void* data)){
    if (!queue) { return 1; }
    for (int i = 0; i < queue->n; i++){
        free_func(queue->data[(queue->head + i) % queue->maxn]);
    }
    free(queue->data);
    free(queue);
    return 0;
}

uint64_t empty(Queue* queue){
    if (queue->n == 0) { return 1; }
    else { return 0; }
}

uint64_t print_elements(Queue* queue, void (*print_func) (void* data)){
    if (!queue) { return 1; }
    for (int i = 0; i < queue->n; i++){
        print_func(queue->data[(queue->head + i) % queue->maxn]);
    }
    return 0;
}