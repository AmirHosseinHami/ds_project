#ifndef KD
#define KD

#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

#include "hash.h"
#include "Neighbourhood.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"

class KdTree {
public:
	KdTree();
	void insert(PizzaNode* insertedNode);
	PizzaNode* minNode(PizzaNode* x, PizzaNode* y, PizzaNode* z, int dimension);
	PizzaNode* findMin(PizzaNode* root, int dimension);
	bool havingSameCoordinates(PizzaNode* node1, PizzaNode* node2);
	void copyPizzaNode(PizzaNode* node1, PizzaNode* node2);
	void deleteNode(int x, int y, string* mainName);
	bool isBalanced();
	void checkIterativeCoordinates(int x, int y, int* state);
	void searchForNodeByName(string name, PizzaNode** searchingNode);
	string getMainNameOfSearchingNode(string name);
	void fillingArrOfMains(NodeForCompNumOfBrs arr[150], PizzaList* hashTableForPizzas, int* indexForArr);
	void fillingArrWithTreeNodes(PizzaNode* arr, int* index);
	void sortNodesBasedOnChosenCoor(PizzaNode* arr, int const begin, int const end, int comp);
	void rebuildToBalance();
	PizzaNode* findingNodeWithCoordinates(int x, int y);
	void printingPizzaLandsWithInNeighbourhood(int xMin, int xMax, int yMin, int yMax);
	void printingAvailablePizzaLands(int xMin, int xMax, int yMin, int yMax);
	void NearestPizzaLand(int x, int y);
	void NearestBranch(string name, PizzaList* hashTableForPizzas, int x, int y);
private:
	PizzaNode* root;

	void findingNodeWithCoordinatesRec(int x, int y, PizzaNode* root, int depth, PizzaNode** pToSearchingNode);
	PizzaNode* insertRec(PizzaNode* root, PizzaNode* insertedNode, int depth);
	PizzaNode* findMinRec(PizzaNode* root, int dimension, int depth);
	PizzaNode* deleteNodeRec(PizzaNode* root, PizzaNode* deletedNode, int depth);
	int isBalancedRec(PizzaNode* root);
	void checkIterativeCoordinatesRec(int x, int y, PizzaNode* root, int* state);
	void searchForNodeByNameRec(string name, PizzaNode** searchingNode, PizzaNode* root);
	void fillingArrOfMainsRec(PizzaNode* root, NodeForCompNumOfBrs arr[150], PizzaList* hashTableForPizzas, int* indexForArr);
	void fillingArrWithTreeNodesRec(PizzaNode* arr, PizzaNode* root, int* index);
	PizzaNode* rebuildToBalanceRec(PizzaNode* arr, int begin, int end, int depth);
	void sortNodesBasedOnChosenCoorHelper(PizzaNode* arr, int const left, int const mid,
		int const right, int comp);
	void printingPizzaLandsWithInNeighbourhoodRec(int xMin, int xMax, int yMin, int yMax, PizzaNode* root, int depth);
	void printingAvailablePizzaLandsRec(int xMin, int xMax, int yMin, int yMax,
		PizzaNode* root, int depth);
	PizzaNode* NearestPizzaLandRec(int x, int y, PizzaNode* root, PizzaNode* nearest, int depth);
	bool NearestPizzaLandRecHelper(int x, int y, PizzaNode* root, PizzaNode* nearest, int depth);
};

#endif