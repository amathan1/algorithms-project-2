#include "obst.hpp"



OBST::OBST(char* args[])
{

	this->numNodes = atoi(args[1]);

	this->matrix = (float**) malloc((this->numNodes+1) * sizeof(float*));
	this->roots = (int**) malloc((this->numNodes+1) * sizeof(int*));

	for (int i = 0; i < this->numNodes+1; i++) 
	{
			this->matrix[i] = (float*) calloc(sizeof(float), this->numNodes+1);
			this->roots[i] = (int*) calloc(sizeof(int), this->numNodes+1);
	}

	for (int i = 0; i < this->numNodes; i++) 
	{
		this->matrix[i][i+1] = atof(args[i + 2]);
		this->roots[i][i+1] = i;
	}
	cout << "Initialized the matrix" << endl;
}


float
OBST::findCost(int i, int j, int k)
{
	return this->matrix[i][k-1] + this->matrix[k+1][j];
}


int
OBST::findMinCost(vector<float> &costs)
{
	int min_idx;
	float min_val = 999999999;
	
	for (int i = 0; i < costs.size(); i++) {
		if (costs[i] < min_val) {
			min_idx = i;
			min_val = costs[i];
		}
	}

	return min_idx;
}


int
OBST::updateCost(int i, int j)
{

	// int cost;
	// if (j-i == 1) {
	// 	cost = this->matrix[i][i+1] + this->matrix[j][j+1] + min(this->matrix[i][i+1], this->matrix[j][j+1]);
	// 	this->matrix[i][j+1] = cost;
	// 	if (this->matrix[i][i+1] > this->matrix[j][j+1]) {
	// 		this->roots[i][j] = j;
	// 	} else {
	// 		this->roots[i][j+1] = i;
	// 	}

	// }

	vector <float> costs;
	int initial_cost = 0;
	int min_idx;
	for (int m = i; m < j; m++) {
		initial_cost += this->matrix[m][m+1];
	}

	for (int k = i; k < j; k++) {
		costs.push_back(initial_cost + findCost(i, j, k));
	}

	min_idx = findMinCost(costs);
	this->matrix[i][j] = costs[min_idx];

	return 0;
}

int
OBST::findOptimalBST()
{

	for (int j = 2; j < this->numNodes+1; j++) {
		for (int i = 0; i < this->numNodes - j; i++) {
			updateCost(i, j);
		}
	}
	cout << "Killed it." << endl;

	return 0;
}




int 
main(int argc, char* argv[])
{

	OBST obst(argv);

	obst.findOptimalBST();

	return 0;
}