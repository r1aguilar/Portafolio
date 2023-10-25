#include "Jugador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Jugador::Jugador() {

}

Jugador::Jugador(int numJugador_r) 
{
	casilla_actual = 1;
	numJugador = numJugador_r;
}

int Jugador::avanza(int tiro_dado)
{
	int casilla_nueva;
	/*srand((unsigned int)time(NULL));
	int tiro_dado = (rand() % 6 + 1);
	cout << tiro_dado << endl;*/
	casilla_nueva = tiro_dado + casilla_actual;
	avance = tiro_dado;


	return casilla_nueva;
}

int Jugador::getCasilla()
{
	return casilla_actual;
}

int Jugador::getNumero()
{
	return numJugador;
}

int Jugador::getAvance()
{
	return avance;
}

void Jugador::setCasilla(int casilla_r)
{
	casilla_actual = casilla_r;
}