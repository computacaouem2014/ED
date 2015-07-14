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
	int nElem, size;
} list;

int jump(int position) {
	return (position + 1) % MAX;
}

void randVec(int arr[], int max, int min, int size){
	srand(time(NULL));
	max -= min;
	for (int k = size - 1; k >= 0; k--)
		arr[k] = rand() % max + min;
}

int listSearch(keyType b, list lista) {
	for (int i = 0; i < lista.size; i++) {
		if (b == lista.a[i].key) return i;
	} return -1;
}

void listStart(list *lista) {
	lista -> nElem = 0, lista -> size = MAX;
	printf("\\\\List initialized//\n\n");
}

void randNum(list *arr, int max, int min) {
	max -= min;
	for (int k = 0; k < arr -> size; k++) {
		arr -> a[k].key = rand() % max + min;
		arr -> nElem++;
	}
}

void showList(list lista) {
	for (int i = 0; i < lista.nElem; i++) {
		printf("| %4d ", lista.a[i].key);
	} printf("|\n");
}

void insertion(list *lista) {
	for(int i = 1; i < lista -> nElem; i++){
		int j = i - 1, change = lista -> a[i].key;
		while(change > lista -> a[j].key && j >= 0){
			lista -> a[j + 1].key = lista -> a[j].key;
			j--;
		}
		lista -> a[j + 1].key = change;
	}
}

//EX 1

void insereEmpurra(list *lista, keyType b, int j) {
	if (j < 0 || j > lista -> nElem) {
		printf("[Incorrect Value]\n");
	} else if (lista -> nElem < lista -> size){
		lista -> nElem++;
		for (int i = lista -> nElem - 1; i > j; i--) {
			lista -> a[i].key = lista -> a[i - 1].key;
		} lista -> a[j].key = b;
	} else {
		for (int i = lista -> nElem - 1; i > j; i--) {
			lista -> a[i].key = lista -> a[i - 1].key;
		} lista -> a[j].key = b;
	}
}

//EX 2

void removeArruma2(list *lista, keyType x, keyType y) {
	if (x > y) {
		while (y < x && y > 0) {
			lista -> a[x--].key = lista -> a[--y].key;
			lista -> a[y].key = 0;
		}
		while (x >= 0) lista -> a[x--].key = 0;
	} else {
		while (x < y && x > 0) {
			lista -> a[y--].key = lista -> a[--x].key;
			lista -> a[x].key = 0;
		}
		while (y >= 0) lista -> a[y--].key = 0;
	}
}

//EX 3

void removeArruma3(list *lista, keyType x, keyType y) {
	if (x > y) {
		while (y < x && y > 0) {
			lista -> a[x--].key = lista -> a[--y].key;
			lista -> a[y].key = 0;
		}
		while (x >= 0) lista -> a[x--].key = 0;
	} else {
		while (x < y && x > 0) {
			lista -> a[y--].key = lista -> a[--x].key;
			lista -> a[x].key = 0;
		}
		while (y >= 0) lista -> a[y--].key = 0;
	}
}

//EX 4

void returnHigher(list *lista, keyType k, list *returnList) {
	if (k < 0 || k > lista -> nElem) printf("\n[Invalid axis]\n");
	else {
		for (int i = 0; i < lista -> nElem; i++) {
			int max = lista -> a[i].key;
			if (listSearch(max, *returnList) != -1) continue;
			for (int j = 0; j < lista -> nElem; j++) {
				if (i != j) {
					if (max < lista -> a[j].key && listSearch(lista -> a[j].key, *returnList) == -1) {
						max = lista -> a[j].key;
					}
				}
			}
			if (k > 0) insereEmpurra(returnList, max, 0); // Funcao EX 1
			else break;
			k--;
		}
	}
}

//EX 5

void transferVec(list *lista, int *vector, int size) {
	if (lista -> nElem >= lista -> size) {
		printf("[Full List]\n");
	} else if (size > lista -> size - lista -> nElem) {
		printf("A lista nao possui espaco para todos os elementos.");
	} else {
		for (int i = 0; i < size; i++) {
			insereEmpurra(lista, vector[i], lista -> nElem - i); // Funcao EX 1
		}
	}
}

void transferVecI(list *lista, int *vector, int size) {
	if (lista -> nElem >= lista -> size) {
		printf("[Full List]\n");
	} else if (size > lista -> size - lista -> nElem) {
		printf("A lista nao possui espaco para todos os elementos.");
	} else {
		for (int i = 0; i < size; i++) {
			insereEmpurra(lista, vector[i], i); // Funcao EX 1
		}
	}
}

//EX 6

void filterHigher(list *high, list *low) {
	for (int i = 0; i < high -> nElem; i++) {
		for (int j = 0; j < low -> nElem; j++) {
			if (high -> a[i].key < low -> a[j].key) {
				int aux = high -> a[i].key;
				high -> a[i].key = low -> a[j].key;
				low -> a[j].key = aux;
			}
		}
	}
}

//EX 7

int ex7(){
	int n = 10, vec[n], low = -1, high = -1;
	randVec(vec, 500, 200, n);
	list foward, backward, distanceFoward, distanceBackward;
	listStart(&foward);
	listStart(&backward);
	listStart(&distanceFoward);
	listStart(&distanceBackward);
	transferVec(&foward, vec, 10);
	transferVecI(&backward, vec, 10);
	showList(foward);
	showList(backward);
	for (int j = 0; j < foward.size; j++) {
		insereEmpurra(&distanceFoward, foward.a[j].key + foward.a[jump(j)].key, 0);
		insereEmpurra(&distanceBackward, backward.a[j].key + backward.a[jump(j)].key, 0);
		for (int i = 0; i < foward.size - 1; i++) {
			insereEmpurra(&distanceFoward, (foward.a[jump(i)].key + distanceFoward.a[i].key), jump(i));
			insereEmpurra(&distanceBackward, (backward.a[jump(i)].key + distanceBackward.a[i].key), jump(i));
		}
		if (distanceBackward.a[MAX - 1].key < distanceFoward.a[MAX - 1].key) {
			if (distanceFoward.a[MAX - 1].key > high) {
				high = distanceFoward.a[MAX - 1].key;
				for (int k = 0; k < foward.size - 1; k++) {
					if(!k) low = distanceFoward.a[k].key;
					if (distanceFoward.a[k].key < low) low = distanceFoward.a[k].key;
				}
			}
		} else if (distanceFoward.a[MAX - 1].key < distanceBackward.a[MAX - 1].key) {
			if (distanceBackward.a[MAX - 1].key > high) {
				high = distanceBackward.a[MAX - 1].key;
				for (int k = 0; k < backward.size - 1; k++) {
					if(!k) low = distanceBackward.a[k].key;
					if (distanceBackward.a[k].key < low) low = distanceBackward.a[k].key;
				}
			}
		}
	}
	printf("\n\n%d, %d\n\n", high, low);
	return 0;
}

int main() {
	srand(time(NULL));
	system("pause");
	return 0;
}
