#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class
Floyd
{

public:
	Floyd(string fileName) {this->fileName = fileName;}

	int findShortestPaths();

	int recursiveHelper();

	int readFile();

	int updateMatrix(vector<string>&);

private:
	int numNodes = 0;
	string fileName;
	int **dist;
	int ***path;

};