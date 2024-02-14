#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"

PizzaNode::PizzaNode(int x, int y, string name, string main) : name{ name }, numOfBr{ 0 }
, left{ NULL }, right{ NULL }{
	if (main == "beingMain") {
		numOfBr++;
	}
	point[0] = x;
	point[1] = y;
}

bool PizzaNode::isBranch(string name1) {
	if (isSubBranch()) {
		if (main == name1)
			return true;
		else
			return false;
	}
	else {
		if (name == name1) {
			return true;
		}
		else
			return false;
	}
}

double PizzaNode::dbDis(int x, int y) {
	return pow(point[0] - x, 2) + pow(point[1] - y, 2);
}

int PizzaNode::hashValue() {
	if (numOfBr != 0) {
		return hashVal(name);
	}
	return hashVal(main);
}

bool PizzaNode::isSubBranch() {
	if (numOfBr == 0) {
		return true;
	}
	else {
		return false;
	}
}