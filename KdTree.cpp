#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"

KdTree::KdTree() {
	root = NULL;
}

PizzaNode* KdTree::insertRec(PizzaNode* root, PizzaNode* insertedNode, int depth)
{
	if (root == NULL)
		return insertedNode;

	int comp = depth % 2;

	if (insertedNode->point[comp] < (root->point[comp]))
		root->left = insertRec(root->left, insertedNode, depth + 1);
	else
		root->right = insertRec(root->right, insertedNode, depth + 1);

	return root;
}

void KdTree::insert(PizzaNode* insertedNode)
{
	root = insertRec(root, insertedNode, 0);
}

PizzaNode* KdTree::minNode(PizzaNode* x, PizzaNode* y, PizzaNode* z, int dimension)
{//min between three nodes coordinates based on dimension
	PizzaNode* res = x;
	if (y != NULL && y->point[dimension] < res->point[dimension])
		res = y;
	if (z != NULL && z->point[dimension] < res->point[dimension])
		res = z;
	return res;
}

PizzaNode* KdTree::findMinRec(PizzaNode* root, int dimension, int depth)
{
	if (root == NULL)
		return NULL;

	int comp = depth % 2;

	if (comp == dimension)
	{
		if (root->left == NULL)
			return root;
		return findMinRec(root->left, dimension, depth + 1);
	}

	return minNode(root,
		findMinRec(root->left, dimension, depth + 1),
		findMinRec(root->right, dimension, depth + 1), dimension);
}

PizzaNode* KdTree::findMin(PizzaNode* root, int dimension)
{
	return findMinRec(root, dimension, 0);
}

bool KdTree::havingSameCoordinates(PizzaNode* node1, PizzaNode* node2)
{

	for (int i = 0; i < 2; ++i) {
		if (node1->point[i] != node2->point[i]) {
			return false;
		}
	}

	return true;
}

void KdTree::copyPizzaNode(PizzaNode* node1, PizzaNode* node2)//copies node2 to node1
{
	for (int i = 0; i < 2; i++) {
		node1->point[i] = node2->point[i];
	}
	node1->numOfBr = node2->numOfBr;
	node1->main = node2->main;
	node1->name = node2->name;
}

PizzaNode* KdTree::deleteNodeRec(PizzaNode* root, PizzaNode* deletedNode, int depth)
{

	if (root == NULL) {
		return NULL;
	}

	int comp = depth % 2;

	if (havingSameCoordinates(root, deletedNode))
	{
		if (root->right != NULL)
		{
			PizzaNode* min = findMin(root->right, comp);
			copyPizzaNode(root, min);
			root->right = deleteNodeRec(root->right, min, depth + 1);
		}
		else if (root->left != NULL)
		{
			PizzaNode* min = findMin(root->left, comp);
			copyPizzaNode(root, min);
			root->right = deleteNodeRec(root->left, min, depth + 1);
		}
		else
		{
			delete root;
			return NULL;
		}
		return root;
	}

	if (deletedNode->point[comp] < root->point[comp])
		root->left = deleteNodeRec(root->left, deletedNode, depth + 1);
	else
		root->right = deleteNodeRec(root->right, deletedNode, depth + 1);
	return root;
}

void KdTree::findingNodeWithCoordinatesRec(int x, int y, PizzaNode* root, int depth, PizzaNode** pToSearchingNode) {

	if (root == NULL) {
		return;
	}

	PizzaNode* temp = new PizzaNode(x, y);
	if (havingSameCoordinates(temp, root)) {
		(*pToSearchingNode) = root;
	}

	int comp = depth % 2;
	if (!comp) {
		if (root->point[0] < x) {
			findingNodeWithCoordinatesRec(x, y, root->left, depth, pToSearchingNode);
		}
		else {
			findingNodeWithCoordinatesRec(x, y, root->right, depth, pToSearchingNode);
		}
	}
	else {
		if (root->point[1] < y) {
			findingNodeWithCoordinatesRec(x, y, root->left, depth, pToSearchingNode);
		}
		else {
			findingNodeWithCoordinatesRec(x, y, root->right, depth, pToSearchingNode);
		}
	}
	delete temp;
}

PizzaNode* KdTree::findingNodeWithCoordinates(int x, int y) {
	PizzaNode* temp = NULL;
	findingNodeWithCoordinatesRec(x, y, root, 0, &temp);
	if (temp == NULL) {
		cout << "There is no pizzaLand with thes coordinates.\n";
		return NULL;
	}
	else if (!temp->isSubBranch()) {
		cout << "Thsese coordinates belong to a main branch ,thus it can not be deleted.\n";
		return NULL;
	}
	return temp;
}

void KdTree::deleteNode(int x, int y, string* mainName)
{
	PizzaNode* temp = findingNodeWithCoordinates(x, y);
	if (temp != NULL) {
		PizzaNode* deletedNode = new PizzaNode(x, y);
		root = deleteNodeRec(root, deletedNode, 0);
		(*mainName) = temp->main;
	}
	return;
}

int KdTree::isBalancedRec(PizzaNode* root) {//more than zero is balanced
	if (root == NULL)
		return 0;
	int lh = isBalancedRec(root->left);
	if (lh == -1)
		return -1;
	int rh = isBalancedRec(root->right);
	if (rh == -1)
		return -1;

	if (abs(lh - rh) > 1)
		return -1;
	else {
		if (lh > rh) {
			return lh + 1;
		}
		else {
			return rh + 1;
		}
	}
}

bool KdTree::isBalanced() {
	if (isBalancedRec(root) > 0) {
		return true;
	}
	else {
		return false;
	}
}

void KdTree::checkIterativeCoordinatesRec(int x, int y, PizzaNode* root, int* state) {
	if (root == NULL)
		return;

	checkIterativeCoordinatesRec(x, y, root->left, state);

	if (root->point[0] == x && root->point[1] == y) {
		(*state) = 1;
		return;
	}

	checkIterativeCoordinatesRec(x, y, root->right, state);
}

void KdTree::checkIterativeCoordinates(int x, int y, int* state) {
	checkIterativeCoordinatesRec(x, y, root, state);
}

void KdTree::searchForNodeByNameRec(string name, PizzaNode** searchingNode, PizzaNode* root) {
	if (root == NULL)
		return;

	searchForNodeByNameRec(name, searchingNode, root->left);

	if (root->name == name) {
		(*searchingNode) = root;
		return;
	}

	searchForNodeByNameRec(name, searchingNode, root->right);
}

void KdTree::searchForNodeByName(string name, PizzaNode** searchingNode) {
	searchForNodeByNameRec(name, searchingNode, root);
}

string KdTree::getMainNameOfSearchingNode(string name) {
	PizzaNode* temp;
	searchForNodeByName(name, &temp);
	if (temp->numOfBr != 0) {
		return name;
	}
	else {
		return temp->main;
	}
}

void KdTree::fillingArrOfMainsRec(PizzaNode* root, NodeForCompNumOfBrs arr[150],
	PizzaList* hashTableForPizzas, int* indexForArr) {
	if (root == NULL) {
		return;
	}
	fillingArrOfMainsRec(root->left, arr, hashTableForPizzas, indexForArr);

	int numOfMainBrs = 0;
	if (!root->isSubBranch()) {
		(*indexForArr) = (*indexForArr) + 1;
		arr[(*indexForArr)].mainName = root->name;
		int indexForHashTable = root->hashValue();
		arr[(*indexForArr)].numOfBrs = hashTableForPizzas[indexForHashTable].findingMainBranchAndRetNumOfBrs(root->name);
	}

	fillingArrOfMainsRec(root->right, arr, hashTableForPizzas, indexForArr);
}

void KdTree::fillingArrOfMains(NodeForCompNumOfBrs arr[150], PizzaList* hashTableForPizzas, int* indexForArr) {
	fillingArrOfMainsRec(root, arr, hashTableForPizzas, indexForArr);
}

void KdTree::fillingArrWithTreeNodesRec(PizzaNode* arr, PizzaNode* root, int* index) {
	if (root == NULL)
		return;
	fillingArrWithTreeNodesRec(arr, root->left, index);

	(*index) = (*index) + 1;
	copyPizzaNode(&arr[(*index)], root);

	fillingArrWithTreeNodesRec(arr, root->right, index);
}

void KdTree::fillingArrWithTreeNodes(PizzaNode* arr, int* index) {
	fillingArrWithTreeNodesRec(arr, root, index);
}

void KdTree::sortNodesBasedOnChosenCoorHelper(PizzaNode* arr, int const left, int const mid,
	int const right, int comp) {

	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	PizzaNode* leftArray = new PizzaNode[subArrayOne];
	PizzaNode* rightArray = new PizzaNode[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		copyPizzaNode(&leftArray[i], &arr[left + i]);
	for (auto j = 0; j < subArrayTwo; j++)
		copyPizzaNode(&rightArray[j], &arr[mid + 1 + j]);

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (comp ? (leftArray[indexOfSubArrayOne].point[1]
			<= rightArray[indexOfSubArrayTwo].point[1]) : (leftArray[indexOfSubArrayOne].point[0]
				<= rightArray[indexOfSubArrayTwo].point[0])) {
			copyPizzaNode(&arr[indexOfMergedArray], &leftArray[indexOfSubArrayOne]);
			indexOfSubArrayOne++;
		}
		else {
			copyPizzaNode(&arr[indexOfMergedArray], &rightArray[indexOfSubArrayTwo]);
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		copyPizzaNode(&arr[indexOfMergedArray], &leftArray[indexOfSubArrayOne]);
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		copyPizzaNode(&arr[indexOfMergedArray], &rightArray[indexOfSubArrayTwo]);
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;

}

void KdTree::sortNodesBasedOnChosenCoor(PizzaNode* arr, int const begin, int const end, int comp) {
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	sortNodesBasedOnChosenCoor(arr, begin, mid, comp);
	sortNodesBasedOnChosenCoor(arr, mid + 1, end, comp);
	sortNodesBasedOnChosenCoorHelper(arr, begin, mid, end, comp);
}

PizzaNode* KdTree::rebuildToBalanceRec(PizzaNode* arr, int begin, int end, int depth) {
	if (begin == end) {
		return &arr[begin];
	}
	else if (begin > end) {
		return NULL;
	}

	int comp = depth % 2;

	sortNodesBasedOnChosenCoor(arr, begin, end, comp);

	int medium = begin + (end - begin + 1) / 2;

	PizzaNode* root = &arr[medium];

	root->left = rebuildToBalanceRec(arr, begin, medium - 1, depth + 1);
	root->right = rebuildToBalanceRec(arr, medium + 1, end, depth + 1);

	return root;
}

void KdTree::rebuildToBalance() {
	PizzaNode* arrOfNodes = new PizzaNode(100);
	int index = -1;
	fillingArrWithTreeNodes(arrOfNodes, &index);
	root = rebuildToBalanceRec(arrOfNodes, 0, index, 0);
}

void KdTree::printingPizzaLandsWithInNeighbourhoodRec(int xMin, int xMax, int yMin, int yMax,
	PizzaNode* root, int depth) {
	if (root == NULL) {
		return;
	}
	int comp = depth % 2;
	if (!comp) {
		if (root->point[0] < xMin) {
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
		else if (root->point[0] > xMax) {
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		}
		else {
			if ((yMin <= root->point[1]) && (root->point[1] <= yMax)) {
				if (root->isSubBranch()) {
					cout << "Sub :name: " << root->name << "\n";
					cout << "mainBranch: " << root->main << "\n";
				}
				else {
					cout << "Main: name: " << root->name << "\n";
				}
				cout << "x: " << root->point[0] << "   y: " << root->point[1] << "\n";
			}
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
	}
	else {
		if (root->point[1] < yMin) {
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
		else if (root->point[1] > yMax) {
			printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		}
		else {
			if ((xMin <= root->point[0]) && (root->point[0] <= xMax)) {
				if (root->isSubBranch()) {
					cout << "Sub :name: " << root->name << "\n";
					cout << "mainBranch: " << root->main << "\n";
				}
				else {
					cout << "Main: name: " << root->name << "\n";
				}
				cout << "x: " << root->point[0] << "  y: " << root->point[1] << "\n";
			}
		}
		printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
	}
}

void KdTree::printingPizzaLandsWithInNeighbourhood(int xMin, int xMax, int yMin, int yMax) {
	printingPizzaLandsWithInNeighbourhoodRec(xMin, xMax, yMin, yMax, root, 0);
}

void KdTree::printingAvailablePizzaLandsRec(int xMin, int xMax, int yMin, int yMax,
	PizzaNode* root, int depth) {
	if (root == NULL) {
		return;
	}
	int comp = depth % 2;
	if (!comp) {
		if (root->point[0] < xMin) {
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
		else if (root->point[0] > xMax) {
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		}
		else {
			int xTar = (xMin + xMax) / 2;
			int yTar = (yMin + yMax) / 2;
			int R = (yMax - yMin) / 2;
			if (root->dbDis(xTar, yTar) <= pow(R, 2)) {
				if (root->isSubBranch()) {
					cout << "Sub :name: " << root->name << "\n";
					cout << "mainBranch: " << root->main << "\n";
				}
				else {
					cout << "Main: name: " << root->name << "\n";
				}
				cout << "x: " << root->point[0] << "   y: " << root->point[1] << "\n";
			}
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
	}
	else {
		if (root->point[1] < yMin) {
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
		}
		else if (root->point[1] > yMax) {
			printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		}
		else {
			int xTar = (xMin + xMax) / 2;
			int yTar = (yMin + yMax) / 2;
			int R = (yMax - yMin) / 2;
			if (root->dbDis(xTar, yTar) <= pow(R, 2)) {
				if (root->isSubBranch()) {
					cout << "Sub :name: " << root->name << "\n";
					cout << "mainBranch: " << root->main << "\n";
				}
				else {
					cout << "Main: name: " << root->name << "\n";
				}
				cout << "x: " << root->point[0] << "  y: " << root->point[1] << "\n";
			}
		}
		printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->left, depth + 1);
		printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root->right, depth + 1);
	}
}

void KdTree::printingAvailablePizzaLands(int xMin, int xMax, int yMin, int yMax) {
	printingAvailablePizzaLandsRec(xMin, xMax, yMin, yMax, root, 0);
}

PizzaNode* KdTree::NearestPizzaLandRec(int x, int y, PizzaNode* root, PizzaNode* nearest, int depth) {
	if (root == NULL) {
		return nearest;
	}
	if (nearest->dbDis(x, y) > root->dbDis(x, y) || nearest == NULL) {
		nearest = root;
	}

	PizzaNode* possiblePath;
	PizzaNode* nextPath;

	int comp = depth % 2;

	if (comp) {
		if (y < root->point[1]) {
			nextPath = root->left;
			possiblePath = root->right;
		}
		else {
			nextPath = root->right;
			possiblePath = root->left;
		}
	}
	else {
		if (x < root->point[0]) {
			nextPath = root->left;
			possiblePath = root->right;
		}
		else {
			nextPath = root->right;
			possiblePath = root->left;
		}
	}

	nearest = NearestPizzaLandRec(x, y, nextPath, nearest, depth + 1);

	if (NearestPizzaLandRecHelper(x, y, root, nearest, depth)) {
		nearest = NearestPizzaLandRec(x, y, possiblePath, nearest, depth + 1);
	}

	return nearest;

}

void KdTree::NearestBranch(string name, PizzaList* hashTableForPizzas, int x, int y) {
	string mainName;
	//
	PizzaNode* temp;
	searchForNodeByName(name, &temp);
	if (!temp->isSubBranch()) {
		mainName = temp->name;
	}
	else {
		mainName = temp->main;
	}
	// mainName=name;
	int index = hashVal(mainName);
	PizzaNode* nearestBranch;
	hashTableForPizzas[index].determineNearestBranch(name, &nearestBranch, x, y);

	cout << "\n";
	cout << "x: " << nearestBranch->point[0] << "  y: " << nearestBranch->point[1] << "\n";
}

bool KdTree::NearestPizzaLandRecHelper(int x, int y, PizzaNode* root, PizzaNode* nearest, int depth) {
	int comp = depth % 2;

	if (comp) {
		if (nearest->dbDis(x, y) > pow(y - root->point[1], 2)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (nearest->dbDis(x, y) > pow(x - root->point[0], 2)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void KdTree::NearestPizzaLand(int x, int y) {
	PizzaNode* nearest = NULL;
	nearest = NearestPizzaLandRec(x, y, root, nearest, 0);
	cout << "nearest pizzaLand:\n";
	if (nearest->isSubBranch()) {
		cout << "Sub: name: " << nearest->name << "\n";
		cout << "mainBranch: " << nearest->main << "\n";
	}
	else {
		cout << "Main: name: " << nearest->name << "\n";
	}
	cout << "x: " << root->point[0] << "   y: " << root->point[1] << "\n";
}