#include <stdio.h>
#include <stdlib.h>
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
				int aux = lista -> a[j].key;
				lista -> a[j].key = lista -> a[j - 1].key;
			}
			lista -> a[i].key = b;
		}
	}
}

void listStart(list *lista) {
	lista -> size = 0;
	printf("\t\t\t\t\t\t\t\t\t\\\\List initialized//\n\t\t\t\t\t\t\t\t\t \\\\\\\\\\\\\\\\\\/////////\n");
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

void randNum(int arr[], int size, int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = size - 1; k>=0; k--)
		arr[k] = rand() % max + min;
}

void insertion(int *arr, int size){
	for(int i = 1; i < size; i++){
		int j = i - 1, change = arr[i];
		while(change < arr[j] && j >= 0){
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = change;
	}
}

//ex1
void insertionSort(int start, int *arr, int size){
	if (start < size){
		int j = start - 1, change = arr[start];
		while (change < arr[j] && j > 0) {
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
//coming soon.

int main(){
	int arr[10], arr2[10], arr3[10], a = 0, b = 0;
	randNum(arr, 10, 100, -30);
	printArray(arr, 10);
	selectionSort(arr, 10);
//	repSort(arr, 10);
	splitVec(arr, 10, arr2, arr3, &a, &b);
	printArray(arr, 10);
	printArray(arr2, a);
	printArray(arr3, b);
	return 0;
}
