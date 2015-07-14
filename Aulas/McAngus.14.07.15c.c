#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Lista Circular com no "cabeca"

typedef int keyType;

typedef struct structure {
	keyType key;
	int data;
	struct structure *next;
} node;

typedef struct {
	node *head;
} list;

void initiate(list *li) {
	li -> head = (node*) malloc(sizeof(node));
	li -> head -> next = li -> head;
}

node *buscaSeqOrd(keyType key, list li, node **ant) {
	node *p = li.head -> next;
	ant = NULL;
	li.head -> next -> key = key;
	while(p -> key < key) {
		*ant = p;
		p = p -> next;
	}
	if(p != li.head && p -> key == key) return p;
	return NULL;
}

void putIn(keyType key, int data, list *li) {
	node *new = (node*) malloc(sizeof(node)), *ant = NULL;
	if(!buscaSeqOrd(key, *li, &ant)) {
		new -> key = key;
		new -> data = data;
		if(li -> head -> next == li -> head) {
			new -> next = li -> head;
			li -> head -> next = new;
		} else if(key < li -> head -> next -> key) {
			new -> next = li -> head -> next;
			li -> head -> next = new;
		} else {
			new -> next = ant;
			ant = new;
		}
	}
}

node *findElem(int n, list li) {
	node *p = li.head -> next;
	int i = 1;
	if(p != li.head) {
		while(p != li.head) {
			p = p -> next;
			i++;
			if(i < n) return p;
		}
	}
	return NULL;
}

void putOut(keyType key, list *li) {
	node *ant = NULL, *elem = buscaSeqOrd(key, *li, &ant);
	if(elem) {
		if(!ant) li -> head -> next = elem -> next;
		else ant -> next = elem -> next;
	}
	elem -> next = NULL;
	free(elem);
}

void destroyList(list *li) {
	node *atual, *prox;
	atual = li -> head -> next;
	while (atual) {
		prox = atual -> next;
		atual -> next = NULL;
		free(atual);
		atual = prox;
	}
	initiate(li);
}


void showList(list li) {
	node *p = li.head -> next;
	printf("Beggin -> [");
	while(p != li.head) {
		printf("%d, %d", p -> key, p -> data);
		p = p -> next;
		if(p != li.head) printf("], [");
	}
	printf("].\n");
}

void showFirst(list li) {
	if(li.head -> next == li.head) {
		printf("Empty list.\n");
	} else {
		printf("First -> [%d, %d].\n", li.head -> next -> key, li.head -> next -> data);
	}
}

void showLast(list li) {
	if(li.head -> next == li.head) printf("Empty list.\n");
	else {
		node *p = li.head -> next;
		while(p -> next != li.head) {
			p = p -> next;
		}
		printf("Last -> [%d, %d].\n", p -> key, p -> data);
	}
}

int showSize(list li) {
	if(li.head -> next != li.head) {
		printf("Empty list.\n");
		return 0;
	} else {
		int size = 1;
		node *p = li.head -> next;
		while(p -> next != li.head) {
			p = p -> next;
			size++;
		}
		return size;
	}
}

void clearlist(list *li) {
	node *atual, *next;
	atual = li -> head -> next;
	while(atual) {
		next = atual -> next;
		free(atual);
		atual = next;
	}
	initiate(li);
}

int main() {
	list li;
	initiate(&li);
	int key, number;
	while(1) {
		printf("Digite uma chave (0 para sair): "); scanf("%d", &key);
		if(!key) break;
		printf("Digite um numero: "); scanf("%d", &number);
		if(key) putIn(key, number, &li);
	}
	showList(li);
	destroyList(&li);
	showList(li);
	return 0;
}
