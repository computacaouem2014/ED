#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void bubble(int arr[], int size){
	int temp;
	for (int k = size - 1; k >  0; k--){
		for (int j = 0; j < k; j++){
			if (arr[j] < arr[j + 1]){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
		printArray(arr, size);
	}
}

void selection(int arr[], int size){
	for(int i = 0; i < size - 1; i++){
		int min = i;
		for(int j = i + 1; j < size; j++){
			if(arr[min] > arr[j]){
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

void randNum(int arr[], int size, int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = size - 1; k>=0; k--)
		arr[k] = rand() % max + min;
}

int main(){
	int arr[10];
	randNum(arr, 10, 100, 8);
	selection(arr, 10);
	printArray(arr, 10);
}
