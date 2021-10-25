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
void CrearTablero(tablero tab){
	casilla Casilla;

	Casilla.id = 0;
	Casilla.valor = 0;
	//START y FREE
	tab.mapeo[0] = Casilla;
	tab.mapeo[14] = Casilla;

	//Casillas de suma/resta
	Casilla.id = 1;
	Casilla.valor = 50;
	tab.mapeo[1] = Casilla;
	tab.mapeo[2] = Casilla;
	tab.mapeo[5] = Casilla;
	tab.mapeo[16] = Casilla;
	tab.mapeo[18] = Casilla;

	Casilla.valor = 75;
	tab.mapeo[8] = Casilla;
	tab.mapeo[11] = Casilla;
	tab.mapeo[12] = Casilla;
	tab.mapeo[22] = Casilla;
	tab.mapeo[24] = Casilla;

	Casilla.valor = -25;
	tab.mapeo[3] = Casilla;
	tab.mapeo[6] = Casilla;
	tab.mapeo[20] = Casilla;
	tab.mapeo[26] = Casilla;

	Casilla.valor = -50;
	tab.mapeo[9] = Casilla;
	tab.mapeo[10] = Casilla;
	tab.mapeo[19] = Casilla;

	Casilla.valor = -75;
	tab.mapeo[27] = Casilla;

	//MOVIMIENTO
	//ADELANTE
	Casilla.id = 2;

	Casilla.valor = 3;
	tab.mapeo[15] = Casilla;

	Casilla.valor = 5;
	tab.mapeo[23] = Casilla;

	//RETROCEDER
	Casilla.id = 3;

	Casilla.valor = 2;
	tab.mapeo[4] = Casilla;

	Casilla.valor = 3;
	tab.mapeo[13] = Casilla;

	Casilla.valor = 4;
	tab.mapeo[17] = Casilla;
	tab.mapeo[25] = Casilla;

	Casilla.id = 4;
	Casilla.valor = 0;
	tab.mapeo[7] = Casilla;
	tab.mapeo[21] = Casilla;
}

void Movimiento(jugador player, int valor){
	player.posicion += valor;
	if(player.posicion > 27){
		player.posicion = player.posicion % 28;
	}
}

int Dado(){
	int r = rand()%6 + 1;
	return r;
}

void dinero(jugador player, int valor){
	player.dinero+=valor;
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

int main(){
	int msg1, msg2, msg3;
	int pipeph1[2], pipehp1[2];
	int pipeph2[2], pipehp2[2];
	int pipeph3[2], pipehp3[2];
	pipe(pipeph1);pipe(pipehp1);
	pipe(pipeph2);pipe(pipehp2);
	pipe(pipeph3);pipe(pipehp3);

	int Proceso1 = fork();
	int Proceso2 = fork();
	if(Proceso1 == 0 && Proceso2 > 0){//Primer hijo (Tablero)
		srand(getpid());
		int flag=1;
		while(flag){
			if(read(pipeph1[0], &msg1, sizeof(msg1))>0){
				msg1=Dado();
				write(pipehp1[1], &msg1, sizeof(msg1));
				flag=0;
			}
		}
	}
	else if(Proceso2 == 0 && Proceso1 == 0){//2do hijo (CPU)
		srand(getpid());
		int flag = 1;
		while(flag){
			if(read(pipeph2[0], &msg2, sizeof(msg2))>0){
				msg2=Dado();
				write(pipehp2[1], &msg2, sizeof(msg2));
				flag=0;
			}
		}
	}
	else if(Proceso2 == 0 && Proceso1 > 0){//3er Hijo (CPU)
		srand(getpid());
		int flag = 1;
		while(flag){
			if(read(pipeph3[0], &msg3, sizeof(msg3))>0){
				msg3=Dado();
				write(pipehp3[1], &msg3, sizeof(msg3));
				flag=0;
			}
		}
	}
	else if(Proceso2 > 0 && Proceso1 > 0){//Padre de todos (Jugador)
		write(pipeph1[1], &msg1, sizeof(int));
		while(read(pipehp1[0], &msg1, sizeof(msg1))<0){};
		printf("Dado 1 ->%d\n", msg1);
		write(pipeph2[1], &msg2, sizeof(int));

		while(read(pipehp2[0], &msg2, sizeof(msg2))<0){};
		printf("Dado 2 ->%d\n", msg2);
		write(pipeph3[1], &msg3, sizeof(int));

		while(read(pipehp3[0], &msg3, sizeof(msg3))<0){};
		printf("Dado 3 ->%d\n", msg3);
		printf("Padre\n");
	}
	return 0;
}
