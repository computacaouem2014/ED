#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void pretty_print_array(int a[], int first, int last){
	if (first < last) {
		printf("[");
		printf("%d", a[0]);
		for (int i = first + 1; i < last; i++)
			printf(", %d", a[i]);
		printf("]\n");
	} else if (first == last) {
		printf("[%d]\n", a[first]);
	} else {
		printf("[]\n");
	}
}

int partition(int vetor[], int start, int end){
	int random_index = (rand() % (start - end)) + start;
	int pivot = vetor[random_index];
	// printf("Pivot: A[%d] = %d\n", random_index, pivot);
	int i = start - 1;
	int j = end + 1;
	while (1) {
		do {
			i++;
		} while (vetor[i] < pivot);
		do {
			j--;
		} while (vetor[j] > pivot);
		if (i < j) {
			int aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
		} else return j;
	}
}

void quicksort(int vetor[], int first, int last){
	if (vetor != 0) {
		if (first < last) {
			// printf("\n%d~%d;\n", first, last);
			int division = partition(vetor, first, last);
			// printf("%d: ", division);
			// pretty_print_array(vetor, first, last);
			quicksort(vetor, first, division);
			quicksort(vetor, division + 1, last);
		} else {
			// printf("Vetor tamanho 1\n");
		}
	} else {
		printf("Erro! Ponteiro invalido.");
	}
}

int main() {
	srand(time(0));
	int n = 10000;
	int vetor[n];

	for (int i = 0; i < n; i++) vetor[i] = rand() % 100000;

	// pretty_print_array(vetor, 0, n-1);
	// printf("\n");

	quicksort(vetor, 0, n-1);

	// pretty_print_array(vetor, 0, n-1);
	// printf("\n");
	return 0;
}
