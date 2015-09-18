#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct ptreenode {
	struct ptreenode * esquerda, * direita;
	char valor;
} ptreenode;

typedef struct qnode {
	struct qnode * next;
	ptreenode * data;
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

void queue_enqueue(queue * q, ptreenode * data){
	if (queue_is_initialized(q)) {
		if (queue_is_empty(q)) {
			q->inicio = q->fim = (qnode *) malloc(sizeof(qnode));
			q->inicio->data = data;
			q->inicio->next = 0;
		} else {
			q->fim->next = (qnode *) malloc(sizeof(qnode));
			q->fim->next->data = data;
			q->fim = q->fim->next;
		}
	} else {
		printf("Erro! A fila nao foi inicializada.\n");
	}
}

void queue_dequeue(queue * q, ptreenode ** data){
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

int get_bit_at(char from, char which_bit){
	if (which_bit > 0 && which_bit <= 8) {
		return (from & (1 << (which_bit - 1)));
	} else {
		return 0;
	}
}

int ptree_is_empty(ptreenode *root){
	return root == 0;
}

char first_different_bit(char a, char b){
	unsigned char xor = (unsigned char) (a ^ b);
	xor = xor | xor >> 1;
	xor = xor | xor >> 2;
	xor = xor | xor >> 3;
	xor = xor | xor >> 4;
	xor = xor | xor >> 5;
	xor = xor | xor >> 6;
	xor = xor | xor >> 7;
	return xor & (~xor >> 1);
}

void ptree_insert(ptreenode **node, char valor){
	if (ptree_is_empty(*node)) {
		printf("Arvore Vazia\nCriando Node Externo.\n");
		*node = (ptreenode *) malloc(sizeof(ptreenode));
		*node = (ptreenode*) malloc(sizeof(ptreenode));
		(*node)->direita = (*node)->esquerda = 0;
		(*node)->valor = valor;
		printf("Elemento \'%c\' adicionado a arvore.\n", valor);
	} else if ((*node)->esquerda == 0 && (*node)->direita == 0) {
		printf("Encontrado Node Externo.\n");
		if (valor == (*node)->valor) {
			printf("Erro! O elemento \'%c\' ja esta na arvore.\n", valor);
		} else {
			(*node)->direita = (ptreenode *) malloc(sizeof(ptreenode));
			(*node)->esquerda = (ptreenode *) malloc(sizeof(ptreenode));
			(*node)->direita->direita = 0;
			(*node)->direita->esquerda = 0;
			(*node)->esquerda->direita = 0;
			(*node)->esquerda->esquerda = 0;
			char diff_bit = (char) log2(first_different_bit(valor, (*node)->valor)) + 1;
			if (get_bit_at(valor, diff_bit) == 0) {
				(*node)->direita->valor = (*node)->valor;
				(*node)->esquerda->valor = valor;
			} else {
				(*node)->esquerda->valor = (*node)->valor;
				(*node)->direita->valor = valor;
			}
			(*node)->valor = diff_bit;
			printf("Elemento \'%c\' adicionado a arvore.\n", valor);
		}
	} else if ((*node)->esquerda != 0 && (*node)->direita != 0) {
		printf("Passando por Node Interno.\n");
		if (get_bit_at(valor, (*node)->valor) == 0) {
			// ESQUERDA
			ptree_insert(&((*node)->esquerda), valor);
			if ((*node)->esquerda->esquerda != 0 && (*node)->esquerda->direita != 0) {
				if ((*node)->esquerda->valor > (*node)->valor) {
					ptreenode *aux = *node;
					*node = aux->esquerda;
					aux->esquerda = (*node)->esquerda;
					(*node)->esquerda = aux;
				}
			}
		} else {
			// DIREITA
			ptree_insert(&((*node)->direita), valor);
			if ((*node)->direita->esquerda != 0 && (*node)->direita->direita != 0) {
				if ((*node)->direita->valor > (*node)->valor) {
					ptreenode *aux = *node;
					*node = aux->direita;
					aux->direita = (*node)->direita;
					(*node)->direita = aux;
				}
			}
		}
	} else {
		printf("Erro! Estrutura nao e uma arvore patricia.\n");
	}
}

void ptree_remove(ptreenode ** node, char valor){
	if (!ptree_is_empty(*node)) {
		if ((*node)->direita != 0 && (*node)->esquerda != 0) {
			if (get_bit_at(valor, (*node)->valor) == 0) {
				ptree_remove(&((*node)->esquerda), valor);
				if ((*node)->esquerda == 0) {
					ptreenode * aux = *node;
					*node = (*node)->direita;
					free(aux);
				}
			} else {
				ptree_remove(&((*node)->direita), valor);
				if ((*node)->direita == 0) {
					ptreenode * aux = *node;
					*node = (*node)->esquerda;
					free(aux);
				}
			}
		} else if ((*node)->direita == 0 && (*node)->esquerda == 0) {
			if ((*node)->valor != valor) {
				printf("Erro! Impossivel remover elemento (\'%c\') inexistente da arvore.\n", valor);
			} else {
				printf("Elemento \'%c\' removido.\n", valor);
				ptreenode * aux = *node;
				*node = 0;
				free(aux);
			}
		} else {
			printf("Erro! Estrutura nao e uma arvore patricia.\n");
		}
	} else {
		printf("Erro! Impossivel remover de arvore vazia.\n");
	}
}

void ptree_search(ptreenode ** node, char valor){
	if (!ptree_is_empty(*node)) {
		if ((*node)->direita != 0 && (*node)->esquerda != 0) {
			if (get_bit_at(valor, (*node)->valor) == 0) {
				ptree_search(&((*node)->esquerda), valor);
			} else {
				ptree_search(&((*node)->direita), valor);
			}
		} else if ((*node)->direita == 0 && (*node)->esquerda == 0) {
			if ((*node)->valor != valor) {
				printf("Buscando(\'%c\')\nO elemento \'%c\' nao esta na arvore.\n", valor, valor);
			} else {
				printf("Buscando(\'%c\')\nO elemento \'%c\' esta na arvore.\n", valor, valor);
			}
		} else {
			printf("Erro! Estrutura nao e uma arvore patricia.\n");
		}
	} else {
		printf("Erro! Impossivel remover de arvore vazia.\n");
	}
}

void ptree_print_in_order(ptreenode * node){
	if (node != 0) {
		ptree_print_in_order(node->esquerda);
		if (node->esquerda != 0 && node->direita != 0) {
			printf("%d", node->valor);
		} else if (node->esquerda == 0 && node->direita == 0) {
			printf("%c", node->valor);
		}
		ptree_print_in_order(node->direita);
	}
}

void ptree_print_bfs(ptreenode * node){
	if (!ptree_is_empty(node)) {
		queue * q = 0;
		queue_initialize(&q);
		queue_enqueue(q, node);
		int count = 1;
		int next_count = 0;
		ptreenode * current_node = 0;
		while (!queue_is_empty(q)) {
			queue_dequeue(q, &current_node);
			if (current_node->esquerda != 0 && current_node->direita != 0) {
				printf("%d", current_node->valor);
				queue_enqueue(q, current_node->esquerda);
				queue_enqueue(q, current_node->direita);
				next_count += 2;
			} else if (current_node->esquerda == 0 && current_node->direita == 0) {
				printf("%c", current_node->valor);
			}
			count--;
			if (count <= 0) {
				printf("\n");
				count = next_count;
				next_count = 0;
			}
		}
		queue_destroy(&q);
		current_node = 0;
	}
}

int main() {
	ptreenode * root = 0;
	ptree_insert(&root, 'D');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_insert(&root, 'B');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_insert(&root, 'C');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_insert(&root, 'C');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_insert(&root, 'A');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_remove(&root, 'A');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_search(&root, 'C');
	printf("\n");

	ptree_remove(&root, 'C');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_remove(&root, 'C');
	printf("Arvore no passeio in-order: ");
	ptree_print_in_order(root);
	printf("\n\n");

	ptree_search(&root, 'C');
	printf("\n");

	//ptree_print_bfs(root);
	return 0;
}
