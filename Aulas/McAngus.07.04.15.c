#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef int keyType;

typedef struct {
	keyType key;
} reg;

typedef struct {
	reg a[MAX];
	int size;
} list;

void listEnd(list *lista, keyType b) {
	if (lista -> size >= MAX) {
		printf("Vetor cheio\n");
	} else {
		lista -> a[lista -> size].key = b;
		lista -> size++;
	}
}

void randNum(list *arr, int num, int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = num - 1; k >= 0; k--)
		listEnd(arr, rand() % max + min);
}

void insertion(list *lista){
	for(int i = 1; i < lista -> size; i++){
		int j = i - 1, change = lista -> a[i].key;
		while(change < lista -> a[j].key && j >= 0){
			lista -> a[j + 1].key = lista -> a[j].key;
			j--;
		}
		lista -> a[j + 1].key = change;
	}
}

void listStart(list *lista) {
	lista -> size = 0;
	printf("\t\t\t\t\t\t\t\t\t\\\\List initialized//\n\t\t\t\t\t\t\t\t\t \\\\\\\\\\\\\\\\\\/////////\n");
}

int listSize(list lista) {
	return lista.size;
}


void listInsert(list *lista, keyType b, int j) {
	if (lista -> size >= MAX) {
		printf("Vetor cheio\n");
	} else if (j < 0 || j > lista -> size){
		printf("Valor incorreto.");
	} else if (!j) {
		lista -> a[j].key = b;
		lista -> size++;
	} else if (j) {
		lista -> a[j].key = b;
		lista -> size++;
	}
}

void listInsertOrd(list *lista, keyType b) {
	if (lista -> size >= MAX){
		printf("Lista Cheia.\n");
	} else {
		int i;
		for (i = 0; i < lista -> size; i++) {
			if (b < lista -> a[i].key) break;
		}
		if (i < lista -> size){
			lista -> size++;
			for (int j = lista -> size - 1; j > i; j--){
				lista -> a[j].key = lista -> a[j - 1].key;
			}
			lista -> a[i].key = b;
		}
	}
}

void showList(list lista){
	for (int i = 0; i < lista.size; i++) {
		printf("| %d ", lista.a[i].key);
	} printf("|\n");
}

void invertList(list lista1, list *lista2) {
	for (int i = 0; i < lista1.size; i++) {
		listInsert(lista2, lista1.a[i].key, 0);
	}
}

void copyList(list lista1, list *lista2) {
	for (int i = 0; i < lista1.size; i++) {
		listInsert(lista2, lista1.a[i].key, i);
	}
}

int main(){
	list staticList1, staticList2;
	srand(time(NULL));
	int random = rand() % 200 - 100;
	listStart(&staticList1);
	listStart(&staticList2);
	randNum(&staticList1, 30, 100, 10);
	printf("%d | %d\n", listSize(staticList1), listSize(staticList2));
	copyList(staticList1, &staticList2);
	insertion(&staticList2);
	printf("%d | %d\n", listSize(staticList1), listSize(staticList2));
	showList(staticList1);
	showList(staticList2);
	listInsertOrd(&staticList2, random);
	showList(staticList2);
	return 0;
}
