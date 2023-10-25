#pragma once
#include <iostream>
#include "Ronda.h"
#include "Jugador.h"
#include "Tablero.h"
#include <iostream>
#include <vector> 
#include <fstream>
#include <sstream>

inline void borrar_contenido(string salida)
{
	fstream file(salida, ios::out);
	file << "";
}

class MyGame 
{
public:
	MyGame();
	void start(string nombre, string salida)
	{
		fstream outfile;
		outfile.open(salida, ios::out | ios::app);
		borrar_contenido(salida);

		if (outfile.is_open())
		{
			string letra;

			do
			{
				if (letra.empty() == true)
				{
					cout << "Press C to continue next turn, or E to end the game: ";
					cin >> letra;

					outfile << "Press C to continue next turn, or E to end the game: ";
					outfile << letra;
					outfile << endl;
				}

				else if (letra != "C" && letra != "E") {
					cout << "Invalid option, please press C to continue next turn or E to end the game... ";
					cin >> letra;

					outfile << "Invalid option, please press C to continue next turn or E to end the game... ";
					outfile << letra;
					outfile << endl;
				}

			} while (letra != "C" && letra != "E");

			cout << endl;
			outfile << endl;

			// Inicializar el vector de string para guardar fracciones e imprimirlas
			vector<string> turnos;
			int acum_turnos = 0;

			// Obtener las lineas del txt
			fstream newfile;
			newfile.open(nombre, ios::in);

			if (newfile.is_open()) { //revisar si el archivo esta abierto
				string linea;

				while (getline(newfile, linea)) //leer del archivo linea por linea
				{
					turnos.push_back(linea);
					acum_turnos++;
				}
				newfile.close(); //cerrar el archivo
			}

			Jugador jugador1(1), jugador2(2);
			Tablero tablero;
			array<string, 30> tablero_del_juego = tablero.getTablero();

			int acum_ronda = 1;
			int numero_jugador;
			int casilla_actual_1;
			int casilla_actual_2;
			int casilla_nueva_1;
			int casilla_nueva_2;
			int avance_r_1;
			int avance_r_2;
			int tiro_dado_1;
			int tiro_dado_2;
			bool ganador = false;
			string letra_casilla_nueva;

			srand(time(0));


			for (int i = 0; i < acum_turnos; i++)
			{
				letra = turnos[i];

				if (letra == "E" && (jugador1.getCasilla() <= 30 && jugador2.getCasilla() <= 30))
				{
					cout << endl;
					cout << "-- GAME OVER --" << endl;
					cout << "Thanks for playing!!!" << endl;

					outfile << endl;
					outfile << "-- GAME OVER --" << endl;
					outfile << "Thanks for playing!!!" << endl;

					break;
				}

				else if (letra == "C")
				{
					if (jugador1.getCasilla() >= 30 || jugador2.getCasilla() >= 30)
					{
						if (jugador1.getCasilla() >= 30)
						{
							cout << endl;
							cout << "-- GAME OVER --" << endl;
							cout << "Player 1 is the winner!!!" << endl;

							
							outfile << endl;
							outfile << "-- GAME OVER --" << endl;
							outfile << "Player 1 is the winner!!!" << endl;

							ganador = true;
							break;
						}
						else
						{
							cout << endl;
							cout << "-- GAME OVER --" << endl;
							cout << "Player 2 is the winner!!!" << endl;

			
							outfile << endl;
							outfile << "-- GAME OVER --" << endl;
							outfile << "Player 2 is the winner!!!" << endl;

							ganador = true;
							break;
						}
					}

					if (acum_ronda % 2 == 0) {
						numero_jugador = jugador2.getNumero();
						casilla_actual_2 = jugador2.getCasilla();
						tiro_dado_2 = (rand() % 6 + 1);
						casilla_nueva_2 = jugador2.avanza(tiro_dado_2);
						avance_r_2 = jugador2.getAvance();

						if (casilla_nueva_2 >= 30)
						{
							letra_casilla_nueva = tablero_del_juego[29];
						}

						if (tablero_del_juego[casilla_nueva_2 - 1] == "L")
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_2 - 1];
							casilla_nueva_2 = casilla_nueva_2 + 3;

						}
						else if (tablero_del_juego[casilla_nueva_2 - 1] == "S")
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_2 - 1];
							casilla_nueva_2 = casilla_nueva_2 - 3;
							if (casilla_nueva_2 <= 0)
							{
								casilla_nueva_2 = 1;
							}

						}
						else
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_2 - 1];
						}

						Ronda ronda(acum_ronda, numero_jugador, casilla_actual_2, avance_r_2, letra_casilla_nueva, casilla_nueva_2);
						ronda.muestraRonda();
						ronda.imprimeRonda(salida);

						jugador2.setCasilla(casilla_nueva_2);
					}

					else
					{
						numero_jugador = jugador1.getNumero();
						casilla_actual_1 = jugador1.getCasilla();
						tiro_dado_1 = (rand() % 6 + 1);
						casilla_nueva_1 = jugador1.avanza(tiro_dado_1);
						avance_r_1 = jugador1.getAvance();

						if (casilla_nueva_1 >= 30)
						{
							letra_casilla_nueva = tablero_del_juego[29];
						}

						else if (tablero_del_juego[casilla_nueva_1 - 1] == "L")
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_1 - 1];
							casilla_nueva_1 = casilla_nueva_1 + 3;

						}

						else if (tablero_del_juego[casilla_nueva_1 - 1] == "S")
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_1 - 1];
							casilla_nueva_1 = casilla_nueva_1 - 3;
							if (casilla_nueva_1 <= 0)
							{
								casilla_nueva_1 = 1;
							}

						}

						else
						{
							letra_casilla_nueva = tablero_del_juego[casilla_nueva_1 - 1];

						}

						Ronda ronda(acum_ronda, numero_jugador, casilla_actual_1, avance_r_1, letra_casilla_nueva, casilla_nueva_1);
						ronda.muestraRonda();
						ronda.imprimeRonda(salida);

						jugador1.setCasilla(casilla_nueva_1);
					}

					acum_ronda++;
				}

			}

			if (jugador1.getCasilla() < 30 && jugador2.getCasilla() < 30 && letra != "E")
			{
				cout << endl;
				cout << "The maximum number of turns has been reached..." << endl;

				
				outfile << endl;
				outfile << "The maximum number of turns has been reached..." << endl;
			}

			else
			{
				if (jugador1.getCasilla() >= 30 && ganador == false)
				{
					cout << endl;
					cout << "-- GAME OVER --" << endl;
					cout << "Player 1 is the winner!!!" << endl;

					
					outfile << endl;
					outfile << "-- GAME OVER --" << endl;
					outfile << "Player 1 is the winner!!!" << endl;

				}
				else if (jugador2.getCasilla() >= 30 && ganador == false)
				{
					cout << endl;
					cout << "-- GAME OVER --" << endl;
					cout << "Player 2 is the winner!!!" << endl;

					
					outfile << endl;
					outfile << "-- GAME OVER --" << endl;
					outfile << "Player 2 is the winner!!!" << endl;

				}
			}
			outfile.close();
		}
	}
		

		
};
