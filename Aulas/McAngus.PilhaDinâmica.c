#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Pilha dinamica

typedef int keyType;

typedef struct structure {
	keyType key;
	int data;
	struct structure *next;
} node;

typedef struct {
	node *top;
} stack;

void initiate(stack *pile) {
	pile -> top = NULL;
	printf("\t\tPilha inicializada.\n");
}

void putIn(keyType key, int data, stack *pile) {
	node *new;
	new = (node*) malloc(sizeof(node));
	new -> key = key;
	new -> data = data;
	new -> next = pile -> top;
	pile -> top = new;
	printf("%d;%d\n", key, data);
}

void showStack(stack pile) {
	node *p = pile.top;
	printf("Top -> [");
	while(p) {
		printf("%d, %d]", p -> key, p -> data);
		p = p -> next;
		if(p) printf(", [");
	}
	printf(".\n");
}

void showFirst(stack pile) {
	if(!pile.top) {
		printf("Empty stack.\n");
	} else {
		printf("First -> [%d, %d].\n", pile.top -> key, pile.top -> data);
	}
}

void showLast(stack pile) {
	if(!pile.top) printf("Empty Stack.\n");
	else {
		node *p = pile.top;
		while(p -> next) {
			p = p -> next;
		}
		printf("Last -> [%d, %d].\n", p -> key, p -> data);
	}
}

void showSize(stack pile) {
	if(!pile.top) printf("Empty Stack.\n");
	else {
		int size = 1;
		node *p = pile.top;
		while(p -> next) {
			p = p -> next;
			size++;
		}
		printf("Size -> [%d].\n", size);
	}
}

void putOut(stack *pile) {
	node *elem;
	elem = pile -> top;
	if(!elem) {
		printf("Empty Stack.\n");
	} else {
		pile -> top = elem -> next;
		free(elem);
	}
}

void clearStack(stack *pile) {
	node *atual;
	node *next;
	atual = pile -> top;
	while(atual) {
		next = atual -> next;
		free(atual);
		atual = next;
	}
	pile -> top = NULL;
}

int main() {
	stack pile;
	int num;
	initiate(&pile);
	scanf("%d", &num);
	putIn(0, num, &pile);
	putIn(1, num + 1, &pile);
	putIn(2, num + 2, &pile);
	putIn(3, num + 3, &pile);
	putOut(&pile);
	showStack(pile);
	showFirst(pile);
	showLast(pile);
	showSize(pile);
	clearStack(&pile);
	showStack(pile);
	return 0;
}
