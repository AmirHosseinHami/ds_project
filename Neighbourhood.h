#ifndef HOOD
#define HOOD

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"

class Neighbourhood {
private:
	NeighbourhoodNode* first;
public:
	Neighbourhood();
	void insert(NeighbourhoodNode* newNode);//insert at first
	int Max(int a, int b);
	int Min(int a, int b);
	void determiningDistrictOfCoordinates(int* xMin, int* xMax, int* yMin, int* yMax, NeighbourhoodNode* node);
	NeighbourhoodNode* retNodeWithName(string name);
};

#endif
