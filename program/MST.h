#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Graph.h"
#include "math.h"
using namespace std;

// heapNode structure

struct heapNode { 
	int Hvalue;
	int Hsource;
	int Hweight;
	heapNode* left;
	heapNode* right;
	heapNode* parentLeft;
	heapNode* parentRight;
};

// MSTNode structure

struct MSTNode {
	int Mvalue;
	int Mweight;
	int source;
	MSTNode* leftChild;
	MSTNode* rightSibling;

};



class MST : public Graph {


	// private members
private:

	MSTNode* MSTroot;
	heapNode* heapRoot;
	vector<heapNode> minHeap;

	int Vcount;
	int Vtotal;
	int MSTWeight;
	bool disjoint;


	// public members
public:

	MST();
	MST(int);

	void makeMST(); // adds starting node to Minimum spanning tree. Calls a minheap to be built in order to add subsequent nodes. Prints every iteration.

	void getHeapValues(); // make a heap representing egdes availible from the selected nodes (the nodes in the MST)

	void checkCycle(vertex*&); // check to see if an edge leads to a previously visited vertex
	void buildHeap(); // creates a binary heap with chosen edge values 
	void bubble(heapNode*&); // utility function for maintaining min heap properties // swaps current node with parent that has a greater weight

	void printHeap(); // print contents in heap
	void printH(heapNode*); // daughter call of printHeap

	void destroyHeap(); // destroy contents in heap
	void destroyH(heapNode*&); // daughter call of destroyHeap

	void printMST(); // print current MST path
	void printM(MSTNode*); // daughter call of printMST

	void destroyMST(); //destroy contents of MST
	void destroyM(MSTNode*&); // daughter call of destroyMST

	int getMSTWeight(); // returns and integer (weight of current MST)

	~MST();

};

MST::MST() {
	Vcount = 0;
	MSTWeight = 0;
	disjoint = false;
	heapRoot = NULL;
}

MST::MST(int V) : Graph(V) {
	Vcount = 0;
	MSTWeight = 0;
	disjoint = false;
	heapRoot = NULL; 
}




void MST::makeMST() { // new tree will be made for each disjoint
	
	if (parent.size() == 0) {
		oFile << "\n Nothing in Graph. \n" << endl;
		return;
	}

	if (MSTroot == NULL) { // nothing in MST. Add a root
		for (int i = 0; i < parent.size(); i++) {
			if (parent[i] != NULL) { 
				// add source
				cout << "\nMST Source is: " << parent[i]->name << endl;
				oFile << "\nMST Source is: " << parent[i]->name << endl;
				MSTroot = new MSTNode;

				MSTroot->Mvalue = parent[i]->name;
				MSTroot->Mweight = parent[i]->weight;

				MSTWeight += MSTroot->Mweight;

				MSTroot->leftChild = NULL;
				parent[i]->known = true;
				Vcount++;
				printMST();

				getHeapValues();
				break;
			}
		}
	}



	while (Vcount != vertexCount) {
		if (heapRoot == NULL && disjoint == false) { // no more edges, assume the rest of the verticies are disjointed
		// go to next unknown vertex and restart MST function. counts stay the same, old heap is deleted. each MST will be on screen when finished
			disjoint = true;
			MSTWeight = 0;

		}

		if (disjoint == true) {
			// find new starting point for MST;
			// destroy old MST before making new one
			destroyMST();
			for (int i = 0; i < parent.size(); i++) {

				if (parent[i] != NULL && parent[i]->known == false) {

					// new starting point is root.
					MSTroot = new MSTNode;

					MSTroot->Mvalue = parent[i]->name;
					MSTroot->Mweight = parent[i]->weight;

					MSTWeight += MSTroot->Mweight;

					MSTroot->leftChild = NULL;
					parent[i]->known = true;
					Vcount++;
					cout << "\n\nNew Disjoint MST" << endl;
					printMST();
					oFile << "Weight of current MST: " << getMSTWeight() << endl;
					cout << "MST Weight: " << getMSTWeight() << endl;
					getHeapValues();

					break;

				}
			}

			disjoint = false;

			if (Vcount == vertexCount) {
				cout << "\nDone making MST path!\n" << endl;
				oFile << "\nDone making MST path!" << endl;

				Vcount = 0;
				MSTWeight = 0;
				destroyMST();

				// Re-init values for disjoint exit
				// set the known member in every vertex and every edge back to false
				for (int i = 0; i < parent.size(); i++) {

					if (parent[i] != NULL) {
						parent[i]->known = false;

						if (parent[i]->nextAdjNode != NULL) {
							vertex* read;
							read = parent[i];

							read = read->nextAdjNode;
							while (read != NULL) {
								read->known = false;
								read = read->nextAdjNode;
							}
						}
					}
				}

				return; // done
			}

		}


		while (Vcount != vertexCount && heapRoot != NULL) {



			// copy data from root of heap into new node
			// MSTNode* add;
			MSTNode* temp;
			MSTNode* add;
			add = new MSTNode;

			add->Mvalue = heapRoot->Hvalue;
			add->Mweight = heapRoot->Hweight;
			add->source = heapRoot->Hsource;
			MSTWeight += add->Mweight;

			// add left child
			temp = MSTroot;
			while (true) {

				if (temp->leftChild == NULL) {

					temp->leftChild = add;
					add->leftChild = NULL;
					add->rightSibling = NULL;
					break;
				}
				/*else if () { // if add.source == temp.source, temp traverses to last right sibling 

					if () { // if 

					}

				}*/
				else {
					temp = temp->leftChild;
				}
			}

			// look for matching parent (same as what's in heapRoot) in vector. Mark it known
			for (int i = 0; i < parent.size(); i++) {
				if (parent[i] != NULL && heapRoot->Hvalue == parent[i]->name) {
					parent[i]->known = true;
				}
			}

			// increment Vcount
			Vcount++;

			// print current MST
			printMST();
			oFile << "MST Weight: " << getMSTWeight() << endl;
			cout << "MST Weight: " << getMSTWeight() << endl;

			//destroy heap so new one can be made
			destroyHeap();

			if (Vcount == vertexCount) {
				cout << "Done making MST path!\n" << endl;
				oFile << "\nDone making MST path!\n" << endl;
				break;
			}

			// call getHeapValues
			getHeapValues();



		} // end while
	}

	Vcount = 0;
	MSTWeight = 0;
	destroyMST();

	// set the known member in every vertex and every edge back to false
	for (int i = 0; i < parent.size(); i++) {

		if (parent[i] != NULL) {
			parent[i]->known = false;

			if (parent[i]->nextAdjNode != NULL) {
				vertex* read;
				read = parent[i];

				read = read->nextAdjNode;
				while (read != NULL) {
					read->known = false;
					read = read->nextAdjNode;
				}
			}
		}
	}
}





void MST::getHeapValues() {

	// look at known parents in adjacency list
	// add their unkown edges

	for (int i = 0; i < parent.size(); i++) { // read each parent

		if (parent[i] != NULL && parent[i]->known == true) { // if the parent is marked known

			// read the edges
			vertex* reader = parent[i];
			reader = reader->nextAdjNode; // access first edge

			while (reader != NULL) {
				
				
				// if the edge is true, nothing is done, loop and read next

				if (reader->known == false) { // if the egde is false, check for a cycle (may be cleaner if done in a daughter function)

					// check for cycle
					checkCycle(reader);

					// if still false, add to min heap
					if (reader->known == false) {

						// extract data
						
						heapNode edge;
						edge.Hvalue = reader->name;
						edge.Hsource = reader->source;
						edge.Hweight = reader->weight;

						minHeap.push_back(edge);
						

					}

				}

				reader = reader->nextAdjNode; // access next edge
			}

		}

	}

	// time to add values in heap;
	buildHeap();
	// minheapclear
}

// compare edge against each found vertex
void MST::checkCycle(vertex*& edge) {
	//oFile << "\nChecking " << edge->name << " for cycle.\n" << endl;
	for (int i = 0; i < parent.size(); i++) {
		
		if (parent[i] != NULL && parent[i]->known == true && edge->name == parent[i]->name) { // if this results in a cycle, mark the edge known

			edge->known = true;

		}
	}
}



// using values, build a heap
void MST::buildHeap() {
	int heapV = 0;
	int max = 1;
	int level = 0;
	int prevMax, m, levelCount, midpoint;
	bool left = false;
	bool right = false;
	heapNode* root;

	//cout << minHeap[heapV].Hweight << endl;

	while (heapV < minHeap.size()) {

		if (heapV == 0) { // there is nothing in heap so make root

			root = new heapNode; 
			root->Hvalue = minHeap[heapV].Hvalue; 
			root->Hsource = minHeap[heapV].Hsource; 
			root->Hweight = minHeap[heapV].Hweight;

			//global root point points to this root
			heapRoot = root; 

			// init added node's pointers
			root->parentLeft = NULL;
			root->parentRight = NULL;
			root->left = NULL;
			root->right = NULL;
			// increase heapV
			heapV++;

			// if root is the only addition, routine is done
			if (heapV == minHeap.size()) {
				break;
			}

		}

		//check whether V = max
		if (heapV == max) { // done with level start next
			// update values
			prevMax = max; 
			level++; 
			max = max + pow(2, level); // new max 
			levelCount = 0; 
			m = 0; 

			//add new value at left most space
			heapNode* temp;
			temp = heapRoot;

			while (true) {

				if (temp->left == NULL) { // found left most
					
					heapNode* n = new heapNode;
					temp->left = n;
					
					// add values of next node
					n->Hvalue = minHeap[heapV].Hvalue;
					n->Hsource = minHeap[heapV].Hsource;
					n->Hweight = minHeap[heapV].Hweight;

					// init added node's pointers
					n->parentLeft = NULL;
					n->parentRight = temp;
					n->left = NULL;
					n->right = NULL;

					m = 1;
					bubble(n); // added this for testing
					// exit loop
					break;

				}

				temp = temp->left;
			} // end while true
		} // end if

		// add next value
		midpoint = (prevMax * .5) + pow(2, level);
		heapNode* t = heapRoot; 


		while (heapV != max) {


			if (levelCount > 0) { // need to update midpoint as traversal progresses

				if (left == true) {
					midpoint = midpoint - (level - levelCount);
					left = false;
				}

				if (right == true) {
					midpoint = midpoint + (level - levelCount);
					left = false;
				}
			}


			if (heapV++ > midpoint) {

				if (t->right == NULL) {

					// add immediately to right
					heapNode* add = new heapNode;
					t->right = add;

					// add values of node
					add->Hvalue = minHeap[heapV].Hvalue;
					add->Hsource = minHeap[heapV].Hsource;
					add->Hweight = minHeap[heapV].Hweight;

					// init added node's pointers
					add->parentLeft = t; // points to left parent 
					add->parentRight = NULL;
					add->left = NULL;
					add->right = NULL;

					heapV++;
					m++; // increase number of nodes on level count

					// bubble to correct spot
					bubble(add);
				}
				else {
					t = t->right;
					levelCount++;
					right = true;
				}
			}



			if (heapV++ < midpoint) {

				if (t->left == NULL) {

					// add immediately left
					heapNode* add = new heapNode;
					t->left = add;

					// add values of node
					add->Hvalue = minHeap[heapV].Hvalue;
					add->Hsource = minHeap[heapV].Hsource;
					add->Hweight = minHeap[heapV].Hweight;

					// init added node's pointers
					add->parentLeft = NULL;
					add->parentRight = t; // points to right parent  
					add->left = NULL;
					add->right = NULL;

					heapV++;
					m++; // increase number of nodes on level count

					// bubble to correct spot
					bubble(add);
				}
			}
			else {
				t = t->left;
				levelCount++;
				left = true;
			}
		}

		

	} // end parent while

	// print on the way out
	printHeap(); 
	minHeap.clear(); // empty vector for next use
}


void MST::bubble(heapNode*& node) {
	// bubble while parent left or parent right is not null and grater than current node

	if (node->parentLeft == NULL && node->parentRight == NULL) { 
		return; // at root. Nothing more to do
	}

	if (node->parentLeft != NULL && node->parentLeft->Hweight > node->Hweight) {
		// swap
		heapNode* temp;
		heapNode* n;

		temp = node->parentLeft;

		// create node off to the side
		n = new heapNode;
		n->Hvalue = temp->Hvalue;
		n->Hsource = temp->Hsource;
		n->Hweight = temp->Hweight;

		// copy data from node to temp
		temp->Hvalue = node->Hvalue;
		temp->Hsource = node->Hsource;
		temp->Hweight = node->Hweight;

		// copy data from n to temp right child (node)
		node->Hvalue = n->Hvalue;
		node->Hsource = n->Hsource;
		node->Hweight = n->Hweight;

		bubble(node->parentLeft);

	}
	else if (node->parentRight != NULL && node->parentRight->Hweight > node->Hweight) {
		// swap
		heapNode* temp;
		heapNode* n;

		temp = node->parentRight;

		// create node off to the side
		n = new heapNode;
		n->Hvalue = temp->Hvalue;
		n->Hsource = temp->Hsource;
		n->Hweight = temp->Hweight;

		// copy data from node to temp
		temp->Hvalue = node->Hvalue;
		temp->Hsource = node->Hsource;
		temp->Hweight = node->Hweight;

		// copy data from n to temp left child (node)
		node->Hvalue = n->Hvalue;
		node->Hsource = n->Hsource;
		node->Hweight = n->Hweight;

		bubble(node->parentRight);
	}

}


void MST::printHeap() {

	
	if (heapRoot == NULL) {
		oFile << "\n\nNothing in heap to print" << endl;
		return;
	}
	//cout << "\n\nPrinting Heap In pre order. \n(Heap Resets per iteration).\n" << endl;
	oFile << "\n\nPrinting Heap In pre order. \n(Heap Resets per iteration).\n" << endl;
	printH(heapRoot);
}


void MST::printH(heapNode* read) {

	if (read != NULL) {
		//cout << "Vertex: " << read->Hvalue << "	Weight: " << read->Hweight << endl;
		oFile << "Vertex: " << read->Hvalue << "	Weight: " << read->Hweight << endl;
		printH(read->left);
		printH(read->right);
	}
}



void MST::destroyHeap() {

	if (heapRoot == NULL) {
		return;
	}

	destroyH(heapRoot);
	heapRoot = NULL;
}

void MST::destroyH(heapNode*& node) {
	if (node != NULL) {
		destroyH(node->left);
		destroyH(node->right);
		delete node;
	}
}


void MST::printMST() {
	if (MSTroot == NULL) {
		oFile << "Nothing in MST to print" << endl;
		return;
	}
	cout << "\nPrinting MST" << endl;
	oFile << "\nPrinting MST" << endl;
	printM(MSTroot); 
}

void MST::printM(MSTNode* node) { 
	if (node != NULL) {
		cout << "Vertex: " << node->Mvalue << endl;
		oFile << "Vertex: " << node->Mvalue << endl;
		printM(node->leftChild);
	}
}

void MST::destroyMST() {
	if (MSTroot == NULL) {
		return;
	}

	destroyM(MSTroot);
	MSTroot = NULL;
}

void MST::destroyM(MSTNode*& node) {
	if (node != NULL) {
		destroyM(node->leftChild);
		delete node;
	}
}


int MST::getMSTWeight() {
	return MSTWeight;
}


MST::~MST() {
	// free memory. close log

	// MST
	destroyMST();

	// heap
	destroyHeap();

	// close file
	oFile.close();

}