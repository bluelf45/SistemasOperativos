typedef struct {
	int id; //Tipo de casilla 0-> start/free, 1 -> Suma, 2-> mover, 3 -> Jail
	int valor; //valor de la casilla, en caso de agregar dinero o de mover al pj
}casilla;

typedef struct {
	casilla* mapeo
}tablero;
