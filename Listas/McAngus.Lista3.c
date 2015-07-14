#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

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
		printf("Vetor cheio. %d\n", lista -> size);
	} else {
		lista -> a[lista -> size].key = b;
		lista -> size++;
	}
}
int binSearch(keyType b, list lista) {
	int first = 0, last = lista.size - 1, mid = (first+last)/2;
	while (first <= last) {
		if (lista.a[mid].key < b)
			first = mid + 1;    
		else if (lista.a[mid].key == b) {
			return mid;
		} else last = mid - 1;
	mid = (first + last)/2;
	}
	return -1;
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

void randList(list *arr, int num, int max, int min) {
	max -= min;
	for (int k = num - 1; k >= 0; k--) {
		int add = rand() % max + min;
		listEnd(arr, add);
	}
}

void listStart(list *lista) {
	lista -> size = 0;
	printf("\\\\List initialized//\n");
}

void showList(list lista) {
	for (int i = 0; i < lista.size; i++) {
		printf("| %2d ", lista.a[i].key);
	} printf("|\n");
}

void printArray(int a[], int size) {
	if (size > 1) {
		printf("\n[");
		printf("%d", a[0]);
		for (int i = 1; i < size; i++)
			printf(", %d", a[i]);
		printf("]\n");
	} else if (size == 1){
		printf("\n[%d]\n", a[0]);
	} else printf("\n[]\n");
}

void randNum(int *arr, int size, int max, int min){
	max -= min;
	for (int k = size - 1; k>=0; k--) {
		arr[k] = rand() % max + min;
	}
}

void insertionFirst(list *lista, list *lista2) {
	if (lista -> a[0].key > lista2 -> a[0].key) {
		for (int i = 0; i < lista -> size; i++) {
			int aux = lista -> a[i].key;
			lista -> a[i].key = lista2 -> a[i].key;
			lista2 -> a[i].key = aux;
		}
	}
}

void repRemove(list *lista) {	
	insertion(lista);
	for (int j = 0; j < lista -> size - 1; j++) {
		for (int k = j + 1; k < lista -> size; k++) {
			if (lista -> a[j].key == lista -> a[k].key) {
				lista -> a[j].key++;
			}
		insertion(lista);
		}
	}
}

//ex1
void insertionSort(int start, int *arr, int size){
	if (start < size){
		int j = start - 1, change = arr[start];
		while (change < arr[j] && j >= 0) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = change;
		insertionSort(++start, arr, size);
	}
}

//ex2
void selectionSort(int *arr, int size){
	for(int i = 0; i < size - 1; i++){
		int min = i;
		for(int j = i + 1; j < size; j++){
			if(arr[min] < arr[j]){
				min = j;
			}
		}
		if (min != i){
			int aux = arr[min];
			arr[min] = arr[i];
			arr[i] = aux;
		}
	}
}

//ex3
void repSort(int *arr, int size){
	int n[size];
	insertionSort(1, arr, size);
	for (int i = 0; i < size; i++) n[i] = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (arr[i] == arr[j]) {
				n[i]++;
			}
		}
	}
	for(int i = 1; i < size; i++){
		int j = i - 1, change = arr[i];
		while(n[i] >= n[j] && j >= 0){
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = change;
	}
}

//ex4
void splitVec(int in[], int sizeIn, int *outPos, int *outNeg, int *sizePos, int *sizeNeg) {
	for (int i = 0; i < sizeIn; i++) {
		if (in[i] >= 0) outPos[(*sizePos)++] = in[i];
		else outNeg[(*sizeNeg)++] = in[i];
	}
}

//ex5
int bingo() {
	srand(time(NULL));
	int n, resul[5];
	printf("Digite o numero de cartelas que sera gerado: ");
	scanf("%d", &n);
	list cartelas[n];
	for (int i = 0; i < n; i++) {
		listStart(&cartelas[i]);
		randList(&cartelas[i], 10, 60, 0);
		repRemove(&cartelas[i]);
	}
	for (int i = 0; i < n; i++ ) {
		for (int j = i + 1; j < n; j++){
			insertionFirst(&cartelas[i], &cartelas[j]);
		}
		printf("%2d ", i + 1);
		showList(cartelas[i]);
	}
	randNum(resul, 5, 60, 0);
	insertionSort(1, resul, 5);
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (resul[i] == resul[j]) resul[j]++;
		}
		insertionSort(1, resul, 5);
	}
	printArray(resul, 5);
	for (int i = 0; i < n; i++) {
		int count = 0;
		while (binSearch(resul[count], cartelas[i]) != -1 && count < 5) count++;
		printf("A cartela %2d%s possui todos os numeros.\n", i + 1, count == 5 ? "" : " nao");
	}
	return 0;
}

int main() {
	bingo();
	return 0;
}

