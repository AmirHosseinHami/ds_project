#ifndef COMP
#define COMP

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "hash.h"
#include "KdTree.h"
#include "Neighbourhood.h"
#include "NeighbourhoodNode.h"
#include "PizzaList.h"
#include "PizzaNode.h"

struct NodeForCompNumOfBrs {
	string mainName;
	int numOfBrs;
};

void merge(NodeForCompNumOfBrs array[], int const left, int const mid,
	int const right);
void mergeSort(NodeForCompNumOfBrs array[], int const begin, int const end);

#endif
