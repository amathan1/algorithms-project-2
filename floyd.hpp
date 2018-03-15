#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;


class
Floyd
{

public:
	Floyd(string fileName) {this->fileName = fileName;}

	int findShortestPaths();

	int printMatrices();

	int readFile();

	int updateMatrix(vector<string>&);

private:
	int numNodes = 0;
	string fileName;
	int **dist;
	vector< vector< vector<int> > > path;
};