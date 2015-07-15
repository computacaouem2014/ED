#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Listas Ligadas Dinamicas e "sentinela"

typedef int keyType;

typedef struct structure {
	keyType key;
	int data;
	struct structure *next;
} node;

typedef struct {
	node *beggin, *aux;
} list;

void initiate(list *li) {
	li -> aux = (node*) malloc(sizeof(node));
	li -> beggin = li -> aux;
}

node *buscaSeqOrd(keyType key, list li, node **ant) {
	node *p = li.beggin;
	li.aux -> key = key;
	while(p -> key < key) {
		*ant = p;
		p = p -> next;
	}
	if(p != li.aux && p -> key == key) return p;
	return NULL;
}

void putIn(keyType key, int data, list *li) {
	node *new = (node*) malloc(sizeof(node)), *ant = NULL;
	if(!buscaSeqOrd(key, *li, &ant)) {
		new -> key = key;
		new -> data = data;
		if(li -> beggin == li -> aux) {
			new -> next = li -> aux;
			li -> beggin = new;
		} else if(key < li -> beggin -> key) {
			new -> next = li -> beggin;
			li -> beggin = new;
		} else {
			new -> next = ant -> next;
			ant -> next = new;
		}
	}
}

node *findElem(int n, list li) {
	node *p = li.beggin;
	int i = 1;
	if(p != li.aux) {
		while(p != li.aux) {
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
		if(!ant) li -> beggin = elem -> next;
		else ant -> next = elem -> next;
	}
	elem -> next = NULL;
	free(elem);
}

void destroyList(list *li) {
	node *atual, *prox;
	atual = li -> beggin;
	while (atual) {
		prox = atual -> next;
		atual -> next = NULL;
		free(atual);
		atual = prox;
	}
	initiate(li);
}


void showList(list li) {
	node *p = li.beggin;
	printf("Beggin -> [");
	while(p != li.aux) {
		printf("%d, %d", p -> key, p -> data);
		p = p -> next;
		if(p != li.aux) printf("], [");
	}
	printf("].\n");
}

void showFirst(list li) {
	if(li.beggin == li.aux) {
		printf("Empty list.\n");
	} else {
		printf("First -> [%d, %d].\n", li.beggin -> key, li.beggin -> data);
	}
}

void showLast(list li) {
	if(li.beggin == li.aux) printf("Empty list.\n");
	else {
		node *p = li.beggin;
		while(p -> next != li.aux) {
			p = p -> next;
		}
		printf("Last -> [%d, %d].\n", p -> key, p -> data);
	}
}

int showSize(list li) {
	if(li.beggin != li.aux) {
		printf("Empty list.\n");
		return 0;
	} else {
		int size = 1;
		node *p = li.beggin;
		while(p -> next != li.aux) {
			p = p -> next;
			size++;
		}
		return size;
	}
}

void clearlist(list *list) {
	node *atual, *next;
	atual = list -> beggin;
	while(atual) {
		next = atual -> next;
		free(atual);
		atual = next;
	}
	list -> beggin = NULL;
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
