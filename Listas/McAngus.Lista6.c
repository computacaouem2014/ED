#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct structure {
	char data;
	struct structure *next;
} node;

typedef struct {
	node *top;
} stack;

typedef struct boxes {
	int box_weight;
	struct boxes *next;
} box;

typedef struct {
	int capacity, total_weight;
	box *atual;
} truck;

void initiate(stack *pile) {
	pile -> top = NULL;
}

void truckStart(truck *caminhao) {
	caminhao -> atual = NULL;
	caminhao -> capacity = 100;
	caminhao -> total_weight = 0;
}

void loadTruck(box *caixa, truck *caminhao) {
	if(caminhao -> total_weight + caixa -> box_weight > caminhao -> capacity) {
		printf("Caminhao cheio.\n");
	} else {
		caminhao -> atual = caixa;
		caminhao -> total_weight += caixa -> box_weight;
	}
}

box *unloadTruck(truck *caminhao) {
	box *elem;
	elem = caminhao -> atual;
	if(!elem) {
		printf("Caminhao vazio.\n");
		return NULL;
	} else {
		caminhao -> total_weight -= caminhao -> atual -> box_weight;
		caminhao -> atual = elem -> next;
		return elem;
	}
}

void putIn(char data, stack *pile) {
	node *new;
	new = (node*) malloc(sizeof(node));
	new -> data = data;
	new -> next = pile -> top;
	pile -> top = new;
}

void showStack(stack pile) {
	if(!pile.top) printf("Empty Stack.\n");
	else {
		node *p = pile.top;
		printf("Top -> [");
		while(p) {
			printf("%c", p -> data);
			p = p -> next;
			if(p) printf("], [");
		}
		printf("].\n");
	}
}

int showSize(stack pile) {
	if(!pile.top) return 0;
	else {
		int size = 1;
		node *p = pile.top;
		while(p -> next) {
			p = p -> next;
			size++;
		}
		return size;
	}
}

void putOut(stack *pile) {
	node *elem;
	elem = pile -> top;
	if(!elem) {
		printf("Pilha vazia.\n");
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

bool palindrome(char word[]) {
	stack pile;
	for(int i = 0; i < strlen(word); i++) {
		putIn(word[i], &pile);
	}
	for(int i = 0; i < strlen(word); i++) {
		if(word[i] != pile.top -> data) return false;
		putOut(&pile);
	}
	return true;
}

bool checkBracket(char word[]) {
	stack pile;
	initiate(&pile);
	if(word[0] == ')') return false;
	for(int i = 0; i < strlen(word); i++) {
		if(word[i] == '(') putIn(word[i], &pile);
	}
	for(int i = 0; i < strlen(word); i++) {
		if(word[i] == ')') putOut(&pile);
	}
	if(pile.top) return false;
	return true;
}

void invertString(stack *pile, char string[]) {
	for(int i = strlen(string) - 1; i > -1 ; i--) {
		if(string[i] == ' ' || !i) {
			for(int j = i + 1; j < strlen(string); j++) {
				if(string[j] == ' ') break;
				putIn(string[j], pile);
			}
			putIn(string[i], pile);
		}
	}
}

void inverterPilha(stack *pile) {
	stack aux;
	initiate(&aux);
	int size = showSize(*pile);
	for(int i = 0; i < size; i++) {
		putIn(pile -> top -> data, &aux);
		putOut(pile);
	}
	*pile = aux;
}

int main() {
	int menu = 1;
	stack pile;
	while(menu){
	printf("Escolha um exercicio (1 - 5), digite 0 para sair: "); scanf("%d", &menu);
	initiate(&pile);
	clearStack(&pile);
		switch(menu){
			case 1: {
				char word[30];
				printf("Digite a palavra que deseja verificar: "); getchar();
				gets(word);
				if(palindrome(word)) printf("Palindrome.\n");
				else printf("Nao e palindrome.\n");
			} break;
			case 2: {
				char word[60];
				printf("Digite a expressao matematica: "); getchar();
				gets(word);
				if(checkBracket(word)) printf("Expressao correta.\n");
				else printf("Expressao incorreta.\n");
			} break;
			case 3: {
				char string[100];
				printf("Digite a string: "); getchar();
				gets(string);
				invertString(&pile, string);
				showStack(pile);
			} break;
			case 4: {
				char string[100];
				printf("Digite a string: "); getchar();
				gets(string);
				for(int i = 0; i < strlen(string); i++) putIn(string[i], &pile);
				showStack(pile);
				inverterPilha(&pile);
				showStack(pile);
			} break;
			case 5: {
				truck caminhao;
				truckStart(&caminhao);
				box box1, box2, box3;
				box1.box_weight = 50;
				box2.box_weight = 50;
				box3.box_weight = 50;
				loadTruck(&box1, &caminhao);
				loadTruck(&box2, &caminhao);
				unloadTruck(&caminhao);
				loadTruck(&box3, &caminhao);
			} break;
		}
	}
	return 0;
}
