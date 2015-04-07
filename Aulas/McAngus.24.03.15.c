#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define n 7

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

void swap(int *arr, int a, int b){
	int aux = arr[a];
	arr[a] = arr[b];
	arr[b] = aux;
}

void selecDec(int arr[], int size){
	for(int i = 0; i < size - 1; i++){
		int max = i;
		for(int j = i + 1; j < size; j++){
			if(arr[max] < arr[j]){
				max = j;
			}
		}
		if (max != i) swap(arr, max, i);
	}
}

void selecCre(int arr[], int size){
	for(int i = 0; i < size - 1; i++){
		int max = i;
		for(int j = i + 1; j < size; j++){
			if(arr[max] > arr[j]){
				max = j;
			}
		}
		if (max != i) swap(arr, max, i);
	}
}

void randNum(int arr[], int size, int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = size - 1; k>=0; k--)
		arr[k] = rand() % max + min;
}

void separate(int *arrA, int *posi, int *nega, int size, int *pos, int *neg){
	for(int i = 0; i < size; i++){
		if(arrA[i] >= 0){
			posi[*pos] = arrA[i];
			(*pos)++;
		} else {
			nega[*neg] = arrA[i];
			(*neg)++;
		}
	}
}

void ex1(){
	int arr[n];
	/* for(int i = 0; i < n; i++){
		printf("Digite o %d numero: ", i + 1); scanf("%d", &arr[i]);
	} */
	randNum(arr, n, 100, 0);
	printArray(arr, n);
	selecDec(arr, n);
	printArray(arr, n);
}

void ex2(){
	int arrA[n], arrP[n], arrN[n], nSize = 0, pSize = 0;
	randNum(arrA, n, 100, -100);
	printArray(arrA, n);
	separate(arrA, arrP, arrN, n, &pSize, &nSize);
	selecCre(arrP, pSize);
	selecDec(arrN, nSize);
	printArray(arrP, pSize);
	printArray(arrN, nSize);
}

int main(){
	ex2();
	return 0;
}
