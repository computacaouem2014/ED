#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Listas Ligadas Dinamicas

typedef int keyType;

typedef struct structure {
	keyType key;
	int data;
	struct structure *next;
} node;

typedef struct {
	node *beggin;
} list;

void initiate(list *li) {
	li -> beggin = NULL;
}

bool buscaSeqOrd(keyType key, list li, node* *ant) {
	node *p = li.beggin;
	while(p) {
		if(p -> key > key) return false;
		else if(p -> key == key) return true;
		else {
			*ant = p;
			p = p -> next;
		}
	}
	return false;
}

void putIn(keyType key, int data, list *li) {
	if(!buscaSeqOrd(key, *li, NULL)) {
		node *new = (node*) malloc(sizeof(node)), *n, *last;
		new -> key = key;
		new -> data = data;
		if(!li -> beggin) {
			new -> next = NULL;
			li -> beggin = new;
		} else if(key < li -> beggin -> key) {
			new -> next = li -> beggin;
			li -> beggin = new;
		} else {
			n = li -> beggin;
			while(n -> next) {
				if(n -> key > key) break;
				last = n;
				n = n -> next;
			}
			new -> next = last -> next;
			last = new;
		}
	}
}


void showList(list li) {
	node *p = li.beggin;
	printf("Beggin -> [");
	while(p) {
		printf("%d, %d", p -> key, p -> data);
		p = p -> next;
		if(p) printf("], [");
	}
	printf("].\n");
}

void showFirst(list li) {
	if(!li.beggin) {
		printf("Empty list.\n");
	} else {
		printf("First -> [%d, %d].\n", li.beggin -> key, li.beggin -> data);
	}
}

void showLast(list li) {
	if(!li.beggin) printf("Empty list.\n");
	else {
		node *p = li.beggin;
		while(p -> next) {
			p = p -> next;
		}
		printf("Last -> [%d, %d].\n", p -> key, p -> data);
	}
}

int showSize(list li) {
	if(!li.beggin) {
		printf("Empty list.\n");
		return 0;
	} else {
		int size = 1;
		node *p = li.beggin;
		while(p -> next) {
			p = p -> next;
			size++;
		}
		return size;
	}
}

void putOut(list *list) {
	node *elem;
	elem = list -> beggin;
	if(!elem) {
		printf("Empty list.\n");
	} else {
		list -> beggin = elem -> next;
		free(elem);
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
	return 0;
}
