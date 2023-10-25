#pragma once
#include <iostream>

class Jugador {
protected:
	int numJugador;
	int casilla_actual;
	int avance;

public:
	Jugador();
	Jugador(int);
	int avanza(int);
	int getAvance();
	int getCasilla();
	int getNumero();
	void setCasilla(int);
};

