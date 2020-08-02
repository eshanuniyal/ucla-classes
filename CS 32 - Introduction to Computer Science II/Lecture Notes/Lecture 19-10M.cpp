#include <iostream>
#include <string>
using namespace std;

struct Node{
	string data;
	vector<Node*> children;
	Node* parent;
};


// given a binary search tree, how do we print all its elements in order?
	// to find the smallest element in the navigate, we start from the root node and keep going to the root node of the left subtree until we reach a node with an empty left subtree
	// that's our smallest element
	// we then take its right subtree (if any) and repeat until we exhaust it
	// we then backtrack and repeat

void printTree(const Node* p){
	// print elements of a binary search tree in order
	if (p != nullptr){
		printTree(p->left);	// prints and exhausts elements smaller than current node
		cout << p->data << endl;	// prints current node
		printTree(p->right);	// prints and exhausts elements larger than current node
	}
}	// note: this algorithm involves neither pre-order or post-order traversal, since we examine the left subtree and then the node and then the right subtree
	// this kind of traversal is called inorder traversal

/* Different Kinds of Traversals
	- Preorder traversal:	process the node
							process the subtrees

	- Postorder traversal:	process the subtrees
							process the node

	- Inorder traversal:	process the left subtree
							process the node
							proces the right subtree

	Note: Inorder traversal only makes sense with binary trees.
*/

/* Inserting a node in a binary search tree
	- Traverse through the tree as if searching for the node you want to insert until you arrive to an empty subtree
	- Place the node there
Note: any nodes will therefore always be inserted as a leaf node. Insertion in any reasonably-balanced tree will be O(logN).

*/

/* Deleting a node in a binary search tree
	- Traverse through the tree to locate the node
	- If the node has at least one empty subtree, replace the node with its non-empty subtree (if any)
	- If both the subtrees are non-empty, we replace the node with one of its children
		- In general, we can replace it with the node immediately before it in order or immediately after it in order
			i.e. the largest node in the left subtree or the smallest node in the right subtree
		- Whichever node we choose will have an empty subtree; 
			if the other subtree is not empty, its parent simply inherits that subtree and the node is moved up to replace the deleted node

In a reasonably-balanced tree, deletion is going to be O(logN).

Some subtleties:
	-  If we decide whenever deleting nodes, we're always going to replace it with a node from the left subtree, the tree will become unbalanced over time (with larger right subtrees)
		- This creates a higher constant of proportionality for the time complexity O(logN)
		- The best way to fix this is to either (ideal:) randomise whether you pick a node in the right subtree or the left subtree, or to just alternate
*/

/* AVL Trees
AVL Trees are binary search trees with an additional property: at any given node, the height of the left subtree and the height of the right subtree differ by at most 1
	- Any implementation of an AVL tree requires an extra piece of data for each node: whether the right subtree is larger, or whether the left subtree is larger
	- Insertion and deletion are still O(logN), with a worse constant of proportionality; the worst case time complexity of lookups is vastly improved (always O(logN), never O(N))
*/

/* Red-Black Trees
Red-Black trees are binary search trees where the length of any subtree of one node is at most twice the length of the other subtree of the node
	- Set, map, multiset and multimap all use red-black trees, guaranteeing O(logN) search, insertion and deletion time
	- They also guarantee O(N) ordered lookup time (*unordered* lookup time is O(1) for hash tables)
*/



/* Priority Queues (priority_queue)
A priority queue is a queue where the object in the front is always the object with the highest priority
	- Typically, the priority is represented by a priority; a lower number usually (but not necessarily) means higher priority
	- The C++ STL priority_queue just does a comparison of the items to find which item should be prioritised first
	- Usually, a priority queue is implemented as a binary tree for quick searches and comparisons
		- However, a priority queue doesn't need all the functionality / generality of a binary search tree; 
		  it is therefore implemented as a specialised version of a binary tree called a "heap"
*/

#include <priority_queue>

class Student{
	...;
}

struct PQItem{
	
	bool operator<(const PQItem& lhs, const PQItem& rhs){
		return lhs.priority < rhs.priority;		// could use <= or account for ties some other way
	}

	int priority;
	Student data;
}

int main(){
	// say we want to create a priority queue of students where seniors have higher priority than juniors and so on, and those with higher GPAs within the same year have higher priority
	priority_queue<Student> pq;	// not a good idea, since it doesn't naturally mean anything for a Student to be "less" than another

	priority_queue<PQItem> pq;	// better way to go about things; we can implicitly compare students this way
}


//

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
    const GeoCoord& start, const GeoCoord& end,
    list<StreetSegment>& route, double& totalDistanceTravelled) const {
    // finds an optimal route using the A* search algorithm
    // we use Euclidean distance as a heuristic

    // trivial case: starting coordinate is ending coordinate
    if (start == end) {
        route.clear();
        totalDistanceTravelled = 0;
        return DELIVERY_SUCCESS;
    }

    // checking for bad coordinates
    if (!checkCoords(start, end))
        return BAD_COORD;

    map<GeoCoord, GeoCoord> parents;
    map<GeoCoord, double> openList;        // initialising open list (maps GeoCoords to doubles representing g)
    map<GeoCoord, double> closedList;      // initialising closed list (maps GeoCoords to doubles representing g)

    // pushing starting coordinate onto open list
    openList[start] = 0;    // starting coordinate has zero g
    
    // variable to track current coordinate
    GeoCoord currentCoord = start;

    // while open list isn't empty
    while (!openList.empty()) {
        
        // finding current coord
        currentCoord = findCurrentCoord(openList, end);
        double currentCoordG = openList[currentCoord];
        
        // removing current coord from open list
        openList.erase(currentCoord);

        // DEBUGGING
        // cerr << "Current Coordinates: " << endl;
        // printCoordinates(currentCoord, currentCoordG, distanceEarthMiles(currentCoord, end));
        // DEBUGGING

        // found the solution -> break
        if (currentCoord == end)
            break;

        // finding segments that start with current coordinate
        vector<StreetSegment> nextSegs;
        m_streetMap->getSegmentsThatStartWith(currentCoord, nextSegs);

        // updating parents and open list with next coordinates
        for (int i = 0; i != nextSegs.size(); i++) {
            
            // generating data about next coordinate
            const GeoCoord nextCoord = nextSegs[i].end;                                     // pointer to next geocoordinate
            const double newG = currentCoordG + distanceEarthMiles(currentCoord, nextCoord);         // change in g in this coordinate
            const double nextCoordH = distanceEarthMiles(nextCoord, end);                   // heuristic: Euclidean distance
                
            // bool to check whether parent of coord needs to be added/updated
            bool addCoordParent = true;

            map<GeoCoord, double>::iterator openListItr, closedListItr;
            openListItr = openList.find(nextCoord);
            closedListItr = closedList.find(nextCoord);

            // nextCoord is in open list
            if (openListItr != openList.end()) {
                // if newG is lesser, no need to update parent
                if (openListItr->second <= newG)
                    addCoordParent = false;
            }
            // nextCoord is in closed list
            else if (closedListItr != closedList.end()) {
                // if newG is lesser, no need to update parent
                if (closedListItr->second <= newG)
                    addCoordParent = false;
                // newG is greater -> move coordinate from closed list to open list
                else {
                    openList[nextCoord] = closedListItr->second;    // newG is greater, so no update
                    closedList.erase(closedListItr);
                }
            }
            // nextCoord not in open list or closed list -> put nextCoord in open list
            else 
                openList[nextCoord] = newG;

            // adding/updating parent
            if (addCoordParent)
                parents[nextCoord] = currentCoord;
        }

        // pushing current coordinate into closed list
        closedList[currentCoord] = currentCoordG;
    }

    // no route found
    if (currentCoord != end)
        return NO_ROUTE;

    // route found 
    totalDistanceTravelled = 0;
    route.clear();

    // calculate route by backtracking from end node via parents
    GeoCoord e = end;
    while (true) {

        // finding starting geocoordinate of current segment
        GeoCoord s = parents[e];
        
        // base case: s = starting coordinate
        if (s == start)
            break;

        // finding desired street segment (from s to e)
        vector<StreetSegment> segs;
        m_streetMap->getSegmentsThatStartWith(s, segs);

        // iterating over segs to find desired street segment
        for (int i = 0; i != segs.size(); i++)
            if (segs[i].end == e) {
                route.push_front(segs[i]);
                totalDistanceTravelled += distanceEarthMiles(s, e);
                e = s;
                break;
            }   
    }
    return DELIVERY_SUCCESS;
}