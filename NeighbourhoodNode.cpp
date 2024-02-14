#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"

NeighbourhoodNode::NeighbourhoodNode(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, string name)
	:link{ NULL }, name{ name }, x1{ x1 },
	x2{ x2 }, x3{ x3 }, x4{ x4 }, y1{ y1 }, y2{ y2 }, y3{ y3 }, y4{ y4 }{

};
