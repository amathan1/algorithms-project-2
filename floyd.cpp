#include "floyd.hpp"


int 
Floyd::updateMatrix(vector<string> &content)
{

	this->dist = (int**)malloc(this->numNodes * sizeof(int*));

	for (int i = 0; i < this->numNodes; i++)	this->dist[i] = (int*)calloc(this->numNodes, sizeof(int));
	this->path.resize(this->numNodes, vector< vector <int> >(this->numNodes, vector<int>(1)));	

	int idx;
	string curDist = "";

	for (int i = 0; i < this->numNodes; i++) {
		idx = 0;
		curDist = "";
		for  (int j = 0; j < content[i].size(); j++) {
			if (content[i][j] == ',') {
				this->dist[i][idx] = atoi(curDist.c_str());
				curDist = "";
				idx++;
			} else if ((int)content[i][j] == 32) {
				continue;
			} else {
				curDist += content[i][j];
				if (j == content[i].size()-1)	this->dist[i][idx] = atoi(curDist.c_str());	
			}
		}
	}
	return 0;
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
		if (line.size() > 2)	this->numNodes++;
	}

	updateMatrix(wholeCsv);
	cout << "Matrix updated." << endl;
	return 0;
}

int 
Floyd::printMatrices()
{
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}


int
Floyd::findShortestPaths()
{	
	int total_size;
	int firstPath, secondPath;

	for (int j = 0; j < this->numNodes; j++) {
		for (int i = 0; i < this->numNodes; i++) {
			for (int k = 0; k < this->numNodes; k++) {

				if(dist[i][k] > (dist[i][j] + dist[j][k])) {
					dist[i][k] = dist[i][j] + dist[j][k];
					total_size = path[i][j].size() + path[j][k].size();
					path[i][k].resize(total_size);
					
					firstPath = path[i][j].size();
					if (firstPath == 1) {
						path[i][k][0] = j;
					}	else {
						for (int m = 0; m < firstPath; m++)
							path[i][k][m] = path[i][j][m];
					}

					secondPath = path[j][k].size();
					if (secondPath == 1) {
						path[j][k][firstPath] = k;
					}	else {
						for (int m = 0; m < secondPath; m++) {
							path[i][k][m+firstPath] = path[j][k][m];
						}
					}
				}
			}
		}
	}
	return 0;
}



int
main(int argc, char* argv[])
{
	assert(argc == 2 && "[Usage] ./floyd input.csv");

	Floyd floyd(argv[1]);

	floyd.readFile();

	floyd.printMatrices();

	floyd.findShortestPaths();

	cout << "After finding shortest paths: " << endl;

	floyd.printMatrices();

	return 0;
}