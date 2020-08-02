#include <iostream>
#include <vector>
#include <map>
#include "question1.h"
using namespace std;

void MatrixChainOrder(vector<int> p);
void DFS(const Graph G);

int main() {

	vector<int> p = { 5,10,3,12,5,50,6 };
	cout << "Question 2: "; 
	MatrixChainOrder(p);
	cout << endl;
	
	// creating nodes (same as example from class)
	Node y("y"); Node z("z"); Node s("s"); Node f("f");
	Node x("x"); Node w("w"); Node v("v"); Node u("u");
	map<Node*, vector<Node*>> Adj{
		{&s, vector<Node*> {&z,& w}},
		{&z, vector<Node*> {&y,& w}},
		{&y, vector<Node*> {&x}},
		{&x, vector<Node*> {&z}},
		{&w, vector<Node*> {&x}},
		{&v, vector<Node*> {&s,& w}},
		{&f, vector<Node*> {&v,& u}},
		{&u, vector<Node*> {&f}},
	};

	vector<string> ordering = { "s", "z", "y", "x", "w", "f", "v", "u" };

	Graph G(Adj, ordering);
	DFS(G);
}