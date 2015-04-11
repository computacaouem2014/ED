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

void randNum(list *arr, int num, int max, int min) {
	srand(time(NULL));
	max -= min;
	for (int k = num - 1; k >= 0; k--)
		listEnd(arr, rand() % max + min);
}

void insertion(list *lista) {
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

int listSearch(keyType b, list lista) {
	for (int i = 0; i < lista.size; i++) {
		if (b == lista.a[i].key) return i;
	} return 0;
}

int binSearchRecursive(keyType b, list lista, int mid) {
	if (mid > 2) {
		if (b == lista.a[mid].key) return mid;
		else if (b > lista.a[mid].key) return binSearchRecursive(b, lista, (mid + lista.size) / 2);
		else return binSearchRecursive(b, lista, mid / 2);
	}
	return 0;
}
	

int binSearch(keyType b, list lista) {
	int inf = 0, sup = lista.size - 1, mid = (inf + sup) / 2;
	while (inf <= sup) {
		if (b == lista.a[mid].key) {
			return mid;
		} else if (b > lista.a[mid].key) {
				inf = mid + 1, sup = lista.size - 1, mid = (inf + sup) / 2;
			} else {
				inf = 0, sup = mid - 1, mid = (inf + sup) / 2;
			}
		}
	return 0;	
}

void listInsert(list *lista, keyType b, int j) {
	if (lista -> size >= MAX) {
		printf("Vetor cheio\n");
	} else if (j < 0 || j > lista -> size) {
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
		if (i < lista -> size) {
			lista -> size++;
			for (int j = lista -> size - 1; j > i; j--) {
				lista -> a[j].key = lista -> a[j - 1].key;
			}
			lista -> a[i].key = b;
		}
	}
}

void showList(list lista) {
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

void copyListR(list lista1, list *lista2) {
	for (int i = 0; i < lista1.size; i++) {
		if (!listSearch(lista1.a[i].key, *lista2)) {
			listEnd(lista2, lista1.a[i].key);
		}
	}
}

void listDel(keyType b, list *lista) {
	if (listSearch(b, *lista) < 0) printf("\nO Elemento nao esta na lista.\n");
	else {
		int j = listSearch(b, *lista);
		for (int i = j; i < lista -> size; i++) {
			lista -> a[i].key = lista -> a[i + 1].key;
		}
		lista -> size--;
	}
}


int main(){
	list staticList1, staticList2;
	srand(time(NULL));
	int random = rand() % 200 - 100, scan, del;
	listStart(&staticList1);
	listStart(&staticList2);
	randNum(&staticList1, 30, 100, 10);
	printf("%d | %d\n", staticList1.size, staticList2.size);
	copyListR(staticList1, &staticList2);
	insertion(&staticList2);
	printf("%d | %d\n", staticList1.size, staticList2.size);
	showList(staticList1);
	showList(staticList2);
	listInsertOrd(&staticList2, random);
	printf("Digite o elemento que deseja procurar: ");
	scanf("%d", &scan);
	printf("O elemento %sencontrado.%d\n ", binSearchRecursive(scan, staticList2, staticList2.size/2) == 0 ? "nao foi " : "foi ", binSearchRecursive(scan, staticList2, staticList2.size/2));
	printf("Digite o elemento que deseja deletar: ");
	scanf("%d", &del);
	listDel(del, &staticList2);
	showList(staticList2);
	return 0;
}
