#include "Tablero.h"
#include <iostream>
#include<array>
#include <cstdlib>
#include <ctime>
using namespace std;

Tablero::Tablero() 
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 30; i++) {
		Tablero_r[i] = "N";
	}

	int posicionS, posicionEscalera;
	posicionS = 0;
	posicionEscalera = 0;


	for (int i = 0; i < 3; i++)
	{

			posicionS = rand() % 30;

			while (Tablero_r[posicionS] != "N")
			{
				posicionS = rand() % 30;
			}

			Tablero_r[posicionS] = "S";

		
			posicionEscalera = rand() % 30;

			while (Tablero_r[posicionEscalera] != "N")
			{
				posicionEscalera = rand() % 30;;
			}

			Tablero_r[posicionEscalera] = "L";
			
	}
}

array<string, 30> Tablero::getTablero(){
	return Tablero_r;
}