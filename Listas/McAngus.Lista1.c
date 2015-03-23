#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printVec(float vec[], int size){
	if(size == 1) printf("[%.f].\n", vec[size - 1]);
		else{
			if(size == 2) printf("[%.f, %.f\n].", vec[size - 1], vec[size]);
				else{
					printf("[%.f, ", vec[0]);
					for(int i = 1; i < size - 2; i++) printf("%.f, ", vec[i]);
					printf("%.f].\n", vec[size - 1]);
				}
		}
}

void printVecInt(int vec[], int size){
	if(size == 1) printf("[%d].\n", vec[size - 1]);
		else{
			if(size == 2) printf("[%d, %d].\n", vec[size - 1], vec[size]);
				else{
					printf("[%d, ", vec[0]);
					for(int i = 1; i < size - 2; i++) printf("%d, ", vec[i]);
					printf("%d].\n", vec[size - 1]);
				}
		}
}

int fact(int a){
	return a > 1 ? fact(a - 1) * a : 1;
}

void ex1(){
	int coA[20], coB[10], coC[10], count = 0;
	for(int i = 0; i < 20; i++){
		printf("[CONJ A] - Digite o %d numero: ", i + 1);
		scanf("%d", &coA[i]);
	}
	for(int i = 0; i < 10; i++){
		printf("[CONJ B] - Digite o %d numero: ", i + 1);
		scanf("%d", &coB[i]);
		int aux = coB[i], aux2 = 1;							//aux2 indica elemento repetido
		for(int j = 0; j < i; j++) if(coB[j] == aux) aux2 = 0;                      //Verifico elementos repetidos
		if(aux2){
			for(int j = 0; j < 20; j++){					   //Coloco elemento no coC
				if(coB[i] == coA[j]) {						   //se não for repetido
					coC[count] = coB[i];
					count++;
					break;
				}
			}
		}
	}
	printVecInt(coC, count);    //Imprimo coC
}

void ex2(){
	int vecA[10], vecB[10];
	for(int i = 0; i < 10; i++){
		printf("Digite o %d numero: ", i + 1);
		scanf("%d", &vecA[i]);						//Scan vecA
		vecB[i] = fact(vecA[i]);					//Gera vecB
	}
	for(int i = 0; i < 10; i++) printf("%d; ", vecB[i]); //Printa vecB
}

void ex3(){
	float vecA[10], vecB[10], vecC[10];
	for(int i = 0; i < 10; i++){
		printf("[VET A] - Digite o %d numero: ", i + 1);	//Gera vecA
		scanf("%f", &vecA[i]);
	}
	for(int i = 0; i < 10; i++){
		printf("[VET B] - Digite o %d numero: ", i + 1);	//Gera vecB e vecC,
		scanf("%f", &vecB[i]);
		vecC[i] = vecA[i] - vecB[i];
	}
	printVec(vecC, 10);
}

void ex4(){
	float temp[12], max, min;
	for(int i = 0; i < 12; i++){
		printf("Digite a temperatura do mes %d: ", i + 1);
		scanf("%f", &temp[i]);
		if(!i){
			max = temp[i];
			min = temp[i];
		}
		if(temp[i] > max) max = temp[i];
		if(temp[i] < min) min = temp[i];
	}
	printVec(temp, 12);
	printf("\nMaxima de %.f, minima de %.f.\n", max, min);
}

void ex5(){
	int num[100], max, min, sum = 0, even = 0;
	for(int i = 0; i < 100; i++){
		printf("Digite o %d numero: ", i + 1);
		scanf("%d", &num[i]);
		if(!i){
			max = num[i];
			min = num[i];
		}
		if(num[i] > max) max = num[i];
		if(num[i] < min) min = num[i];
		if(num[i] % 2 == 0) even++;
		sum += num[i];
	}
	printf("Maior numero registrado: %d.\nMenor numero registrado: %d.\nPercentual de numeros pares: %.2f.\nMedia dos elementos registrados: %.2f\n", max, min, (float)even/100, (float)sum/100);
}

void ex6(){
	int nVoo = 1;
	int flyNum[nVoo], flyCap[nVoo], menu;
	char flyOri[nVoo][30], flyDes[nVoo][30];
	for(int i = 0; i < nVoo; i++){
		printf("Digite o numero do %d voo: ", i + 1); scanf("%d", &flyNum[i]); getchar();
		printf("Digite a capacidade do %d voo: ", i + 1); scanf("%d", &flyCap[i]); getchar();
		printf("Digite a origem do %d voo: ", i + 1); fgets(flyOri[i], 30, stdin); strtok(flyOri[i], "\n");
		printf("Digite o destino do %d voo: ", i + 1); fgets(flyDes[i], 30, stdin); strtok(flyDes[i], "\n");
	}
	do{
		printf("\n\n\t\t1 - Consultar\n\t\t2 - Efetuar Reserva\n\t\t0 - Sair\n\t>>");
		scanf("%d", &menu);
		int subMenu;
		switch(menu){
			case 1:{
				printf("\n\t\t\t1 - Por numero de voo\n\t\t\t2 - Por origem\n\t\t\t3 - Por destino\n\t\t\t0 - Voltar\n\t>>");
				scanf("%d", &subMenu);
				switch(subMenu){
					case 1:{
						int findNum;
						printf("Digite o numero do voo que deseja procurar: ");
						scanf("%d", &findNum);
						for(int i = 0; i < nVoo; i++){
							if(findNum == flyNum[i]) printf("\nNumero: %d.\nLugares: %d.\nOrigem:%s.\nDestino: %s.", flyNum[i], flyCap[i], flyOri[i], flyDes[i]);
							else printf("\nVoo nao encontrado.");
						}
					} break;
					case 2:{
						char findOri[30];
						printf("Digite a origem do voo que deseja procurar: ");
						fgets(findOri, 30, stdin); strtok(findOri, "\n");
						for(int i = 0; i < nVoo; i++){
							if(strcmp(findOri, flyOri[i]) == 1) printf("\nNumero: %d.\nLugares: %d.\nOrigem:%s.\nDestino: %s.", flyNum[i], flyCap[i], flyOri[i], flyDes[i]);
							else printf("\nVoo nao encontrado.");
						}
					} break;
					case 3:{
						char findDes[30];
						getchar();
						printf("Digite o destino do voo que deseja procurar: ");
						fgets(findDes, 30, stdin); strtok(findDes, "\n");
						for(int i = 0; i < nVoo; i++){
							if(strcmp(findDes, flyDes[i]) == 1) printf("\nNumero: %d.\nLugares: %d.\nOrigem:%s.\nDestino: %s.", flyNum[i], flyCap[i], flyOri[i], flyDes[i]);
							else printf("\nVoo nao encontrado.");
						}
					} break;
					default: break;
				}
			}
			break;
			case 2:{
				printf("Digite o numero do voo qual deseja efetuar a reserva: ");
				scanf("%d", &subMenu);
				for(int i = 0; i < nVoo; i++){
					if(subMenu == flyNum[i]){
						if(flyCap[i] > 0){
							printf("Reserva efetuada com sucesso.");
							flyCap[i]--;
						} else printf("Voo lotado.");
					} else printf("Voo inexistente.");
				}	
			}
			break;
		}
	} while(menu != 0);
}
	

int main(){
	int ex = 1;
	do {
		printf("Escolha um exercicio (de 1 a 6, 0 para sair): \n-->");
		scanf("%d", &ex);
		switch(ex){
			case 1: ex1(); break;
			case 2: ex2(); break;
			case 3: ex3(); break;
			case 4: ex4(); break;
			case 5: ex5(); break;
			case 6: ex6(); break;
			default: break;
		}
	} while(ex != 0);
	return 0;
}
