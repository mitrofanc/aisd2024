#include "deck.h"

#if DECK_TYPE
int push_back(Deck* deck, void* new){
    if (deck->n == deck->maxn) { return 1; }
    else{
        *(deck->data + deck->tail) = new;
        deck->tail = (deck->tail + 1) % (deck->maxn);
        deck->n++;
    }
    return 0;
}

int push_front(Deck* deck, void* new){
    if (deck->n == deck->maxn) { return 1; }
    else{
        if (deck->head - 1 < 0){ deck->head = deck->maxn - 1; }
        else { deck->head = (deck->head - 1) % (deck->maxn); }
        *(deck->data + deck->head) = new;
        deck->n++;
    }
    return 0;
}

int pop_back(Deck* deck, void** info){
    if (deck->n == 0) { return 1; }
    else{
        *info = *(deck->data + deck->tail);
        deck->tail = (deck->tail - 1) % (deck->maxn);
        deck->n -= 1;
    }
    return 0;
}

int pop_front(Deck* deck, void** info){
    if (deck->n == 0) { return 1; }
    else{
        *info = *(deck->data + deck->head);
        deck->head = (deck->head + 1) % (deck->maxn);
        deck->n -= 1;
    }
    return 0;
}

int make_deck(Deck** info, int num){
    *info = (Deck*)calloc(1, sizeof(Deck));
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

int free_deck(Deck* deck, void (*free_func) (void* data)){
    if (!deck) { return 1; }
    for (int i = 0; i < deck->n; i++){
        free_func(deck->data[(deck->head + i) % deck->maxn]);
    }
    free(deck->data);
    free(deck);
    return 0;
}

int print_elements(Deck* deck, void (*print_func) (void* data)){
    if (!deck) { return 1; }
    for (int i = 0; i < deck->n; i++){
        print_func(deck->data[(deck->head + i) % deck->maxn]);
    }
    return 0;
}

int read_first(Deck* deck, void** info){
    if (deck->n == 0){ return 1; }
    else{
        *info = *(deck->data + deck->head);
        return 0;
    }
}

int empty(Deck* deck){
    if (deck->n == 0) { return 0; }
    else { return 1; }
}

#else

int push_back(Deck* deck, void* new){
    Node* tmp = calloc(1, sizeof(Node));
    if (!tmp) { return 1; }
    if (deck->n == 0){
        deck->head = tmp;
        tmp->next = tmp;
    }
    else{
        tmp->next = deck->tail->next;
        deck->tail->next = tmp;
    }
    tmp->data = new;
    deck->tail = tmp;
    deck->n++;
    return 0;
}

int push_front(Deck* deck, void* new){
    Node* tmp = calloc(1, sizeof(Node));
    if (!tmp) { return 1; }
    if (deck->n == 0){
        deck->head = tmp;
        deck->tail = tmp;
    }
    else{
        tmp->next = deck->head;
        deck->head = tmp;
    }
    deck->tail->next = tmp;
    tmp->data = new;
    deck->n++;
    return 0;
}

int pop_back(Deck* deck, void** info){
    if (deck->n == 0){ return 1; }
    *info = deck->tail->data;
    Node* ptr = deck->head;
    for (int i = 0; i < deck->n - 1; i++){
        ptr = ptr->next;
    }
    Node* f = ptr->next;
    ptr->next = deck->head;
    deck->tail = ptr;
    free(f);
    deck->n--;
    return 0;
}

int pop_front(Deck* deck, void** info){
    if (deck->n == 0){ return 1; }
    else{
        *info = deck->head->data;
        Node* tmp = deck->head;
        deck->head = tmp->next;
        deck->tail->next = tmp->next; 
        free(tmp);
        deck->n--;
    }
    
    return 0;
}


int make_deck(Deck** info, int num){
    *info = (Deck*) calloc(1, sizeof(Deck));
    if (!*info) { return 1; }
    (*info)->n = 0;
    (*info)->maxn = num;
    (*info)->head = (*info)->tail = NULL;
    return 0;
}

int free_deck(Deck* deck, void (*free_func) (void* data)){
    if (!deck) { return 1; }
    if (deck->n){
        Node* ptr = deck->head;
        Node* ptr_prev = NULL;
        deck->tail->next = NULL;
        while (ptr){
            ptr_prev = ptr;
            ptr = ptr->next;
            free_func(ptr_prev->data);
            free_func(ptr_prev);
        }
    }
    free(deck);
    return 0;
}

int print_elements(Deck* deck, void (*print_func) (void* data)){
    if (!deck || !deck->n) { return 1; }
    Node* ptr = deck->head;
    deck->tail->next = NULL;
    while (ptr){
        print_func(ptr->data);
        ptr = ptr->next;
    }
    deck->tail->next = deck->head;
    return 0;
}

int read_first(Deck* deck, void** info){
    if (deck->n == 0){ return 1; }
    else{
        *info = deck->head->data;
        return 0;
    }
}

int empty(Deck* deck){
    if (deck->n == 0) { return 0; }
    else { return 1; }
}
#endif