#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

typedef int keyType;

typedef struct {
	keyType key;
} reg;

typedef struct {
	reg a[MAX];
	int nElem, end, start, totalSize;
} circline;

int jump(int position) {
	return ((position + 1) % MAX);
}

void circlineInsert(circline *line, keyType b) {
	if (line -> end >= line -> totalSize) {
		printf("Vetor cheio\n");
	} else {
		line -> a[line -> end].key = b;
		line -> nElem++;
		line -> end = jump(line -> end);
	}
}

void randNum(circline *arr, int num, int max, int min) {
	max -= min;
	for (int k = num - 1; k >= 0; k--)
		circlineInsert(arr, rand() % max + min);
}

void insertion(circline *line) {
	for(int i = 1; i < line -> nElem; i++){
		int j = i - 1, change = line -> a[i].key;
		while(change < line -> a[j].key && j >= 0){
			line -> a[j + 1].key = line -> a[j].key;
			j--;
		}
		line -> a[j + 1].key = change;
	}
}

void circlineStart(circline *line, int nElem, int start, int end) {
	line -> nElem = nElem, line -> end = end, line -> start = start, line -> totalSize = MAX - 1;
	printf("\t\t\t\t\t\t\t\t\t\\\\circline initialized//\n\t\t\t\t\t\t\t\t\t \\\\\\\\\\\\\\\\\\/////////\n");
}

int circlineSearch(keyType b, circline line) {
	for (int i = line.start; i < line.nElem; i = jump(i)) {
		if (b == line.a[i].key) return (line.start - i);
	} return -1;
}

void showCircline(circline line) {
	for (int i = line.start; i < line.nElem; i = jump(i)) {
		printf("| %d ", line.a[i].key);
	} printf("|\n\n");
}

void circlineDel(circline *line) {
	if (line -> nElem == 0) printf("\n[Empty circline].\n");
	else {
		line -> start = jump(line -> start);
		line -> nElem--;
		if (line -> end == line -> totalSize) {
			line -> end = 0;
		} else line -> end = jump(line -> end);
	}
}

int circlineCheck(circline line) {
	return line.nElem == line.totalSize ? 0 : 1;
}

// void showLine(circline line) {
// 	int i = file.start, k;
// 	for (k = 0; k < )
// }

int main(){
	circline circularLine1, circularLine2;
	srand(time(NULL));
	int search;
	circlineStart(&circularLine1, 0, 0, 0);
	circlineStart(&circularLine2, 0, 0, 0);
	randNum(&circularLine1, 9, 100, 10);
	randNum(&circularLine2, 9, 100, 10);
	showCircline(circularLine1);
	showCircline(circularLine2);
	for (int i = 0; i < 5; i++) circlineDel(&circularLine1);
	for (int i = 0; i < 5; i++) circlineDel(&circularLine2);
	for (int i = 0; i < 5; i++) circlineInsert(&circularLine1, rand() % 200 - 100);
	for (int i = 0; i < 5; i++) circlineInsert(&circularLine2, rand() % 200 - 100);
	puts("");puts("");puts("");puts("");
	showCircline(circularLine1);
	showCircline(circularLine2);
	printf("Digite um elemento que deseja procurar: ");
	scanf("%d", &search);
	printf("Elemento%s encontrado na lista 1.\n", circlineSearch(search, circularLine1) != -1 ? "" : " nao");
	printf("Elemento%s encontrado na lista 2.\n", circlineSearch(search, circularLine2) != -1 ? "" : " nao");
	return 0;
}
