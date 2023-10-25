#pragma once
#include <iostream>
#include <array>
using namespace std;

class Tablero {
protected:
	array<string, 30> Tablero_r;

public:
	Tablero();
	array<string, 30> getTablero();
};