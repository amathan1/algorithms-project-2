#include <cstdlib>
#include <iostream>
#include <array>
#include <assert.h>
#include <math.h>

using namespace std;


class 
Tromino
{

public:
	Tromino(int k, int r, int c) {this->k = k; this->r = r; this->c = c; this->num = 2*k;}

	int trominoTile();

	int buildTromino(int, int, int, int, int, int);

	int buildParams(array <int, 24>&, int, int, int, int, int, int);

	int printTromino();


private:
	int k, r, c, num;	// Parameters
	int **tiles;		// Tromino board
	int cnt = 1;		// Counter variable

};