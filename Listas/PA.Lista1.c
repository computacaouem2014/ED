#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
float fat(int n){
	if(n==0 || n==1) return 1;
	else return n*fat(n-1);
}
void ex1(){
	int v1[10], v2[20];
	for(int k=0; k<10; k++){
		printf("v1[%i]: ", k); scanf("%i", &v1[k]);
	}
	for(int k=0; k<20; k++){
		printf("v2[%i]: ", k); scanf("%i", &v2[k]);
	}
	int size1=10, size2=20;
	for (int i=0; i<size1; i++)
      for (int j=i+1; j<size1;){
         if(v1[i]==v1[j]){               	 //Compara os elementos do mesmo vetor e transfere os repetidos
            for (int k=j; k<size1; k++){        // para o final do vetor
            	v1[k]=v1[k+1];
            }
            size1--;
         }else j++;
      }
	for (int i=0; i<size2; i++)
      for (int j=i+1; j<size2;){
         if(v2[i]==v2[j]){
            for (int k=j; k<size2; k++){
               v2[k]=v2[k+1];
            }
            size2--;
         }else j++;
      }
	for(int i=0; i<size1; i++)
		for(int j=0; j<size2; j++)
			if(v1[i]==v2[j])
				printf("O elemento %i aparece em ambas as listas.\n", v1[i]);
}
void ex2(){
	int v[10];
	float w[10];
	for(int k=0; k<10; k++){
		printf("v[%i]: ", k); scanf("%i", &v[k]);
	}
	for(int k=0; k<10; k++){
		w[k]=fat(v[k]);
		printf("w[%i]: %0.f\n", k, w[k]);	
	}
}
void ex3(){
	int a[10], b[10], dif[10];
	for(int k=0; k<10; k++){
		printf("A[%i]: ", k); scanf("%i", &a[k]);
	}
	for(int k=0; k<10; k++){
		printf("B[%i]: ", k); scanf("%i", &b[k]);
		dif[k]=a[k]-b[k];
	}
    printf("Vetor diferenca [");
    for (int k=0; k<10; k++)
   		printf(" %i ", dif[k]);
    printf("]\n");
 }
 void ex4(){
 	int mes_maior, mes_menor; 
 	float temp[12], min, max; 
 	for(int k=0; k<12; k++){
		printf("Digite, em graus celsius, a temperatura do mes %i: ", k+1); scanf("%f", &temp[k]);
	}
	min=temp[0]; max=temp[0];
	for(int k=0; k<12; k++){
		if(temp[k]>max){
			max=temp[k]; mes_maior=k+1;	
		}
		if(temp[k]<min){ 
			min=temp[k]; mes_menor=k+1;	
		}
	}
	for(int k=0; k<12; k++)
		printf("Temperatura mes %i: %2.f\n", k+1, temp[k]);
	printf("Menor temperatura: %2.f Mes: %i\n", min, mes_menor);
	printf("Maior temperatura: %2.f Mes: %i\n", max, mes_maior);

 }
 void ex5(){
 	int  maior, menor, v[10], par=0, soma=0;
 	float media;
 	for(int k=0; k<10; k++){
		printf("v[%i]: ", k); scanf("%i", &v[k]);
		soma+=v[k];
		if(v[k]%2==0) par++;
	}
	maior=v[0]; menor=v[0];
	for(int k=1; k<10; k++){
		if(v[k]>maior) maior=v[k];
		if(v[k]<menor) menor=v[k];
	}
	media=soma/10;
	printf("Maior elemento do vetor: %i\n", maior);
	printf("Menor elemento do vetor: %i\n", menor);
	printf("Porcentagem de elementos pares: %i%%\n", par*10);
	printf("Media dos elementos do vetor: %2.f\n", media);
 }
void ex6(){
	int num[12], lugares[12], opcao, nvoo;
	char origem[12][30], destino[12][30], str[30];
	for(int k=0; k<12; k++){
		printf("Digite o numero do voo %i: ", k+1); scanf("%i", &num[k]);
		printf("Digite a origem do voo %i: ", k+1); scanf("%s", &origem[k]);
		printf("Digite o destino do voo %i: ", k+1); scanf("%s", &destino[k]);
		printf("Digite a quantidade de lugares do voo %i: ", k+1); scanf("%i", &lugares[k]);
	}	
	do{
		printf("\tMENU\n");
		printf("(1) Consultar\n");
		printf("(2) Efetuar Reserva\n");
		printf("(0) Sair\n");
		printf("Operacao: "); scanf("%i", &opcao);
		if(opcao==1){
			int opcao2;
			do{
				printf("\t\nCONSULTA\n");
				printf("(1) Numero Voo\n");
				printf("(2) Origem\n");
				printf("(3) Destino\n");
				printf("(0) Sair\n");
				printf("Operacao: "); scanf("%i", &opcao2);
				if(opcao2==1){
					int i=0;												// a variavel i faz o controle para saber se existe ou não o voo pesquisado
					printf("Digite o numero do voo: "); scanf("%i", &nvoo);
					for(int k=0; k<12; k++)
						if(num[k]==nvoo){
							i++;
							printf("Numero: %i Origem: %s Destino: %s Lugares: %i\n", num[k], origem[k], destino[k], lugares[k]);
						}
					if(i==0) printf("Voo inexistente.\n");
				}else if(opcao2==2){
					int i=0;
					printf("Digite a origem do voo: "); scanf("%s", &str);
					for(int k=0; k<12; k++)
						if(!strcmp(origem[k], str)){ 
							i++;
							printf("Numero: %i Origem: %s Destino: %s Lugares: %i\n", num[k], origem[k], destino[k], lugares[k]);
						}
					if(i==0) printf("Voo inexistente.\n");
				}else if(opcao2==3){
					int i=0;
					printf("Digite o destino do voo: "); scanf("%s", &str);
					for(int k=0; k<12; k++)
						if(!strcmp(destino[k], str)){ 
							i++;
							printf("Numero: %i Origem: %s Destino: %s Lugares: %i\n", num[k], origem[k], destino[k], lugares[k]);
						}
					if(i==0) printf("Voo inexistente.\n");	
				}
			}while(opcao2!=0);
		}else if(opcao==2){
			int i=0;
			printf("Digite o numero do voo: "); scanf("%i", &nvoo);
			for(int k=0; k<12; k++)
				if(nvoo==num[k]){
					i++;
					if(lugares[k]==0) printf("Nao possuem lugares para este voo.\n");
					else printf("Reserva efetuada no voo: %i Origem: %s Destino: %s restando %i vagas.\n", num[k], origem[k], destino[k], lugares[k]-1);	
				}
			if(i==0) printf("Voo inexistente.\n");
		}
	}while(opcao!=0);
}
int main(){
	int ex;
	do{
		printf("Digite o numero do exercicio desejado (1-6 | 0 p/ sair): "); scanf("%i", &ex);
		while(ex<0 || ex>6){
			printf("Digite o numero do exercicio desejado (1-6 | 0 p/ sair): "); scanf("%i", &ex);	
		}
		switch(ex){
			case 1:
				//system("clear");
				ex1();
				break;
			case 2:
				//system("clear");
				ex2();
				break;
			case 3:
				//system("clear");
				ex3();
				break;
			case 4:
				//system("clear");
				ex4();
				break;
			case 5:
				//system("clear");
				ex5();
				break;
			case 6:
				//system("clear")
				ex6();
				break;
			default: break;
		}
	}while(ex!=0);
}
