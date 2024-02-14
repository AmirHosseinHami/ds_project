#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"

Neighbourhood::Neighbourhood() :first{ NULL } {

}

int  Neighbourhood::Max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int Neighbourhood::Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

void Neighbourhood::insert(NeighbourhoodNode* newNode) {
	if (first == NULL) {
		first = newNode;
	}
	else {
		newNode->link = first;
		first = newNode;
	}
}

NeighbourhoodNode* Neighbourhood::retNodeWithName(string name) {
	NeighbourhoodNode* temp = first;
	if (temp == NULL) {
		return NULL;
	}
	else {
		while (1) {
			if (temp == NULL) {
				return NULL;
			}
			if (temp->name == name) {
				return temp;
			}
			temp = temp->link;
		}
	}
}

void Neighbourhood::determiningDistrictOfCoordinates(int* xMin, int* xMax, int* yMin,
	int* yMax, NeighbourhoodNode* node) {
	(*xMax) = Max(Max(Max(node->x1, node->x2), node->x3), node->x4);
	(*xMin) = Min(Min(Min(node->x1, node->x2), node->x3), node->x4);
	(*yMax) = Max(Max(Max(node->y1, node->y2), node->y3), node->y4);
	(*yMin) = Min(Min(Min(node->y1, node->y2), node->y3), node->y4);
	return;
}
