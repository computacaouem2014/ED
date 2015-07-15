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
		new -> next = NULL;
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
		agencia -> preferencial -> end = new;
		if(agencia -> preferencial -> end != agencia -> preferencial -> beggin) printf("%s entrou na fila preferencial.\n", agencia -> preferencial -> end -> nome);
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

void atenderProximo(banco *agencia) {
	if(agencia -> preferencial -> beggin) {
		pessoa *elem;
		elem = agencia -> preferencial -> beggin;
		printf("Atendendo %s.\n", agencia -> preferencial -> beggin -> nome);
		agencia -> preferencial -> beggin = elem -> next;
		free(elem);
	} else if(agencia -> normal -> beggin) {
		pessoa *elem;
		elem = agencia -> normal -> beggin;
		printf("Atendendo %s\n", agencia -> normal -> beggin -> nome);
		agencia -> normal -> beggin = elem -> next;
		free(elem);
	}
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

void unInter(line l1, line l2, line *uni, line *inter) {
	node *p1 = l1.beggin, *p2 = l2.beggin;
	while(p1) {
		putIn(p1 -> key, p1 -> data, uni);
		p1 = p1 -> next;
	} p1 = l2.beggin;
	while(p1) {
		putIn(p1 -> key, p1 -> data, uni);
		p1 = p1 -> next;
	} p1 = l1.beggin;
	while(p2) {
		while(p1) {
			if(p1 -> data == p2 -> data) putIn(p1 -> key, p1 -> data, inter);
			p1 = p1 -> next;
		}
		p1 = l1.beggin;
		p2 = p2 -> next;
	}
}

int main() {
	line one, two, uni, inter;
	banco agencia;
	initiateBank(&agencia);
	pessoa p1, p2, p3, p4, p5, p6;
	p1.nome = "Carlos";
	p1.idade = 70;
	p2.nome = "Maria";
	p2.idade = 30;
	p3.nome = "Joao";
	p3.idade = 25;
	p4.nome = "Clarisse";
	p4.idade = 40;
	p5.nome = "Clara";
	p5.idade = 90;
	p6.nome = "Teresa";
	p6.idade = 80;
	initiate(&one);
	initiate(&two);
	initiate(&uni);
	initiate(&inter);
	putIn(0, "1", &one);
	putIn(0, "2", &one);
	putIn(0, "3", &one);
	putIn(0, "4", &one);
	putIn(0, "5", &one);
	putIn(0, "6", &two);
	putIn(0, "7", &two);
	putIn(0, "8", &two);
	putIn(0, "9", &two);
	putIn(0, "10", &two);
	showLine(one);
	showLine(two);
	unInter(one, two, &uni, &inter);
	showLine(uni);
	showLine(inter);
	entrarNaFila(p1, &agencia);
	entrarNaFila(p2, &agencia);
	entrarNaFila(p3, &agencia);
	entrarNaFila(p4, &agencia);
	entrarNaFila(p5, &agencia);
	entrarNaFila(p6, &agencia);
	atenderProximo(&agencia);
	atenderProximo(&agencia);
	atenderProximo(&agencia);
	atenderProximo(&agencia);
	atenderProximo(&agencia);
	atenderProximo(&agencia);
	system("pause");
	return 0;
}
