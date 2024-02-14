#ifndef PIZAA
#define PIZAA

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "hash.h"
#include "KdTree.h"
#include "Neighbourhood.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaNode.h"

class PizzaList {
public:
	PizzaList();
	void insert(PizzaNode* newNode);
	PizzaNode* findingMainBranch(string name);
	void findingMainBranchAndIncNumOfBrs(string name);
	void findingMainBranchAndDecNumOfBrs(string name);
	int findingMainBranchAndRetNumOfBrs(string name);
	void printingBrsCoordinatesWithNames(string name);
	void delBrInHashTable(int x, int y);
	bool checkIterativeCoordinates(int x, int y);
	void determineNearestBranch(string name, PizzaNode** nearest, int x, int y);
private:
	PizzaNode* last;
};

#endif
