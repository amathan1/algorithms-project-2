#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;



class 
OBST
{

public:
	OBST(char*[]);

	int findOptimalBST();

	int updateCost(int, int);

	float findCost(int, int, int);

	int findMinCost(vector<float>&);

	int buildTree(int, int, int, vector < vector <int> >&);

	int printOBST();

private:

	float **matrix;

	int **roots;
	
	int numNodes;

};