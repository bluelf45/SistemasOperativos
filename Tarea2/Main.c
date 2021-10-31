#include "jugador.h"
#include "tablero.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include<sys/wait.h>
#include <unistd.h>


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

/*
	void CrearTablero(tablero *tab)
	Crea el tablero de Monopoly.
*/
void CrearTablero(tablero *tab){
	casilla Casilla;

	Casilla.id = 0;
	Casilla.valor = 100;
	//START y FREE
	tab->mapeo[0] = Casilla;

	Casilla.id = 5;
	Casilla.valor = 0;
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

/*
	void Movimiento(jugador *player, int valor)
	Funcion que se usa para modificar la posicion del jugador, tambien aumenta el dinero si pasa por la casilla 0.
*/
void Movimiento(jugador *player, int valor){
	player->posicion += valor;
	if(player->posicion > 27){
		player->posicion = player->posicion % 28;
		player->dinero += 100;
	}
}
/*
	void printTablero()
	Imprime el tablero
*/
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
/*
	void initPlayer(jugador *player)
	inicia el jugador con los valores iniciales
*/
void initPlayer(jugador *player){
	player->dinero = 100;
	player->posicion = 0;
	player->jail = 0;
}
/*
	int Dado()
	retorna un numero aleatorio entre 1 al 6
*/
int Dado(){
	int r = rand()%6 + 1;
	return r;
}

/*
	void dinero(jugador *player, int valor)
	modifica el dinero del jugador
*/
void dinero(jugador *player, int valor){
	player->dinero= player->dinero +valor;
}
/*
	void AccionCasilla(tablero tab, jugador *player)
	Funcion que aplica la casilla, o sea, ejecuta la casilla y llama a diferentes funciones auxiliares para su correcto funcionamiento
*/
void AccionCasilla(tablero tab, jugador *player) {
	int valor;
	switch (tab.mapeo[player->posicion].id)
	{
		case 1://Suma o resta de dinero
			dinero(player, tab.mapeo[player->posicion].valor);
			break;
		case 2://FORWARD
			Movimiento(player, tab.mapeo[player->posicion].valor);
			AccionCasilla(tab, player);
			break;
		case 3://BACKWARD
			valor = tab.mapeo[player->posicion].valor * -1;
			Movimiento(player, valor);
			AccionCasilla(tab, player);
			break;
		case 4://JAIL
			player->jail = 1;
			break;
	}
}
/*
	void printplayer(jugador player, int i)
	imprime el jugador y su inventario
*/
void printplayer(jugador player, int i){
	printf("Jugador %d -> Dinero: %d ; Casilla %d\n", i, player.dinero, player.posicion);
}

int main(){
	tablero tab;
	tab.mapeo = malloc(sizeof(casilla)*28);
	CrearTablero(&tab);
	
	jugador jugador1;
	jugador jugador2;
	jugador jugador3;
	
	initPlayer(&jugador1);
	initPlayer(&jugador2);
	initPlayer(&jugador3);

	int pipeph1[2], pipehp1[2];
	int pipeph2[2], pipehp2[2];
	int pipeph3[2], pipehp3[2];

	pipe(pipeph1);pipe(pipehp1);
	pipe(pipeph2);pipe(pipehp2);
	pipe(pipeph3);pipe(pipehp3);

	int Proceso1 = fork();
	int Proceso2 = fork();

	if(Proceso1 == 0 && Proceso2 > 0){//Primer hijo (Tablero)
		int flag = 1;
		while (flag){
			printTablero();
			write(pipehp1[1], &flag, sizeof(int));
			while(read(pipeph1[0], &flag, sizeof(int))<0){};
		}
	}

	else if(Proceso2 > 0 && Proceso1 > 0){//Player proceso padre pipe1
		srand(getpid());
		int flag = 1;
		char input[50];
		int dado;
		while(flag){
			while(read(pipehp1[0], &flag, sizeof(int))<0){};
			printplayer(jugador1, 1);
			printf(">>>Escriba para tirar el dado<<<\n");
			scanf("%s",input);
			if(jugador1.jail==0){
				dado = Dado();
				printf(">>> Jugador 1 tiro un %d<<<\n", dado);
				Movimiento(&jugador1, dado);
				AccionCasilla(tab, &jugador1);
			}
			else if(jugador1.jail==1){
				jugador1.jail = 0;
				printf("Jugador1 en prision, pierde su turno\n");
			}
			if(jugador1.dinero >=500){
				flag = 0;
				printf("Gana jugador 1\n");
			}
			write(pipeph2[1], &flag, sizeof(int));
			while(read(pipehp2[0], &flag, sizeof(int))<0){};
			write(pipeph3[1], &flag, sizeof(int));
			while(read(pipehp3[0], &flag, sizeof(int))<0){};
			printf(">>>Escriba para pasar a la siguiente ronda<<<\n");
			scanf("%s",input);
			write(pipeph1[1], &flag, sizeof(int));
		}
		printf("\n>>>PUNTAJES FINALES<<<\n");
		printplayer(jugador1, 1);

		write(pipeph2[1], &flag, sizeof(int));
		while(read(pipehp2[0], &flag, sizeof(int))<0){};
		write(pipeph3[1], &flag, sizeof(int));
		while(read(pipehp3[0], &flag, sizeof(int))<0){};
		return 0;	
	}

	else if(Proceso2 == 0 && Proceso1 > 0){//CPU2 pipe2
		srand(getpid());
		int flag = 1;
		int dado;
		while(flag){
			while(read(pipeph2[0], &flag, sizeof(int))<0){};
			printplayer(jugador2, 2);
			if(jugador2.jail==0){
				dado = Dado();
				printf(">>> Jugador 2 tiro un %d<<<\n", dado);
				Movimiento(&jugador2, dado);
				AccionCasilla(tab, &jugador2);
			}
			else if(jugador2.jail==1){
				jugador2.jail = 0;
				printf("Jugador2 en prision, pierde su turno\n");
			}
			if(jugador2.dinero >=500){
				flag = 0;
				printf("Gana jugador 2\n");
			}
			write(pipehp2[1], &flag, sizeof(int));
		}
		while(read(pipeph2[0], &flag, sizeof(int))<0){};
		write(pipehp2[1], &flag, sizeof(int));
		printplayer(jugador2, 2);
		
	}

	else if(Proceso2 == 0 && Proceso1 == 0){//CPU1  pipe3
		srand(getpid());
		int flag = 1;
		int dado;
		while(flag){
			while(read(pipeph3[0], &flag, sizeof(int))<0){};
			printplayer(jugador3, 3);
			if(jugador3.jail==0){
				dado = Dado();
				printf(">>> Jugador 3 tiro un %d<<<\n", dado);
				Movimiento(&jugador3, dado);
				AccionCasilla(tab, &jugador3);
			}
			else if(jugador3.jail == 1){
				jugador3.jail = 0;
				printf("Jugador3 en prision, pierde su turno\n");
			}
			if(jugador3.dinero >=500){
				flag = 0;
				printf("Gana jugador 3\n");
			}
			write(pipehp3[1], &flag, sizeof(int));
		}
		while(read(pipeph3[0], &flag, sizeof(int))<0){};
		write(pipehp3[1], &flag, sizeof(int));
		printplayer(jugador3, 3);
	}
	free(tab.mapeo);
	return 0;
}
