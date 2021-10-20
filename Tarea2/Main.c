#include "jugador.h"
#include "tablero.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

static const int NumCasillas = 28;
static const int DineroInicial = 100;

// INDICES
// 0 -> START
// 1, 2, 5, 16 y 18 -> +50
// 8, 11, 12, 22, 24 -> +75
// 3, 6, 20, 26 -> -25
// 9, 10, 19 -> -50
// 27 -> -75
// 4 -> BACK 2
// 13 -> BACK 3
// 17, 25 -> BACK 4
// 15 -> FORWARD 3
// 23 -> FORWARD 5
// 7, 21 -> JAIL
// 14 -> FREE

tablero CrearTablero{
	tablero tab;
	tab.mapeo = malloc(28*sizeof(casilla));
	casilla suma;
	suma.id = 1;
	suma.valor = 50;
	
}

int main(){
	return 0;
}
