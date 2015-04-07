#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printMatrix(int m, int n, char arr[m][n]){
    if (m*n > n){
        printf("\n⎡");
        for (int j = 0; j < n; j++){
            printf("%6c ", arr[0][j]);
        }
        printf("⎤\n");
        printf("⎢");
        for (int k = 0; k < n; k++){
            printf("       ");
        }
        printf("⎥\n");
        for (int i = 1; i < m-1; i++){
            if (i != 1){
                printf("⎢");
                for (int k = 0; k < n; k++){
                    printf("       ");
                }
                printf("⎥\n");
            }
            printf("⎢");
            for (int j = 0; j < n; j++){
                printf("%6c ", arr[i][j]);
            }
            printf("⎥\n");
        }
        printf("⎢");
        for (int k = 0; k < n; k++){
            printf("       ");
        }
        printf("⎥\n");
        printf("⎣");
        for (int j = 0; j < n; j++){
            printf("%6c ", arr[m-1][j]);
        }
        printf("⎦\n\n");
    } else if (m == 1){
        printf("\n[");
        for (int i = 0; i < n; i++){
                printf("%6c ", arr[0][i]);
        }
        printf("]\n\n");
    } else {
        printf("\n[]\n\n");
    }
}


void swap(int lines, int col, char arr[lines][col], int a, int b){
	char aux[col];
	for(int i = 0; i < col; i++){
		aux[i] = arr[a][i];
		arr[a][i] = arr[b][i];
		arr[b][i] = aux[i];
	}
}

void insertion(int lines, int col, char arr[lines][col]){
	for(int i = 0; i < lines - 1; i++){
		for(int j = i + 1; j < lines; j++){
			int max = i;
			for(int k = 0; k < col; k++){
				if(arr[max][k] > arr[j][k]){
					max = j;
					break;
				}
				if (max != i) {
					char aux[col];
					for(int i = 0; i < col; i++){
						aux[i] = arr[max][i];
						arr[max][i] = arr[j + 1][i];
						arr[j + 1][i] = aux[i];
					}
				}
			}
		}
	}
}

void ex1(){
	char names[9][6] = {" "};
	for(int i = 0; i < 9; i++){
		printf("Digite o %d nome: ", i + 1);
		gets(names[i]); strtok(names[i], "\n");
	}
	printMatrix(9, 6, names);
	insertion(9, 6, names);
	printMatrix(9, 6, names);
}

int main(){
	ex1();
	return 0;
}
