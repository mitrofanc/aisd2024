#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "deck.h"

#define floor(x) ((float)((int)x))
#define PROMPT "> "
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#ifndef NDEBUG 
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...)
#endif


typedef struct Patient{
    char* id; //todo char*
    int ta;
    int ts;
} Patient;

int get_pos_int();
int count_sub(char*, char*);
Deck* input_queue();
int output_queue(Deck*);
void print_funcv(void*);
int free_deck_p(Deck*);
void free_funcv(void*);
void clearbuf();
int output_by_time(Deck*);
char* str_in(char* invite);

int main(){
    Deck* deck = input_queue();
    if (!deck){ return 1; }
    output_by_time(deck);
    free_deck_p(deck);
    return 0;
}

// int get_pos_int(){
//     float tmp = -1;
//     int flag = scanf("%f", &tmp);
//     printf("\n");
//     while ((floor(tmp) - tmp != 0) || (tmp < 0)){
//         if (flag == EOF){
//             printf("Exit\n");
//             return -1;
//         }
//         clearbuf();
//         flag = scanf("%f", &tmp);
//     }
//     return (int) tmp;
// }

int count_sub(char* str, char* sep){
    int num = 0;
    while (*str != '\0'){
        if (strncmp(str, sep, strlen(sep)) == 0){
            num += 1;
            str += strlen(sep) - 1;
        }
        str += 1;
    }
    return num;
}

Deck* input_queue(){
    Deck* deck = NULL;
    if (make_deck(&deck, 30)) { printf("Failed to allocate memory\n"); return NULL;} // Making deck
    printf("Input the information about patients:\n");
    char* str = str_in(PROMPT);
    char* sep = " ";
    int num = count_sub(str, sep) + 1;
    if (num > 30) { 
        printf("Unavailable number of patients\n"); 
        return NULL;
    }
    char* person = strtok(str, sep);
    while (person){
        int i = 0; // Person counter
        Patient* patient = calloc(1, sizeof(Patient));
        while ((int)(*(person + i)) != '/'){
            patient->id = realloc(patient->id, (i + 2) * sizeof(char));
            *((patient->id) + i) = *(person + i);
            i += 1;
        }
        *((patient->id) + i)  = '\0';
        sscanf(person + i, "/%d/%d", &(patient->ta), &(patient->ts));
        push_back(deck, patient); // Insert patient
        person = strtok(NULL, sep);
    }
    printf("\n");
    return deck;
}

void print_funcv(void* data){
    Patient* patient = data;
    printf("%s\n", patient->id);
}

int output_queue(Deck* deck){ 
    return print_elements(deck, print_funcv);
}

void free_funcv(void* data){
    Patient* patient = data;
    free(patient->id);
}

int free_deck_p(Deck* deck){
    return free_deck(deck, free_funcv);
}

void clearbuf(){
    char symbol = ' ';
    symbol = getchar();
    while ((symbol != '\n') && (symbol != EOF)) 
    {
        symbol = getchar();
    }
}

int output_by_time(Deck* deck){
    Deck* current_queue = NULL;
    make_deck(&current_queue, 30);
    Patient* cabinet = calloc(1, sizeof(Patient));
    Patient* person = calloc(1, sizeof(Patient));
    read_first(deck, (void*) &person);
    int time = person->ta;
    pop_front(deck, (void*) &cabinet);
    DBG_PRINT("CAB START %s\n", cabinet->id);
    while (empty(deck)){
        read_first(deck, (void*) &person);
        DBG_PRINT("check1 %s\n", person->id);
        while ((person->ta <= time) && empty(deck)){
            pop_front(deck, (void*) &person);
            if (person->id[0] == '*'){ push_front(current_queue, (void*) person); }
            else{ push_back(current_queue, (void*) person); }
            read_first(deck, (void*) &person);
        }
        if (cabinet->ta + cabinet->ts <= time){ // Оutput
            if (!empty(current_queue)) {
                cabinet->ta = person->ta;
                cabinet->ts = 0;
            }
            else{
                pop_front(current_queue, (void*) &cabinet);
                cabinet->ta = time;
            }
        }
        printf("Time: %d\n", time);
        printf("In cabinet: %s \n", cabinet->ts?cabinet->id:"");
        read_first(deck, (void*) &person);
        DBG_PRINT("hhj: %d\n",current_queue->n);
        output_queue(current_queue);
        DBG_PRINT("TA %d\n", person->ta); //
        time = MIN(person->ta, cabinet->ta + cabinet->ts);
        DBG_PRINT("TIME %d\n", time); //
    }
    return 0;
}

char* str_in(char* invite)
{
    char buf[2013] = {0};
    char* res = NULL;
    int len = 0, n;
    printf("%s", invite);
    
    do
    {
        n = scanf("%2012[^\n]", buf);
        if (n < 0)
        {
            return NULL;
        }
        else if (n > 0) //Есть символы
        {
            int chunk_len = strlen(buf); //Длина введенной части
            int str_len = len + chunk_len; //Общая длина строки
            res = realloc(res, str_len + 1); //Изменение длины итоговой строки
            strncpy(res + len, buf, chunk_len); // Копирование из chunk_len в res
            len = str_len;
        }
        else
        {
            scanf("%*c");
        }
    } while (n > 0);
    if (len > 0)
    {
        res[len] = '\0';
    }
    else
    {
        res = calloc(1, sizeof(char));
    }
    return res;
}