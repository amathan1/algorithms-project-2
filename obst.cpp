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
		this->roots[i][i+1] = i+1;
	}
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


float
OBST::findCost(int i, int j, int k)
{
	return this->matrix[i][k] + this->matrix[k+1][j];
}


int
OBST::updateCost(int i, int j)
{

	vector <float> costs;
	float initial_cost = 0;
	int min_idx;
	for (int m = i; m < j; m++) {
		initial_cost += this->matrix[m][m+1];
	}

	for (int k = i; k < j; k++) {
		costs.push_back(initial_cost + findCost(i, j, k));
	}

	min_idx = findMinCost(costs);
	this->matrix[i][j] = costs[min_idx];
	this->roots[i][j] = i + min_idx + 1;

	return 0;
}


int
OBST::findOptimalBST()
{

	for (int j = 2; j < this->numNodes+1; j++) {
		for (int i = 0; i < (this->numNodes-j+1); i++) {
			updateCost(i, i+j);
		}
	}

	return 0;
}


int
OBST::printOBST()
{

	int cnt = 0; 
	for (int i = 0; i < numNodes+1; i++) {
		for (int j = 0; j < numNodes+1; j++) {
			cout << this->matrix[i][j] << "\t";
		}
		cout << endl << endl;
	}

	/*cout << "This is roots : " << endl;

	for (int i = 0; i < numNodes+1; i++) {
		for (int j = 0; j < numNodes+1; j++) {
			cout << this->roots[i][j] << "\t";
		}
		cout << endl << endl;
	}*/

	vector < vector <int> > depths(numNodes);

	buildTree(0, this->numNodes, 0, depths);

	for (int i = 0; i < depths.size(); i++) {
		if (depths[i].size() > 0) {
			cout << "Depth " << i << ": ";
			for (int j = 0; j < depths[i].size(); j++) {
				cout << depths[i][j] << ", ";
			}
			cout << endl;
		}
	}

	return 0;	
}


int
OBST::buildTree(int i, int j, int depth, vector < vector <int> > &depths)
{

	if (j-i == 1) {
		if (depths[0].size() > 0 && depths[0][0] != j) {
			depths[depth].push_back(j);
		}	else if (depths[0].size() == 0) {
				depths[depth].push_back(j);
			}

		return 0;
	} else if (j - i == 2 && i == 0) {
		buildTree(0, 1, depth, depths);
		return 0;
	}

	depths[depth].push_back(this->roots[i][j]);
	buildTree(i, this->roots[i][j], depth+1, depths);
	buildTree(this->roots[i][j], j, depth+1, depths);

	return 0;
}


int 
main(int argc, char* argv[])
{

	OBST obst(argv);

	obst.findOptimalBST();

	obst.printOBST();

	return 0;
}