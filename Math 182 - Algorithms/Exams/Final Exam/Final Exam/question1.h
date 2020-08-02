#pragma once

#include <vector>
#include <string>
#include <map>
using namespace std;

enum Colour { WHITE, GREY, BLACK };

struct Node {
	// Node name
	string name;
	// Node properties
	Colour colour;
	Node* pred;
	int d;
	int f;

	Node(string name)
		: name(name) {}
};

struct Graph {
	// vertices in graph
	vector<Node*> V;
	// map of vertices to adjacent vertices
	map<Node*, vector<Node*>> Adj;

	Graph(map<Node*, vector<Node*>> Adj, vector<string> ordering)
		: Adj(Adj) {
		// inserting vertices 
		for (string v : ordering) 
			for (map<Node*, vector<Node*>>::iterator itr = Adj.begin(); itr != Adj.end(); itr++)
				if (itr->first->name == v) {
					V.push_back(itr->first);
					break;
				}
		}		
};

