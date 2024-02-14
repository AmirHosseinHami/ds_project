#include "hash.h"
#include "KdTree.h"
#include "NeighbourhoodNode.h"
#include "NodeForCompNumOfBrs.h"
#include "PizzaList.h"
#include "PizzaNode.h"
#include "Neighbourhood.h"

int hashVal(string str) {
	int H = 5381;
	for (int i = 0; i <= (str.length() - 1); i++) {
		H = (H * 33) ^ str[i];
	}
	H = abs(H);
	H = H % 1009;
	return H;
}