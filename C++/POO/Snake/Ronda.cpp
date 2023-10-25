#include "Ronda.h"
#include "Jugador.h"
#include <fstream>
#include <iostream>

Ronda::Ronda(int ronda_r, int numJugador_r, int casilla_r, int avance_r, string letra_r, int casilla_f) 
{
	numRonda = ronda_r;

	numJugador = numJugador_r;

	casilla_actual = casilla_r;

	avance_ronda = avance_r;

	letra_actual = letra_r;

	casilla_final = casilla_f;
	
}

void Ronda::muestraRonda()
{
	cout << numRonda;
	cout << " ";
	cout << numJugador;
	cout << " ";
	cout << casilla_actual;
	cout << " ";
	cout << avance_ronda;
	cout << " ";
	cout << letra_actual;
	cout << " ";
	if (casilla_final > 30)
	{
		cout << 30;
		cout << " ";
	}
	else
	{
		cout << casilla_final;
		cout << " ";
	}
	cout << endl;
}

void Ronda::imprimeRonda(string salida)
{
	fstream outfile;

	outfile.open(salida, ios::app);

	if (outfile.is_open())
	{
		outfile << numRonda;
		outfile << " ";
		outfile << numJugador;
		outfile << " ";
		outfile << casilla_actual;
		outfile << " ";
		outfile << avance_ronda;
		outfile << " ";
		outfile << letra_actual;
		outfile << " ";
		if (casilla_final > 30)
		{
			outfile << 30;
			outfile << " ";
		}
		else
		{
			outfile << casilla_final;
			outfile << " ";
		}
		outfile << endl;

		outfile.close();

	}
	
}