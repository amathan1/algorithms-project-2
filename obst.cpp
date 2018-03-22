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
	/*
	* Find minimum cost
	*/
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
	/*Formula discussed in the class*/
	return this->matrix[i][k] + this->matrix[k+1][j];
}


int
OBST::updateCost(int i, int j)
{
	/*
	* Update cost in the matrix
	*/

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
	/*
	* Build Optimal BST Matrix
	*/

	for (int j = 2; j < this->numNodes+1; j++) {
		for (int i = 0; i < (this->numNodes-j+1); i++) {
			updateCost(i, i+j);
		}
	}

	return 0;
}


int
OBST::findDepth(vector < vector <int> > &depths)
{
	/*
	* Finds the maximum depth of tree.
	*/
	int depth = depths.size();
	int cnt = 0;
	int size;
	
	for (int i = 0; i < depths.size(); i++) {
		size = depths[i].size();
		cnt = 0;
		for (int j = 0; j < size; j++) 
			if (depths[i][j] > 0)	cnt++;
		if (size == 0 || cnt == 0) {
			depth = i;
			break;
		} else {
			cnt += size;
		  }
	}
		
	return depth;
}



int
OBST::printOBST()
{
	/*
	* To print the tree from the matrix
	*/
	
	vector < vector <int> > depths(numNodes);
	buildTree(0, this->numNodes, 0, depths);

	int depth = findDepth(depths);

	for (int i = 0; i < depth; i++) {
		cout << "Depth " << i << ": ";
		for (int j = 0; j < depths[i].size(); j++) {
			cout << depths[i][j] << ", ";
		}
		cout << endl;
	}

	return 0;	
}



int
OBST::buildTree(int i, int j, int depth, vector < vector <int> > &depths)
{
	/*
	* Builds the tree using the matrix
	*/
	
	if (i > this->numNodes+1){
		depths[depth].push_back(0);
		return 0;
	}

	if (i == j) {	// When there's just one node left to add
		if (i == 0)	{	// When the node has no children, push zeros
			depths[depth].push_back(0);	
		} else {
			depths[depth].push_back(this->roots[j-1][j]);
			buildTree(0, 0, depth+1, depths);
			buildTree(0, 0, depth+1, depths);
			}
		return 0;
	}

	int next;
	int current = this->roots[i][j];
	depths[depth].push_back(current);
	(i <= 1) ? next = 1 : next = i;

	// Recursively build the tree
	buildTree(i, current-1, depth+1, depths);
	if (current==j) {
		buildTree(0, 0, depth+1, depths);
	} else {
		buildTree(current+1, j, depth+1, depths);
		}

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