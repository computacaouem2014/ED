/*
 * @author theosirian
 * @date 09-01-2015
 * Compile with 'gcc -o %output_name% %this_file_name% -Wall -lm -std=c99'
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

typedef struct trigo {
    size_t length, capacity;
    int *data;
} trigo;

size_t next_power_2(int n){
    return (size_t) pow(2, ceil(log(n)/log(2)));
}

void heap_initialize_cap(trigo **t, int initial_capacity){
    (*t) = (trigo*) malloc(sizeof(trigo));
    (*t)->length = 0;
    (*t)->capacity = next_power_2(initial_capacity);
    //t->data = (int*) calloc((*t)->capacity, sizeof(int));
    (*t)->data = (int*) malloc((*t)->capacity * sizeof(int));
    printf("Initializing Heap with Initial Capacity of %d...\n", (*t)->capacity);
}

void heap_initialize(trigo **t){
    heap_initialize_cap(t, 2);
}

bool heap_is_empty(trigo *t){
    return t == 0 || t->length == 0;
}

bool heap_is_full(trigo *t){
    return t != 0 && t->length == t->capacity;
}

void heap_resize(trigo *t){
    t->capacity = next_power_2(t->capacity + 1);
    t->data = (int *) realloc(t->data, t->capacity * sizeof(int));
    printf("Resizing Heap to Capacity of %d...\n", t->capacity);
}

void heap_ascend(trigo *t, int index){
    if (index > 0){
        int parent = floor((index - 1) / 2);
        if (t->data[index] > t->data[parent]){
            int aux = t->data[index];
            t->data[index] = t->data[parent];
            t->data[parent] = aux;
            heap_ascend(t, parent);
        }
    }
}

void heap_descend(trigo *t, int index){
    if (index < t->length / 2){
        int child = (2 * index) + 1;
        if (child + 1 < t->length) {
            if (t->data[child] < t->data[child + 1]) {
                child++;
            }
        }
        if (t->data[index] < t->data[child]){
            int aux = t->data[index];
            t->data[index] = t->data[child];
            t->data[child] = aux;
            heap_descend(t, child);
        }
    }
}

void heap_push(trigo *t, int elem){
    if (heap_is_full(t)){
        heap_resize(t);
    }
    t->data[t->length] = elem;
    heap_ascend(t, t->length);
    t->length++;
    printf("Pushing %d to Heap...\n", elem);
}

void heap_pop(trigo *t, int *elem){
    if (heap_is_empty(t)){
        elem = 0;
    } else {
        (*elem) = t->data[0];
        t->data[0] = t->data[t->length - 1];
        t->length--;
        heap_descend(t, 0);
        printf("Poping %d from Heap...\n", *elem);
    }
}

void heap_select(trigo *t, int *elem){
    if (heap_is_empty(t)){
        elem = 0;
    } else {
        (*elem) = t->data[0];
    }
}

int main(){
    srand((unsigned int) time(0));
    trigo *t = 0;
    heap_initialize(&t);
    for (int i = 0; i < 17; i++) {
        heap_push(t, rand() % 100);
    }
    for (int i = 0, l = t->length; i < l; i++){
        int k;
        heap_pop(t, &k);
    }
    return 0;
}
