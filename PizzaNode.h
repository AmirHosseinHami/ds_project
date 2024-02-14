#ifndef LIST
#define LIST

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "PizzaList.h"
#include "hash.h"
#include "KdTree.h"
#include "Neighbourhood.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"

class PizzaNode {
	friend class PizzaList;
	friend class KdTree;
public:
	PizzaNode(int x = 0, int y = 0, string name = "a", string main = "a");
	int hashValue();
	bool isSubBranch();
	double dbDis(int x, int y);
	bool isBranch(string name);
private:
	string name;
	int numOfBr;//this is the factor to  know if it is a mainbranch or sub branch
	string main;
	int point[2];
	PizzaNode* left;
	PizzaNode* right;
};

#endif
