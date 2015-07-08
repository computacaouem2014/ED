#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Fila dinamica

typedef int keyType;

typedef struct structure {
	keyType key;
	char *data;
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

void putIn(keyType key, char *data, line *li) {
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
		printf("%d, %s", p -> key, p -> data);
		p = p -> next;
		if(p) printf("], [");
	}
	printf("].\n");
}

void showFirst(line li) {
	if(!li.beggin) {
		printf("Empty line.\n");
	} else {
		printf("First -> [%d, %s].\n", li.beggin -> key, li.beggin -> data);
	}
}

void showLast(line li) {
	if(!li.beggin) printf("Empty line.\n");
	else {
		node *p = li.beggin;
		while(p -> next) {
			p = p -> next;
		}
		printf("Last -> [%d, %s].\n", p -> key, p -> data);
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

void insertName(line *li) {
	char *name;
	int key = 0;
	name = malloc(sizeof(char) * 256);
	printf("Digite o nome: "); gets(name);
	while(strlen(name)) {
		putIn(key, name, li);
		name = malloc(sizeof(char) * 256);
		printf("Digite o nome: "); gets(name);
		key--;
	}
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

void invert(line *li) {
	char *aux;
	aux = malloc(sizeof(char) * 256);
	node *p1, *p2, *p3;
	p1 = li -> beggin;
	p2 = li -> end;
	do {
		p3 = p2;
		aux = p1 -> data;
		p1 -> data = p2 -> data;
		p2 -> data = aux;
		p1 = p1 -> next;
		p2 = p1;
		while(p2 -> next != p3 && p2 -> next != NULL) p2 = p2 -> next;
		if(p1 -> next == p2) {
			aux = p1 -> data;
			p1 -> data = p2 -> data;
			p2 -> data = aux;
			break;
		}
	} while(p1 != p2);
}

int main() {
	line li;
	initiate(&li);
	insertName(&li);
	showLine(li);
	if(crescLine(li)) printf("Esta em ordem crescente\n");
	else printf("Nao esta em ordem crescente\n");
	invert(&li);
	showLine(li);
	system("pause");
	return 0;
}
