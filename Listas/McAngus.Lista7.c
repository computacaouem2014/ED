#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int keyType;

typedef struct structure {
	keyType key;
	int idade;
	char *nome;
	struct structure *next;
} pessoa;

typedef struct {
	pessoa *beggin, *end;
} fila;

typedef struct {
	fila *preferencial, *normal;
} banco;

typedef struct structur {
	keyType key;
	char *data;
	struct structur *next;
} node;

typedef struct {
	node *beggin, *end;
} line;

void initiate(line *li) {
	li -> beggin = NULL;
	li -> end = NULL;
	printf("\t\tFila inicializada.\n");
}

void initiateBank(banco *agencia) {
	agencia -> preferencial = (fila*) malloc(sizeof(fila));
	agencia -> preferencial -> beggin = NULL;
	agencia -> preferencial -> end = NULL;
	agencia -> normal = (fila*) malloc(sizeof(fila));
	agencia -> normal -> beggin = NULL;
	agencia -> normal -> end = NULL;
}

void putIn(keyType key, char *data, line *li) {
	node *new = (node*) malloc(sizeof(node));
	new -> key = key;
	new -> data = data;
	if(!li -> beggin) {
		li -> beggin = new;
		new -> next = NULL;
	} else {
		li -> end -> next = new;
	}
	li -> end = new;
}

void entrarNaFila(pessoa p, banco *agencia) {
	pessoa *new = (pessoa*) malloc(sizeof(pessoa));
	new -> key = p.key;
	new -> idade = p.idade;
	new -> nome = p.nome;
	new -> next = NULL;
	if(new -> idade >= 60) {
		if(!agencia -> preferencial -> beggin) {
			agencia -> preferencial -> beggin = new;
			printf("%s entrou na fila preferencial.\n", agencia -> preferencial -> beggin -> nome);
		} else {
			agencia -> preferencial -> end -> next = new;
		}
		if(agencia -> preferencial -> end) printf("%s entrou na fila.\n", agencia -> preferencial -> end -> nome);
	} else {
		if(!agencia -> normal -> beggin) {
			agencia -> normal -> beggin = new;
			printf("%s entrou na fila.\n", agencia -> normal -> beggin -> nome);
		} else {
			agencia -> normal -> end -> next  = new;
		}
		agencia -> normal -> end = new;
		if(agencia -> normal -> end != agencia -> normal -> beggin) printf("%s entrou na fila.\n", agencia -> normal -> end -> nome);
	}
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

void showFila(fila fi) {
	if(!fi.beggin) {
		pessoa *p = fi.beggin;
		printf("Beggin -> [");
		while(p) {
			printf("%d, %s, %d", p -> key, p -> nome, p -> idade);
			p = p -> next;
			if(p) printf("], [");
		}
		printf("].\n");
	} else {
		printf("Ninguem esta na fila.\n");
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
	banco agencia;
	initiateBank(&agencia);
	pessoa p1, p2, p3;
	p1.nome = "Carlos";
	p1.idade = 40;
	p2.nome = "Maria";
	p2.idade = 30;
	p3.nome = "Joao";
	p3.idade = 25;
	entrarNaFila(p1, &agencia);
	entrarNaFila(p2, &agencia);
	entrarNaFila(p3, &agencia);
	system("pause");
	return 0;
}
