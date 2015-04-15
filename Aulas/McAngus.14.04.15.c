#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50

typedef int keyType;

typedef struct {
	keyType key;
} reg;

typedef struct {
	reg a[MAX];
	int nElem, end, start;
} line;

void lineEnd(line *linha, keyType b) {
	if (linha -> nElem >= MAX) {
		printf("Vetor cheio\n");
	} else {
		linha -> a[linha -> nElem].key = b;
		linha -> nElem++;
		linha -> end++;
	}
}

void randNum(line *arr, int num, int max, int min) {
	srand(time(NULL));
	max -= min;
	for (int k = num - 1; k >= 0; k--)
		lineEnd(arr, rand() % max + min);
}

void insertion(line *linha) {
	for(int i = 1; i < linha -> nElem; i++){
		int j = i - 1, change = linha -> a[i].key;
		while(change < linha -> a[j].key && j >= 0){
			linha -> a[j + 1].key = linha -> a[j].key;
			j--;
		}
		linha -> a[j + 1].key = change;
	}
}

void lineStart(line *linha, int nElem, int start, int end) {
	linha -> nElem = nElem, linha -> end = end, linha -> start = start;
	printf("\t\t\t\t\t\t\t\t\t\\\\Line initialized//\n\t\t\t\t\t\t\t\t\t \\\\\\\\\\\\\\\\\\/////////\n");
}

int lineSearch(keyType b, line linha) {
	for (int i = 0; i < linha.nElem; i++) {
		if (b == linha.a[i].key) return i;
	} return 0;
}

void lineInsert(line *linha, keyType b, int j) {
	if (linha -> nElem >= MAX) {
		printf("Vetor cheio\n");
	} else if (j < 0 || j > linha -> nElem) {
		printf("Valor incorreto.");
	} else if (!j) {
		linha -> a[j].key = b;
		linha -> nElem++;
		linha -> end++;
	} else if (j) {
		linha -> a[j].key = b;
		linha -> nElem++;
		linha -> end++;
	}
}

void lineInsertOrd(line *linha, keyType b) {
	if (linha -> nElem >= MAX){
		printf("linha Cheia.\n");
	} else {
		int i;
		for (i = 0; i < linha -> nElem; i++) {
			if (b < linha -> a[i].key) break;
		}
		if (i < linha -> nElem) {
			linha -> nElem++;
			for (int j = linha -> nElem - 1; j > i; j--) {
				linha -> a[j].key = linha -> a[j - 1].key;
			}
			linha -> a[i].key = b;
		}
	}
}

void showLine(line linha) {
	for (int i = 0; i < linha.nElem; i++) {
		printf("| %d ", linha.a[i].key);
	} printf("|\n");
}

void invertLine(line linha1, line *linha2) {
	for (int i = 0; i < linha1.nElem; i++) {
		lineInsert(linha2, linha1.a[i].key, 0);
	}
}

void copyLine(line linha1, line *linha2) {
	for (int i = 0; i < linha1.nElem; i++) {
		lineInsert(linha2, linha1.a[i].key, i);
	}
}

void lineDel(keyType b, line *linha) {
	if (lineSearch(b, *linha) < 0) printf("\nO Elemento nao esta na linha.\n");
	else {
		int j = lineSearch(b, *linha);
		for (int i = j; i < linha -> nElem; i++) {
			linha -> a[i].key = linha -> a[i + 1].key;
		}
		linha -> nElem--;
	}
}

keyType lineFirst(line linha) {
	if (linha.nElem == 0)	return -1;
	else return linha.a[0].key;
}

void delFirst(line *linha) {
	if (linha -> nElem == 0) printf("\n[Empty line].\n");
	else {
		linha -> start++;
		linha -> nElem--;
	}
}

int main(){
	line staticList1, staticList2;
	srand(time(NULL));
	int random = rand() % 200 - 100;
	lineStart(&staticList1, 0, 0, 0);
	lineStart(&staticList2, 0, 0, 0);
	randNum(&staticList1, 30, 100, 10);
	printf("%d | %d\n", staticList1.nElem, staticList2.nElem);
	insertion(&staticList2);
	printf("%d | %d\n", staticList1.nElem, staticList2.nElem);
	showLine(staticList1);
	copyLine(staticList1, &staticList2);
	lineEnd(&staticList2, random);
	showLine(staticList2);
	return 0;
}
