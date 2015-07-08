#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Fila dinamica

typedef int keyType;

typedef struct structure {
	keyType key;
	int data;
	struct structure *next;
} node;

typedef struct {
	node *beggin, *end;
} line;

void initiate(line *li) {
	li -> beggin = NULL;
	li -> end = NULL;
	printf("\t\tFila inicializada.\n");
}

void putIn(keyType key, int data, line *li) {
	node *new = (node*) malloc(sizeof(node));
	new -> key = key;
	new -> data = data;
	new -> next = NULL;
	if(!li -> beggin) {
		li -> beggin = new;
	} else {
		li -> end -> next = new;
	}
	li -> end = new;
}

void showLine(line li) {
	node *p = li.beggin;
	printf("Beggin -> [");
	while(p) {
		printf("%d, %d", p -> key, p -> data);
		p = p -> next;
		if(p) printf("], [");
	}
	printf("].\n");
}

void showFirst(line li) {
	if(!li.beggin) {
		printf("Empty line.\n");
	} else {
		printf("First -> [%d, %d].\n", li.beggin -> key, li.beggin -> data);
	}
}

void showLast(line li) {
	if(!li.beggin) printf("Empty line.\n");
	else {
		node *p = li.beggin;
		while(p -> next) {
			p = p -> next;
		}
		printf("Last -> [%d, %d].\n", p -> key, p -> data);
	}
}

int showSize(line li) {
	if(!li.beggin) {
		printf("Empty line.\n");
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

void putOut(line *line) {
	node *elem;
	elem = line -> beggin;
	if(!elem) {
		printf("Empty line.\n");
	} else {
		line -> beggin = elem -> next;
		free(elem);
	}
}

void clearLine(line *line) {
	node *atual, *next;
	atual = line -> beggin;
	while(atual) {
		next = atual -> next;
		free(atual);
		atual = next;
	}
	line -> beggin = NULL;
	line -> end = NULL;
}

int crescLine(line li) {
	node *atual, *next;
	atual = li.beggin;
	next = li.beggin -> next;
	while(atual -> next != NULL && next -> next != NULL) {
		if(atual -> key > next -> key) return 0;
		atual = next -> next;
		next = atual -> next;
	}
	return 1;
}


void separa(line *even, line *odd){
	int size = showSize(*even);
	for(int i = 0; i < size; i++) {
		if(even -> beggin -> data % 2 != 0) {
			putIn(even -> beggin -> key, even -> beggin -> data, odd);
		} else {
			putIn(even -> beggin -> key, even -> beggin -> data, even);
		}
		putOut(even);
	}
}

void removeMaior(line *li) {
	node *big, *next;
	big = li -> beggin;
	next = li -> beggin -> next;
	int i = showSize(*li);
	for(int k = 0; k < i; k++) {
		if(big -> data < next -> data) {
			big = next;
			next = next -> next;
		}
	}
	while(big -> data > li -> beggin -> data) {
		putIn(li -> beggin -> key, li -> beggin -> data, li);
		putOut(li);
	}
	putOut(li);
}

int main() {
	line li, li2;
	initiate(&li);
	initiate(&li2);
	separa(&li, &li2);
	showLine(li);
	if(crescLine(li)) printf("Esta em ordem crescente\n");
	else printf("Nao esta em ordem crescente\n");
	removeMaior(&li);
	showLine(li);
	showLine(li2);
	return 0;
}
