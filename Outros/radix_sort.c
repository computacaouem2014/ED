#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct qnode {
	struct qnode * next;
	int data;
} qnode;

typedef struct queue {
	qnode * inicio, * fim;
} queue;

int queue_is_empty(queue * q){
	return q->inicio == 0 && q->fim == 0;
}

int queue_is_initialized(queue * q){
	return q != 0;
}

void queue_initialize(queue ** q){
	if (*q != 0) {
		printf("Erro! A fila ja esta inicializada.\n");
	} else {
		*q = (queue *) malloc(sizeof(queue));
		(*q)->inicio = (*q)->fim = 0;
	}
}

void queue_destroy(queue ** q){
	if (*q != 0) {
		qnode * aux = 0;
		while ((*q)->inicio != 0) {
			aux = (*q)->inicio;
			(*q)->inicio = (*q)->inicio->next;
			free(aux);
			aux = 0;
		}
		aux = 0;
		free(*q);
		*q = 0;
	} else {
		printf("Erro! Impossivel destruir fila inexistente.\n");
	}
}

void queue_enqueue(queue * q, int data){
	if (queue_is_initialized(q)) {
		if (queue_is_empty(q)) {
			q->inicio = q->fim = (qnode *) malloc(sizeof(qnode));
			q->inicio->data = data;
			q->inicio->next = 0;
		} else {
			q->fim->next = (qnode *) malloc(sizeof(qnode));
			q->fim = q->fim->next;
			q->fim->data = data;
			q->fim->next = 0;
		}
	} else {
		printf("Erro! A fila nao foi inicializada.\n");
	}
}

void queue_dequeue(queue * q, int * data){
	if (queue_is_initialized(q)) {
		if (queue_is_empty(q)) {
			printf("Erro! Impossivel remover de fila vazia.\n");
		} else {
			*data = q->inicio->data;
			qnode * aux = q->inicio;
			q->inicio = q->inicio->next;
			if (q->inicio == 0) {
				q->fim = 0;
			}
			free(aux);
		}
	} else {
		printf("Erro! A fila nao foi inicializada.\n");
	}
}

void print_int_binary(int n){
	if (n >= 1) {
		print_int_binary(n / 2);
		printf("%d", n & 1);
	} else printf("\n");
}

int get_bit_at(char from, char which_bit){
	if (which_bit > 0 && which_bit <= 8) {
		return (from & (1 << (which_bit - 1)));
	} else {
		return 0;
	}
}

void pretty_print_queue(queue * q){
	if (q == 0 || (q->inicio == 0 && q->fim == 0)) {
		printf("[]\n");
	} else if (q->inicio != 0 && q->fim != 0 && q->inicio == q->fim) {
		printf("[%d]\n", q->inicio->data);
	} else {
		qnode * current = q->inicio->next;
		printf("[");
		printf("%d", q->inicio->data);
		do {
			printf(", %d", current->data);
			current = current->next;
		} while (current != 0);
		printf("]\n");
	}
}

void pretty_print_array(int a[], int size){
	if (size > 1) {
		printf("[");
		printf("%d", a[0]);
		for (int i = 1; i < size; i++)
			printf(", %d", a[i]);
		printf("]\n");
	} else if (size == 1) {
		printf("[%d]\n", a[0]);
	} else {
		printf("[]\n");
	}
}

int power(int base, int expoente){
	if (expoente < 1) return 1;
	else return base * power(base, expoente - 1);
}

void radix_sort(int vetor[], int n){
	int base = 2;
	queue tabela[base];
	for (int i = 0; i < base; i++) {
		tabela[i].inicio = 0;
		tabela[i].fim = 0;
	}
	int maior = vetor[0];
	for (int i = 1; i < n; i++) {
		if (vetor[i] > maior) maior = vetor[i];
	}
	printf("Maior número: %d\n", maior);
	int digitos = 0;
	while (maior >= 1) {
		digitos++;
		maior = maior / base;
	}
	printf("Quantidade de digitos na base %d: %d\n", base, digitos);
	for (int i = 0; i < digitos; i++) {
		printf("\nDigito no.%d\n", i);
		// printf("\tTabela:\n");
		int j;
		for (j = 0; j < n; j++) {
			int digito = (vetor[j] / power(base, i)) % base;
			queue_enqueue(&(tabela[digito]), vetor[j]);
		}
		// for (j = 0; j < base; j++) {
		// 	printf("\t\t%d: ", j);
		// 	pretty_print_queue(&(tabela[j]));
		// }
		int k = 0;
		// printf("\n\tRecompondo Vetor:\n\t\t");
		for (j = 0; j < n; j++) {
			while (queue_is_empty(&(tabela[k]))) k++;
			queue_dequeue(&(tabela[k]), &(vetor[j]));
		}
		// pretty_print_array(vetor, n);
		printf("\n");
	}
}

int main() {
	srand(time(0));
	int n = 1000;
	int vetor[n];

	for (int i = 0; i < n; i++) vetor[i] = rand() % 5000;

	printf("\t\t");
	pretty_print_array(vetor, n);
	printf("\n");

	radix_sort(vetor, n);

	pretty_print_array(vetor, n);
	printf("\n");
	return 0;
}
