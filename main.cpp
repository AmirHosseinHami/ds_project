#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"


int main() {
	KdTree kdtree;//having unvalid num of brs
	NodeForCompNumOfBrs arrOfMains[150];
	PizzaList* hashTableForPizzas = new PizzaList[1009];
	Neighbourhood* hashTableForNeibrs = new Neighbourhood[1009];

	bool loopState = true;
	while (loopState) {
		cout << "\n";
		cout << "1.Add-N\n";
		cout << "2.Add-P\n";
		cout << "3.Add-Br\n";
		cout << "4.Del-Br\n";
		cout << "5.List-P\n";
		cout << "6.List-Brs\n";
		cout << "7.Near-P\n";
		cout << "8.Near-Br\n";
		cout << "9.Avail-P\n";
		cout << "10.Most-Brs\n";
		cout << "11.exit\n\n";
		string input;
		cout << "input(number):";
		cin >> input;

		if (input == "1") {
			int x1, x2, x3, x4;
			int y1, y2, y3, y4;
			cout << "x1:"; cin >> x1;
			cout << "y1:"; cin >> y1;
			cout << "x2:"; cin >> x2;
			cout << "y2:"; cin >> y2;
			cout << "x3:"; cin >> x3;
			cout << "y3:"; cin >> y3;
			cout << "x4:"; cin >> x4;
			cout << "y4:"; cin >> y4;
			string name;
			cout << "name:";
			cin >> name;
			NeighbourhoodNode* newNode1 = new NeighbourhoodNode(x1, y1, x2, y2, x3, y3, x4, y4, name);
			int index = hashVal(name);
			hashTableForNeibrs[index].insert(newNode1);
		}

		else if (input == "2") {
			int x;
			int y;
			string name;
			cout << "x:";
			cin >> x;
			cout << "y:";
			cin >> y;

			int state = 0;
			kdtree.checkIterativeCoordinates(x, y, &state);
			if (state) {
				cout << "There is a pizzaLand with this coordinates.\n";
			}
			else {
				cout << "name:";
				cin >> name;
				PizzaNode* newNode1 = new PizzaNode(x, y, name, "beingMain");
				int index = newNode1->hashValue();
				hashTableForPizzas[index].insert(newNode1);
				PizzaNode* newNode2 = new PizzaNode(x, y, name, "beingMain");
				kdtree.insert(newNode2);
				if (!kdtree.isBalanced()) {
					kdtree.rebuildToBalance();
				}
			}
		}

		else if (input == "3") {
			int x;
			int y;
			string name;
			cout << "x:";
			cin >> x;
			cout << "y:";
			cin >> y;

			int state = 0;
			kdtree.checkIterativeCoordinates(x, y, &state);
			if (state) {
				cout << "There is a pizzaLand with this coordinates.\n";
			}
			else {
				string nameOfMainBranch;
				cout << "name of main branch:";
				cin >> nameOfMainBranch;
				int index = hashVal(nameOfMainBranch);
				hashTableForPizzas[index].findingMainBranchAndIncNumOfBrs(nameOfMainBranch);
				string name;
				cout << "name:";
				cin >> name;
				PizzaNode* newNode1 = new PizzaNode(x, y, name, nameOfMainBranch);
				hashTableForPizzas[index].insert(newNode1);
				PizzaNode* newNode2 = new PizzaNode(x, y, name, nameOfMainBranch);
				kdtree.insert(newNode2);
				if (!kdtree.isBalanced()) {
					kdtree.rebuildToBalance();
				}
			}
		}

		else if (input == "4") {
			int x;
			int y;
			cout << "x:";
			cin >> x;
			cout << "y:";
			cin >> y;
			string mainBranchName = "none";
			kdtree.deleteNode(x, y, &mainBranchName);
			if (mainBranchName != "none") {
				int index = hashVal(mainBranchName);
				hashTableForPizzas[index].findingMainBranchAndDecNumOfBrs(mainBranchName);
				hashTableForPizzas[index].delBrInHashTable(x, y);
			}
		}

		else if (input == "5") {
			string name;
			cout << "name:";
			cin >> name;
			int index = hashVal(name);
			int yMin, yMax, xMin, xMax;
			NeighbourhoodNode* node;
			node = hashTableForNeibrs[index].retNodeWithName(name);
			hashTableForNeibrs[index].determiningDistrictOfCoordinates(&xMin, &xMax, &yMin, &yMax, node);
			kdtree.printingPizzaLandsWithInNeighbourhood(xMin, xMax, yMin, yMax);
		}

		else if (input == "6") {
			string name;
			cout << "name:";
			cin >> name;
			string mainName;
			mainName = kdtree.getMainNameOfSearchingNode(name);
			cout << "\n\n";
			int index = hashVal(mainName);
			hashTableForPizzas[index].printingBrsCoordinatesWithNames(name);
		}

		else if (input == "7") {
			int x;
			cout << "x: ";
			cin >> x;
			int y;
			cout << "y: ";
			cin >> y;
			kdtree.NearestPizzaLand(x, y);
		}

		else if (input == "8") {
			cout << "name: ";
			string name;
			cin >> name;
			int x, y;
			cout << "x:";
			cin >> x;
			cout << "y:";
			cin >> y;
			kdtree.NearestBranch(name, hashTableForPizzas, x, y);
		}

		else if (input == "9") {
			int x, y, R;
			cout << "x: ";
			cin >> x;
			cout << "y: ";
			cin >> y;
			cout << "R: ";
			cin >> R;
			int xMin, xMax, yMin, yMax;
			xMin = x - R; xMax = x + R;
			yMin = y - R; yMax = y + R;
			kdtree.printingAvailablePizzaLands(xMin, xMax, yMin, yMax);
		}

		else if (input == "10") {
			int indexForArrOfMains = -1;
			kdtree.fillingArrOfMains(arrOfMains, hashTableForPizzas, &indexForArrOfMains);
			mergeSort(arrOfMains, 0, indexForArrOfMains);
			cout << arrOfMains[indexForArrOfMains].mainName;
			cout << " has the most branches by having " << arrOfMains[indexForArrOfMains].numOfBrs;
			cout << " branches in total.\n";
		}

		else if (input == "11") {
			loopState = false;
		}
		else {
			cout << "invalid input\n\n";
		}

	}
}