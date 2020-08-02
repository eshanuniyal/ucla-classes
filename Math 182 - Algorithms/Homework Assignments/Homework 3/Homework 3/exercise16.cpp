#include <vector>
#include <set>
#include <stack>
#include <iostream>
using namespace std;

int k = 0;

void findOptimalPaths(const vector<int>& pathToNode, vector<int>& minMultiplications, const int bound) {
	k++;
	int parent = pathToNode.back();
	//cerr << parent << endl;

	if (pathToNode.size() - 1 < minMultiplications[parent])
	 	minMultiplications[parent] = pathToNode.size() - 1;
	
	for (int pathElem : pathToNode) {
		int child = parent + pathElem;
		if (child <= bound) {
			vector<int> pathToChild = pathToNode;
			pathToChild.push_back(child);
			findOptimalPaths(pathToChild, minMultiplications, bound);
		}
		else break;
	}
	for (int i = 0; i < pathToNode.size(); i++)
		cout << pathToNode[i] << " ";
	cout << endl;
}

int efficientExponentiationSum(int bound) {
	vector<int> minMultiplications(bound + 1, bound);
	
	// vector to keep track of minimum multiplications needed to get to each index
	minMultiplications[1] = 0;
	
	// vector to track all nodes in current level of tree
	vector<int> pathToOne = { 1 };
	findOptimalPaths(pathToOne, minMultiplications, bound);

	for (int i = 1; i <= bound; i++)
		cerr << i << ": " << minMultiplications[i] << endl;

	int sum = 0;
	for (int minMult : minMultiplications)
		sum += minMult;

	cerr << endl << endl << k << endl;
	return sum;
}

/*
int efficientExponentiationSum(int bound) {

	vector<int> minMultiplications(bound + 1, bound);
	// vector to keep track of minimum multiplications needed to get to each index
	minMultiplications[1] = 0;
	// vector to track all nodes in current level of tree
	stack<vector<int>> currentLevel;
	currentLevel.push(vector<int> {1});
	// root node of tree

// iterating till all elements in current level are greater than bound
	while (true) {

		// generating vector for next levle
		stack<vector<int>> nextLevel;

		// iterating over parent nodes
		while (!currentLevel.empty()) {
			vector<int> parentPath = currentLevel.top();
			currentLevel.pop();
//			for (vector<int> parentPath : currentLevel) {
			int parentValue = parentPath.back();
			// iterating over possible path elements
			for (int pathElem : parentPath) {
				int childValue = parentValue + pathElem;
				// checking if child node is contained in bound
				if (childValue <= bound) {
					// creating child node
					vector<int> childPath = parentPath;
					childPath.push_back(childValue);
					nextLevel.push(childPath);
					// updating minimum multiplications
					if (childPath.size() - 1 < minMultiplications[childValue])
						minMultiplications[childValue] = childPath.size() - 1;
				}
			}
		}

		cerr << "Level Size: " << nextLevel.size() << endl;
		// cerr << "Optimal path to 15: " << minMultiplications[15] << endl;

		// updating current level
		currentLevel = nextLevel;

		// for (Node node : currentLevel) {
		// 	cerr << node.value << ":  ";
		// 	for (int elem : node.pathToNode)
		// 		cerr << elem << " ";
		// 	cerr << endl;
		// }


		// terminating condition: there aren't any child nodes
		if (nextLevel.empty())
			break;
	}

	for (int i = 1; i <= bound; i++)
		cerr << i << ": " << minMultiplications[i] << endl;

	int sum = 0;
	for (int minMult : minMultiplications)
		sum += minMult;

	return sum;
}

*/