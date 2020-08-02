#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include "question1.h"
using namespace std;

void DFSVisit(const Graph& G, Node* s, int& time);

void DFS(const Graph G) {
	for (Node* v : G.V) {
		v->colour = WHITE;
		v->pred = nullptr;
	}
	int time = 0;
	for (Node* s : G.V)
		if (s->colour == WHITE)
			DFSVisit(G, s, time);
	
	// printing results
	for (Node* s : G.V) {
		cerr << s->name << endl;
		cerr << "Start time:  " << s->d << endl;
		cerr << "End time:    " << s->f << endl;
		if (s->pred != nullptr)
			cerr << "Predecessor: " << s->pred->name << endl;
		cerr << endl;
	}
}

void DFSVisit(const Graph& G, Node* s, int& time) {
	stack<Node*> whiteStack;
	stack<Node*> blackStack;
	whiteStack.push(s);
	while (!whiteStack.empty()) {
		Node* u = whiteStack.top(); whiteStack.pop();
		if (u->colour == WHITE) {
			time++;
			u->d = time;
			u->colour = GREY;
			vector<Node*> adjacents = G.Adj.find(u)->second;
			for (int vIndex = adjacents.size() - 1; vIndex >= 0; vIndex--) {
				Node* v = adjacents[vIndex];
				if (v->colour == WHITE) {
					v->pred = u;
					whiteStack.push(v);
				}
			}
			u->colour = BLACK;
			blackStack.push(u);
		}
	}

	while (!blackStack.empty()) {
		Node* u = blackStack.top(); blackStack.pop();
		time++;
		u->f = time;
	}
}