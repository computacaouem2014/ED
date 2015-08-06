#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

void clear(){
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
}

int clean_stdin(){
	while (getchar() != '\n') ;
	return 1;
}

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define FLAG 2

#define BOMBA -1
#define ZERO_AO_REDOR 0
#define UM_AO_REDOR 1
#define DOIS_AO_REDOR 2
#define TRES_AO_REDOR 3
#define QUATRO_AO_REDOR 4
#define CINCO_AO_REDOR 5
#define SEIS_AO_REDOR 6
#define SETE_AO_REDOR 7
#define OITO_AO_REDOR 8

#ifdef _WIN32
wchar_t box[12] = {L'-', L'|', L'/', L'\\', L'\\', L'/', L'}', L'{', L'T', L'L', L'+', L'P'};
#else
wchar_t box[12] = {L'═', L'║', L'╔', L'╗', L'╚', L'╝', L'╠', L'╣', L'╦', L'╩', L'╬', L'P'};
#endif

#define BOX_H 0
#define BOX_V 1
#define BOX_DR 2
#define BOX_DL 3
#define BOX_UR 4
#define BOX_UL 5
#define BOX_VR 6
#define BOX_VL 7
#define BOX_HD 8
#define BOX_HU 9
#define BOX_VH 10
#define BOX_FLAG 11

typedef struct campo {
	char tipo;
	char revelado;
} campo;

typedef struct vec2 {
	int x;
	int y;
} vec2;
typedef struct queue_elem queue_elem;

struct queue_elem {
	vec2 coord;
	queue_elem *next;
};

typedef struct coord_queue {
	queue_elem *first, *last;
} coord_queue;

void inicializa_queue(coord_queue *cq){
	cq->first = cq->last = NULL;
}

int is_empty(coord_queue *cq){
	return cq->first == NULL ? TRUE : FALSE;
}

void insere_queue(coord_queue *cq, int x, int y){
	queue_elem *elem = (queue_elem *) malloc(sizeof(queue_elem));
	elem->coord.x = x;
	elem->coord.y = y;
	if (is_empty(cq) == TRUE) cq->first = cq->last = elem;
	else {
		cq->last->next = elem;
		cq->last = elem;
	}
}

void remove_queue(coord_queue *cq, vec2 *v){
	if (is_empty(cq) == FALSE) {
		queue_elem *rem = cq->first;
		v->x = rem->coord.x;
		v->y = rem->coord.y;
		if (cq->first == cq->last) cq->first = cq->last = NULL;
		else cq->first = cq->first->next;
		free(rem);
	}
}

void print_queue(coord_queue *cq){
	wprintf(L"[ ");
	queue_elem *p = cq->first;
	while (p != NULL) {
		wprintf(L"{%d, %d} ", p->coord.x, p->coord.y);
		p = p->next;
	}
	wprintf(L"]\n");
}

int quant_bombas, revelar = FALSE;

int bounded(int min, int max, int who){
	return who >= min && who < max ? TRUE : FALSE;
}

void inicializa_jogo(int cm_a, int cm_l, campo cm[cm_a][cm_l]){
	revelar = FALSE;
	for (int i = 0; i < cm_a; i++) {
		for (int j = 0; j < cm_l; j++) {
			cm[i][j].tipo = ZERO_AO_REDOR;
			cm[i][j].revelado = FALSE;
		}
	}
	for (int i = 0; i < quant_bombas; i++) {
		int x = rand() % cm_a, y = rand() % cm_l;
		while (cm[x][y].tipo == BOMBA) {
			x = rand() % cm_a; y = rand() % cm_l;
		}
		cm[x][y].tipo = BOMBA;
		for (int i = -1; i < 2; i++){
			for (int j = -1; j < 2; j++){
				int a = x + i, b = y + j;
				if (bounded(0, cm_a, a) && bounded(0, cm_l, b) && cm[a][b].tipo != BOMBA){
					cm[a][b].tipo++;
				}
			}
		}
	}
}

void print_campo(int cm_a, int cm_l, campo cm[cm_a][cm_l], wchar_t *icon){
	wprintf(L"%ls%lc", icon, box[BOX_V]);
	for (int i = 0; i < cm_l; i++) {
		wprintf(L"%3d%lc", i+1, box[BOX_V]);
	}
	wprintf(L"\n%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_VH]);
	for (int i = 0; i < cm_l - 1; i++) {
		wprintf(L"%lc%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_VH]);
	}
	wprintf(L"%lc%lc%lc%lc\n", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_VL]);

	for (int i = 0; i < cm_a; i++) {
		wprintf(L"%2d%lc", i+1, box[BOX_V]);
		for (int j = 0; j < cm_l; j++) {
			if (cm[i][j].revelado == FALSE && revelar == FALSE) wprintf(L" %c %lc", ' ', box[BOX_V]);
			else if (cm[i][j].revelado == FLAG) wprintf(L" %c %lc", box[BOX_FLAG], box[BOX_V]);
			else {
				switch(cm[i][j].tipo) {
					case BOMBA: wprintf(L" %c %lc", '*', box[BOX_V]); break;
					case ZERO_AO_REDOR: wprintf(L" %c %lc", '0', box[BOX_V]); break;
					case UM_AO_REDOR: wprintf(L" %c %lc", '1', box[BOX_V]); break;
					case DOIS_AO_REDOR: wprintf(L" %c %lc", '2', box[BOX_V]); break;
					case TRES_AO_REDOR: wprintf(L" %c %lc", '3', box[BOX_V]); break;
					case QUATRO_AO_REDOR: wprintf(L" %c %lc", '4', box[BOX_V]); break;
					case CINCO_AO_REDOR: wprintf(L" %c %lc", '5', box[BOX_V]); break;
					case SEIS_AO_REDOR: wprintf(L" %c %lc", '6', box[BOX_V]); break;
					case SETE_AO_REDOR: wprintf(L" %c %lc", '7', box[BOX_V]); break;
					case OITO_AO_REDOR: wprintf(L" %c %lc", '8', box[BOX_V]); break;
					default: wprintf(L"? "); break;
				}
			}
		}

		if (i != cm_a - 1) {
			wprintf(L"\n%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_VH]);
			for (int i = 0; i < cm_l - 1; i++) {
				wprintf(L"%lc%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_VH]);
			}
			wprintf(L"%lc%lc%lc%lc\n", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_VL]);
		}
	}
	wprintf(L"\n%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_HU]);
	for (int i = 0; i < cm_l - 1; i++) {
		wprintf(L"%lc%lc%lc%lc", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_HU]);
	}
	wprintf(L"%lc%lc%lc%lc\n", box[BOX_H], box[BOX_H], box[BOX_H], box[BOX_UL]);
}

int checar_fim_de_jogo(int cm_a, int cm_l, campo cm[cm_a][cm_l]){
	int marcados = 0;
	int todos_revelados = TRUE;
	for (int i = 0; i < cm_a; i++) {
		for (int j = 0; j < cm_l; j++) {
			if (cm[i][j].tipo == BOMBA && cm[i][j].revelado == FLAG) marcados++;
			else if (cm[i][j].tipo != BOMBA && cm[i][j].revelado == FALSE) todos_revelados = FALSE;
		}
	}
	return marcados == quant_bombas || todos_revelados == TRUE ? TRUE : FALSE;
}

int valid_command(char cmd[5]){
	return strcmp(cmd, "walk") == 0 || strcmp(cmd, "flag") == 0 ? TRUE : FALSE;
}

int main(){
	srand(time(NULL));
	setlocale(LC_ALL, "");
	clear();
	int jogando = TRUE, opcao = -1;
	while (jogando == TRUE) {
		wprintf(L"Opcoes:\n");
		wprintf(L"1.Iniciar Novo Jogo\n");
		wprintf(L"2.Como Jogar\n");
		wprintf(L"3.Sair\n");
		do {
			wprintf(L"O que deseja fazer?\n> ");
		} while (scanf("%d", &opcao) != 1 && clean_stdin());
		switch(opcao) {
			case 1: {
				int altura = -1, largura = -1, x = -1, y = -1;
				quant_bombas = -1;
				do {
					wprintf(L"Qual a altura do campo minado? [3~16]\n> ");
				} while((scanf("%d", &altura) != 1 && clean_stdin()) || bounded(3, 17, altura) == FALSE);
				do {
					wprintf(L"Qual a largura do campo minado? [3~16]\n> ");
				} while((scanf("%d", &largura) != 1 && clean_stdin()) || bounded(3, 17, altura) == FALSE);
				do {
					wprintf(L"Quantas bombas deseja colocar no campo minado? [1~%d]\n> ", (altura * largura));
				} while((scanf("%d", &quant_bombas) != 1 && clean_stdin()) || bounded(1, (altura * largura), quant_bombas) == FALSE);
				clear();
				campo campo_minado[altura][largura];
				inicializa_jogo(altura, largura, campo_minado);
				print_campo(altura, largura, campo_minado, L":)");
				while (jogando == TRUE) {
					x = y = -1;
					char command[5];
					do {
						wprintf(L"Digite \"walk x y\" para revelar ou \"flag x y\" para (des)marcar:\n> ");
					} while ((scanf("%4s %d %d", command, &x, &y) != 3 && clean_stdin()) || valid_command(command) == FALSE || bounded(1, altura + 1, x) == FALSE || bounded(1, largura + 1, y) == FALSE);
					x--; y--;
					if (strcmp(command, "walk") == 0) {
						if (campo_minado[x][y].revelado == FLAG) {
							wprintf(L"O campo selecionado esta marcado, desmarque-o antes de revelar.\n");
							continue;
						} else if (campo_minado[x][y].revelado == TRUE) {
							wprintf(L"O campo selecionado ja foi revelado.");
							continue;
						} else {
							if (campo_minado[x][y].tipo == BOMBA) {
								clear();
								revelar = TRUE;
								print_campo(altura, largura, campo_minado, L":(");
								wprintf(L"Voce perdeu! :(\nBoa sorte na proxima vez.\n\n");
								break;
							} else {
								coord_queue cq;
								inicializa_queue(&cq);
								campo_minado[x][y].revelado = TRUE;
								if (campo_minado[x][y].tipo == ZERO_AO_REDOR) insere_queue(&cq, x, y);
								while (is_empty(&cq) == FALSE) {
									vec2 v;
									remove_queue(&cq, &v);
									for (int i = -1; i < 2; i++){
										for (int j = -1; j < 2; j++){
											int a = v.x + i, b = v.y + j;
											if (bounded(0, altura, a) && bounded(0, largura, b) && campo_minado[a][b].revelado == FALSE && campo_minado[a][b].tipo != BOMBA){
												campo_minado[a][b].revelado = TRUE;
												if (campo_minado[a][b].tipo == ZERO_AO_REDOR) insere_queue(&cq, a, b);
											}
										}
									}
								}
							}
						}
					} else if (strcmp(command, "flag") == 0) {
						if (campo_minado[x][y].revelado == FALSE){
							campo_minado[x][y].revelado = FLAG;
						} else if (campo_minado[x][y].revelado == FLAG){
							campo_minado[x][y].revelado = FALSE;
						} else {
							wprintf(L"O campo selecionado já foi revelado.");
							continue;
						}
					}
					if (checar_fim_de_jogo(altura, largura, campo_minado) == TRUE) {
						clear();
						revelar = TRUE;
						print_campo(altura, largura, campo_minado, L"8)");
						wprintf(L"Parabéns você ganhou!\n\n");
						break;
					} else {
						clear();
						print_campo(altura, largura, campo_minado, L":)");
					}
				}
				break;
			}
			case 2: {
				clear();
				wprintf(L"Como jogar:\n");
				wprintf(L"Escolha o tamanho do campo minado.\n");
				wprintf(L"Escolha o numero de bombas que serao aleatoriamente distribuidas no campo.\n");
				wprintf(L"Digite 'walk x y' para revelar a coordenada (x,y) no campo ou 'flag x y' para marcar a coordenada (x,y) como uma bomba.\n");
				wprintf(L"Se voce pisar (comando 'walk') num campo com bomba voce perde.\n");
				wprintf(L"Voce ganha se conseguir marcar (comando: 'mark') todos os campos que possuem bombas.\n");
				wprintf(L"Ou se conseguir pisar (comando: 'walk') em todos os campos que nao possuem bombas.\n");
				wprintf(L"Para jogar selecione a opção 1 no menu principal.\n");
				wprintf(L"Boa sorte!\n\n");
				break;
			}
			case 3: jogando = FALSE; break;
			default:
			clear();
			wprintf(L"Opção invalida. Por favor tente novamente.\n");
			break;
		}
	}
	wprintf(L"Ate a proxima!\n");
	return 0;
}
