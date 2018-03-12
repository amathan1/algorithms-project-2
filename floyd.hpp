#include <vector>
#include <iostream>
#include <string>

using namespace std;




class
Floyd
{

public:
	Floyd(string fileName) {this->fileName = fileName;}

	int findShortestPaths();

	int recursiveHelper();


private:
	string fileName;

};