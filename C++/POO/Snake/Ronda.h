#pragma once
#include "Jugador.h"
#include <fstream>
#include <iostream>
using namespace std;

class Ronda: protected Jugador {
protected:
	int numRonda;
	int avance_ronda;
	string letra_actual;
	int casilla_final;


public:
	Ronda(int, int, int, int, string, int);
	void muestraRonda();
	void imprimeRonda(string);
};
