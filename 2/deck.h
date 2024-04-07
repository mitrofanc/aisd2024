#ifndef DECK
#define DECK
#include <stdio.h>
#include <stdlib.h>

#ifndef DECK_TYPE
#define DECK_TYPE 1
#endif

#if DECK_TYPE 

typedef struct Deck{
    int n, maxn, head, tail;
    void* *data;
} Deck;

#else

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct Deck {
    Node *head;
    Node *tail;
    int n, maxn;
} Deck;

#endif

int push_back(Deck*, void*);
int push_front(Deck*, void*);
int pop_back(Deck*, void**);
int pop_front(Deck*, void**);
int make_deck(Deck** info, int num);
int free_deck(Deck* deck, void (*free_func) (void* data));
int print_elements(Deck* deck, void (*print_func) (void* data));
int read_first(Deck* deck, void** info);
int empty(Deck* deck);

#endif