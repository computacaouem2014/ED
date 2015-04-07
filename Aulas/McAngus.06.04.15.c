#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define TRUE 1
#define FALSE 0

typedef int keyType;

typedef struct {
	keyType key;
} reg;

typedef struct {
	reg a[MAX];
	int size;
} list;

void listStart(list *lista){
	lista -> size = 0;
	printf("\\\\List initialized//\n");
}

int listSize(list lista){
	return lista.size;
}

void listInsert(list *lista, keyType b, int j){
	if (lista -> size >= MAX) {
		printf("Vetor cheio\n");
	} else if (j > 0 && lista -> size > j){}
		else if (j != lista -> size) {
			for (int i = j; i < lista -> size; i++) lista -> a[i + 1].key = lista -> a[i].key;
			lista -> a[j].key = b;
			lista -> size++;
		} else {
			lista -> a[j].key = b;
			lista -> size++;
		}
}

void showList(list lista){
	for (int i = 0; i < lista.size; i++){
		printf("| %d ", lista.a[i].key);
	} printf("|\n");
}

void invertList(list lista1, list *lista2){
	for (int i = 0; i < lista1.size; i++){
		listInsert(lista2, lista1.a[i].key, 0);
	}
}

int main(){
	list staticList, staticListInverted;
	listStart(&staticList);
	listStart(&staticListInverted);
	printf("%d\n", listSize(staticList));
	listInsert(&staticList, 20, 0);
	printf("%d\n", listSize(staticList));
	listInsert(&staticList, 30, 1);
	printf("%d\n", listSize(staticList));
	invertList(staticList, &staticListInverted);
	showList(staticList);
	showList(staticListInverted);
	return 0;
}
