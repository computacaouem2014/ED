#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct strings{
	char str[5];
};

void printMatrix(int m, int n, int arr[m][n]){
    if (m*n > n){
        printf("\n|");
        for (int j = 0; j < n; j++){
            printf("%6d ", arr[0][j]);	
        }
        printf("|\n");
        printf("|");
        for (int k = 0; k < n; k++){
            printf("       ");
        }
        printf("|\n");
        for (int i = 1; i < m-1; i++){
            if (i != 1){
                printf("|");
                for (int k = 0; k < n; k++){
                    printf("       ");
                }
                printf("|\n");
            }
            printf("|");
            for (int j = 0; j < n; j++){
                printf("%6d ", arr[i][j]);
            }
            printf("|\n");
        }
        printf("|");
        for (int k = 0; k < n; k++){
            printf("       ");
        }
        printf("|\n");
        printf("|");
        for (int j = 0; j < n; j++){
            printf("%6d ", arr[m-1][j]);
        }
        printf("|\n\n");
    } else if (m == 1){
        printf("\n[");
        for (int i = 0; i < n; i++){
                printf("%6d ", arr[0][i]);
        }
        printf("]\n\n");
    } else {
        printf("\n[]\n\n");
    }
}

void matrixFill(int lines, int col, int mat[lines][col]){
	int i, j;
	for(i = 0; i < lines; i++){
		for(j = 0; j < col; j++){
			printf("Digite o termo [%d][%d]: ", i + 1, j + 1);
			scanf("%d", &mat[i][j]);
		}
	}
	printMatrix(lines, col, mat);
}

void randMatrix(int lines, int col, int arr[lines][col], int max, int min){
	srand(time(NULL));
	max -= min;
	for (int k = 0; k < lines; k++){
		for (int j = 0; j < col; j++)
			arr[k][j] = rand() % max + min;
	}
}


void ex1(){
	int mat[8][8], max, i, j;
	matrixFill(8, 8, mat);
	max = mat[0][0];
	for(i = 1; i < 8; i++){
		if(mat[i][i] > max) max = mat[i][i];
	}
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			mat[i][j] = mat[i][j] / max;
		}
	}
	printMatrix(8, 8, mat);
}

void ex2(){
	int mat[10][10], i, j, aux;
	matrixFill(10, 10, mat);
	for(i = 0; i < 10; i++){
		aux = mat[1][i];
		mat[1][i] = mat[7][i];
		mat[7][i] = aux;
	}
	printMatrix(10, 10, mat);
	for(i = 0; i < 10; i++){
		aux = mat[i][3];
		mat[i][3] = mat[i][9];
		mat[i][9] = aux;
	}
	printMatrix(10, 10, mat);
	for(i = 0; i < 10; i++){
		j = 9 - i;
		aux = mat[i][i];
		mat[i][i] = mat[i][j];
		mat[i][j] = aux;
	}
	printMatrix(10, 10, mat);
	for(i = 0; i < 10; i++){
		aux = mat[4][i];
		mat[4][i] = mat[i][9];
		mat[i][9] = aux;
	}
	printMatrix(10, 10, mat);
}

int mediaAr(int lines, int col, int mat[lines][col]){
	int i, j, sum = 0, count = 0;
	for(i = 1; i < lines; i++){
		j = 0;
		while(i > j){
			sum += mat[i][j];
			j++; count++;
		}
	}
	return sum/count;
}

void ex4(){
	int mat[3][3], i, j;
	matrixFill(3, 3, mat);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if ((i + j) % 2 != 0) {
				printf("%d; ", mat[i][j]);
			}
		}
	}
}

void ex5(){
	int matA[3][3], matB[3][3], check = 1, i, j;
	matrixFill(3, 3, matA);
	matrixFill(3, 3, matB);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++){
			if (matA[i][j] != matB[j][i]) {
				check = 0;
				break;
			}
		}
	}
	printf("A matriz %s a transposta.", check == 0 ? "nao e" : "e");
}

void ex6(){
	int size, i, j, check = 1;
	printf("Digite o tamanho da matriz: ");
	scanf("%d", &size);
	int mat[size][size];
	matrixFill(size, size, mat);
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			if (mat[i][j] != mat[j][i]){
				check = 0;
				break;
			}
		}
	}
	printf("A matriz %s simetrica.", check == 0 ? "nao e" : "e");	
}

void ex7(){
	int size, i, j, stop;
	printf("Digite o tamanho da matriz: ");
	scanf("%d", &size);
	int mat[size][size];
	for (i = 0; i < size; i++){
		stop = size;
		for (j = i; j < size; j++){
			mat[i][j] = stop - j + i;
			mat[j][i] = stop - j + i;
		}
	}
	printMatrix(size, size, mat);
}

void ex8(){
	int min, i, j, max[2], mat[5][5];
	matrixFill(5, 5, mat);
	max[0] = mat[0][0]; max[1] = 0;
	min = mat[0][0];
	for (i = 0; i < 5; i++){
		for (j = 1; j < 5; j++){
			if (mat[i][j] > max[0]){
				max[0] = mat[i][j];
				max[1] = i;
			}
		}
	}
	for (i = 0; i < 5; i++){
		if (min > mat[max[1]][i]) min = mat[max[1]][i];
	}
	printf("O elemento minimax é %d.", min);	
}

void ex9(){
	struct strings mat[5], matT[5];
	int i, j, check = 0;
	for (i = 0; i < 4; i++) {
		printf("Digite a %d string: ", i + 1);
		gets(mat[i].str);
		for (j = 0; j < 4; j++) matT[j].str[i] = mat[i].str[j]; matT[i].str[j] = 0;
	}
	for (i = 0; i < 3; i++) {
		for(j = i + 1; j < 4; j++) {
			if (strcmp(mat[i].str, mat[j].str) == 0 || strcmp(matT[i].str, matT[j].str) == 0) check = 1;
		}
	}
	printf("A palavra %s aparece.", check == 0 ? "nao" : "\b");
}

void ex10(){
	int i = 0, j = 0, k = 0, inca = 1, size;
	printf("Digite o tamanho da matriz: ");
	scanf("%d", &size);
	int mat[size][size];
	matrixFill(size, size, mat);
	i = 0; j = 0, k = size;
	do {
		while (++i < j + k){
			if (mat[j][i] != mat[j][i - 1] + 1) inca = 0;
		} i--;
		while (j++ < i){
			if (mat[j][i] != mat[j - 1][i] + 1) inca = 0;
		} j--;
		while (i-- > j - k + 1){
			if (mat[j][i] != mat[j][i + 1] + 1) inca = 0;
		} i++;
		while (j > i + 1){
			if (mat[--j][i] != mat[j + 1][i] + 1) inca = 0;
		}
		k -= 2;
	} while (k > 0);
	printf("\nA matriz %s inca.", inca == 1 ? "e" : "nao e");
}

int main(){
	int menu;
	do {
		printf("\n\nEscolha 1 exercicio de 1 - 10, entre 0 para sair: \n--> ");
		scanf("%d", &menu);
		switch(menu){
			case 1: {
				ex1();
				break;
			}
			case 2: {
				ex2();
				break;
			}
			case 3: {
				int mat[5][5];
				matrixFill(5, 5, mat);
				printf("A media dos elementos abaixo da diagonal principal e %d.", (float)mediaAr(5, 5, mat));
				break;
			}
			case 4: {
				ex4();
				break;
			}
			case 5: {
				ex5();
				break;
			}
			case 6: {
				ex6();
				break;
			}
			case 7: {
				ex7();
				break;
			}
			case 8: {
				ex8();
				break;
			}
			case 9: {
				ex9();
				break;
			}
			case 10: {
				ex10();
				break;
			}
			default: {
				printf("Opcao invalida.\n");
				break;
			}
		}
	} while (menu != 0);
	return 0;
}
