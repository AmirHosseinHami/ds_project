#ifndef NLIST
#define NLIST

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "hash.h"
#include "KdTree.h"
#include "Neighbourhood.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"

class NeighbourhoodNode {
	friend class Neighbourhood;
public:
	NeighbourhoodNode(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, string name);
private:
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
	string name;
	NeighbourhoodNode* link;
};

#endif
