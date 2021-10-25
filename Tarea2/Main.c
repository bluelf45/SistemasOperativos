#include "jugador.h"
#include "tablero.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include<sys/wait.h>
#include <unistd.h>

static const int NumCasillas = 28;
static const int DineroInicial = 100;

// INDICES
// 0 -> START
// 1, 2, 5, 16 y 18 -> +50
// 8, 11, 12, 22, 24 -> +75
// 3, 6, 20, 26 -> -25
// 9, 10, 19 -> -50
// 27 -> -75
// 15 -> FORWARD 3
// 23 -> FORWARD 5
// 4 -> BACK 2
// 13 -> BACK 3
// 17, 25 -> BACK 4
// 7, 21 -> JAIL
// 14 -> FREE
// 4procesos, 2 procesos cpu, 1 proceso jugador y 1 proceso mapa, procesos CPU y mapa esperan a que el usuario actue
void CrearTablero(tablero *tab){
	casilla Casilla;

	Casilla.id = 0;
	Casilla.valor = 0;
	//START y FREE
	tab->mapeo[0] = Casilla;
	tab->mapeo[14] = Casilla;

	//Casillas de suma/resta
	Casilla.id = 1;
	Casilla.valor = 50;
	tab->mapeo[1] = Casilla;
	tab->mapeo[2] = Casilla;
	tab->mapeo[5] = Casilla;
	tab->mapeo[16] = Casilla;
	tab->mapeo[18] = Casilla;

	Casilla.valor = 75;
	tab->mapeo[8] = Casilla;
	tab->mapeo[11] = Casilla;
	tab->mapeo[12] = Casilla;
	tab->mapeo[22] = Casilla;
	tab->mapeo[24] = Casilla;

	Casilla.valor = -25;
	tab->mapeo[3] = Casilla;
	tab->mapeo[6] = Casilla;
	tab->mapeo[20] = Casilla;
	tab->mapeo[26] = Casilla;

	Casilla.valor = -50;
	tab->mapeo[9] = Casilla;
	tab->mapeo[10] = Casilla;
	tab->mapeo[19] = Casilla;

	Casilla.valor = -75;
	tab->mapeo[27] = Casilla;

	//MOVIMIENTO
	//ADELANTE
	Casilla.id = 2;

	Casilla.valor = 3;
	tab->mapeo[15] = Casilla;

	Casilla.valor = 5;
	tab->mapeo[23] = Casilla;

	//RETROCEDER
	Casilla.id = 3;

	Casilla.valor = 2;
	tab->mapeo[4] = Casilla;

	Casilla.valor = 3;
	tab->mapeo[13] = Casilla;

	Casilla.valor = 4;
	tab->mapeo[17] = Casilla;
	tab->mapeo[25] = Casilla;

	Casilla.id = 4;
	Casilla.valor = 0;
	tab->mapeo[7] = Casilla;
	tab->mapeo[21] = Casilla;
}

void Movimiento(jugador *player, int valor){
	player->posicion += valor;
	if(player->posicion > 27){
		player->posicion = player->posicion % 28;
	}
}

int Dado(){
	int r = rand()%6 + 1;
	return r;
}

void dinero(jugador *player, int valor){
	player->dinero= player->dinero +valor;
}

void printTablero(){
	printf("|-------------------------------------------------------|\n");
	printf("| jail | +75  | -50  | -50  | +75  | +75  |Back 3| Free |\n");
	printf("| 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   |\n");
	printf("|------|-----------------------------------------|------|\n");
	printf("| -25  |                                         |Forw 3|\n");
	printf("| 6    |                                         | 15   |\n");
	printf("|------|                                         |------|\n");
	printf("| +50  |                                         | +50  |\n");
	printf("| 5    |                                         | 16   |\n");
	printf("|------|                                         |------|\n");
	printf("|Back 2|                                         |Back 4|\n");
	printf("| 4    |                                         | 17   |\n");
	printf("|------|                                         |------|\n");
	printf("| -25  |                                         | +50  |\n");
	printf("| 3    |                                         | 18   |\n");
	printf("|------|                                         |------|\n");
	printf("| +50  |                                         | -50  |\n");
	printf("| 2    |                                         | 19   |\n");
	printf("|------|                                         |------|\n");
	printf("| +50  |                                         | -25  |\n");
	printf("| 1    |                                         | 20   |\n");
	printf("|------|-----------------------------------------|------|\n");
	printf("| Start| -75  | -25  |Back 4| +75  |Forw 5| +75  | jail |\n");
	printf("| 0    | 27   | 26   | 25   | 24   | 23   | 22   | 21   |\n");
	printf("|-------------------------------------------------------|\n");
}

void initPlayer(jugador *player){
	player->dinero = 100;
	player->posicion = 0;
	player->jail = 0;
}

void AccionCasilla(tablero tab, jugador *player) {
	int valor;
	switch (tab.mapeo[player->posicion].id)
	{
		case 1://Suma o resta de dinero
			dinero(player, tab.mapeo[player->posicion].valor);
			printf("Caso 1\n");
			break;
		case 2://FORWARD
			Movimiento(player, tab.mapeo[player->posicion].valor);
			AccionCasilla(tab, player);
			printf("Caso 2\n");
			break;
		case 3://BACKWARD
			valor = tab.mapeo[player->posicion].valor * -1;
			Movimiento(player, valor);
			AccionCasilla(tab, player);
			printf("Caso 3\n");
			break;
		case 4://JAIL
			printf("Caso 4\n");
			break;
	}
}

void printplayers(jugador* players){
	for (int i =0; i < 3; i++){
		printf("Jugador %d -> Dinero: %d ; Casilla %d\n", i+1, players[i].dinero, players[i].posicion);
	}
}

int main(){
	tablero tab;
	tab.mapeo = malloc(sizeof(casilla)*28);
	CrearTablero(&tab);

	int msg = 0;
	int pipeph1[2], pipehp1[2];
	int pipeph2[2], pipehp2[2];
	int pipeph3[2], pipehp3[2];

	pipe(pipeph1);pipe(pipehp1);
	//pipe(pipeph2);pipe(pipehp2);
	//pipe(pipeph3);pipe(pipehp3);
	printf(">>>Bienvenido a Monopoly<<<\n");
	int flag = 1;
	int Proceso1 = fork();
	int Proceso2 = fork();
	if(Proceso1 == 0 && Proceso2 > 0){//Primer hijo (Tablero)
		jugador players[3];
		while(flag){
			while(read(pipeph1[0], &players, sizeof(players)*3) < 0){};
			printf("\n");
			//printTablero();
			//printplayers(players);
			write(pipehp1[1], &msg, sizeof(int));
			read(pipeph1[0], &flag, sizeof(int));
		}
		free(tab.mapeo);
		return 0;
	}

	else if(Proceso2 == 0 && Proceso1 == 0){//2do hijo
		/*srand(getpid());
		while(read(pipeph2[0], &flag, sizeof(flag))<0){};
		while(flag){
			if(read(pipeph2[0], &msg2, sizeof(msg2))>0){
				msg2=Dado();
				write(pipehp2[1], &msg2, sizeof(msg2));
				flag=0;
			}
		}*/
		free(tab.mapeo);
		return 0;
	}

	else if(Proceso2 == 0 && Proceso1 > 0){//3er Hijo
		/*srand(getpid());
		while(flag){
			if(read(pipeph3[0], &players, sizeof(jugador)*3)>0){
				msg=Dado();
				AccionCasilla(tab.mapeo[players[2].posicion], &players[2]);
				write(pipehp3[1], &msg, sizeof(msg));
				flag=0;
			}
		}*/
		free(tab.mapeo);
		return 0;
	}

	else if(Proceso2 > 0 && Proceso1 > 0){//Padre de todos
		jugador players[3];
		srand(getpid());

		initPlayer(&players[0]);
		initPlayer(&players[1]);
		initPlayer(&players[2]);
		write(pipeph1[1], &players, sizeof(players));
		char input[40];
		int dado;
		while(flag){
			while(read(pipehp1[0], &msg, sizeof(int))<0){};
			write(pipeph1[1], &players, sizeof(jugador)*3);
			dado = Dado();
			Movimiento(&players[0], dado);
			AccionCasilla(tab, &players[0]);
			printplayers(players);
			if(players[0].dinero >=500){
				flag=0;
				write(pipeph1[1], &flag, sizeof(int));
			}
		}
	}
	free(tab.mapeo);
	return 0;
}
