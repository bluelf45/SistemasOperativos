typedef struct {
	int id; //Tipo de casilla 0-> start/free, 1 -> Suma/Resta, 2-> mover adelante, 3 -> mover atras, 4 -> Jail
	int valor; //valor de la casilla, en caso de agregar dinero o de mover al pj
}casilla;

typedef struct {
	casilla* mapeo;
}tablero;
