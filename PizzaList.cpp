#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"


PizzaList::PizzaList() :last{ NULL } {

}

void PizzaList::determineNearestBranch(string name, PizzaNode** nearest, int x, int y) {
	PizzaNode* temp = last;
	if (last == NULL) {
		(*nearest) = NULL;
	}
	while (1) {
		temp = temp->right;
		if (temp->isBranch(name)) {
			if ((*nearest)->dbDis(x, y) > temp->dbDis(x, y)) {
				(*nearest) = temp;
			}
		}
		if (last == temp) {
			break;
		}
	}
	return;
}

PizzaNode* PizzaList::findingMainBranch(string name) {
	PizzaNode* temp = last;
	while (1) {
		temp = temp->right;
		if ((!temp->isSubBranch()) && temp->name == name) {
			return temp;
		}
	}
}

void PizzaList::printingBrsCoordinatesWithNames(string name) {
	PizzaNode* temp = last;
	if (last == NULL) {
		cout << "There is no pizzaLand.\n";
		return;
	}
	while (1) {
		temp = temp->right;
		if (!temp->isSubBranch()) {
			if (temp->name == name) {
				cout << "Main branch: name: " << temp->name << "\n";
				cout << "coordinates:  x: " << temp->point[0];
				cout << "   y: " << temp->point[1] << "\n";
			}
		}
		else if (temp->main == name) {
			cout << "Sub branch: name: " << temp->name << "\n";
			cout << "coordinates:  x: " << temp->point[0];
			cout << "   y: " << temp->point[1] << "\n";
		}
		if (last == temp) {
			break;
		}
	}
	return;
}

int PizzaList::findingMainBranchAndRetNumOfBrs(string name) {
	PizzaNode* temp = findingMainBranch(name);
	return temp->numOfBr;
}

void PizzaList::findingMainBranchAndIncNumOfBrs(string name) {
	PizzaNode* temp = findingMainBranch(name);
	temp->numOfBr++;
}

void PizzaList::findingMainBranchAndDecNumOfBrs(string name) {
	PizzaNode* temp = findingMainBranch(name);
	temp->numOfBr--;
}

void PizzaList::insert(PizzaNode* newNode) {

	if (last == NULL) {
		last = newNode;
		last->left = last->right = newNode;
	}
	else {
		newNode->right = last->right;
		last->right->left = newNode;
		last->right = newNode;
		newNode->left = last;
		last = newNode;
	}
}

bool PizzaList::checkIterativeCoordinates(int x, int y) {//if there is,return true
	PizzaNode* temp = last;
	if (last == NULL) {
		return false;
	}
	while (1) {
		temp = temp->right;
		if (temp->point[0] == x && temp->point[1] == y) {
			return true;
		}
		if (last == temp) {
			break;
		}
	}
	return false;
}

void PizzaList::delBrInHashTable(int x, int y) {
	PizzaNode* temp = last;
	int count = 0;
	if (temp->right == last) {
		count = 1;
	}
	while (1) {
		temp = temp->right;
		if (temp->point[0] == x && temp->point[1] == y) {
			if (count) {
				last = NULL;
			}
			else {
				if (temp == last) {
					last = last->left;
				}
				temp->left->right = temp->right;
				temp->right->left = temp->left;
			}
			delete temp;
			break;
		}
		if (last == temp) {
			break;
		}
	}
}
