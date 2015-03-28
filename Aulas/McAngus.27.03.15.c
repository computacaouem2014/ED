#include <stdio.h>
#include <stdlib.h>
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
	}
	else printf("\n[]\n");
}

void randNum(int arr[], int size, int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = size - 1; k >= 0; k--)
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

int main(){
	int n = 10, arr[n];
	randNum(arr, n, 100, -100);
	printArray(arr, n);
	insertion(arr, n);
	printArray(arr, n);
	return 0;
}			
