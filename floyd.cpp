#include "floyd.hpp"


int 
Floyd::updateMatrix(vector<string> &content)
{

	this->dist = (int**)malloc(this->numNodes * sizeof(int*));
	this->path = (int***)malloc(this->numNodes * sizeof(int*));
	for (int i = 0; i < this->numNodes; i++)	this->dist[i] = (int*)calloc(this->numNodes, sizeof(int));
	for (int i = 0; i < this->numNodes; i++)	this->path[i] = (int**)malloc(this->numNodes * sizeof(int*));
	for (int i = 0; i < this->numNodes; i++) {
		for (int j = 0; j < this->numNodes; j++) {
			path[i][j] = (int*)calloc(1, sizeof(int));
		}
	}




}	


int 
Floyd::readFile()
{

	string line;
	vector<string> wholeCsv;
	ifstream matrixFile;
	matrixFile.open(this->fileName);
	if (!matrixFile) {cerr << "[Error]: Unable to read file"; exit(1);}
	
	while (!matrixFile.eof())
	{
		getline(matrixFile, line);
		wholeCsv.push_back(line);
		this->numNodes++;
	}

	updateMatrix(wholeCsv);
	return 0;
}





int
main()
{

	// So far so good! Papaam paaaaaammmm


	return 0;
}