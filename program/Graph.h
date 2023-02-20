#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// vertex structure
struct vertex {
	int name;
	bool known;
	int source; // prev node
	int weight; // weight to prev node
	vertex* nextAdjNode; // for traversing a linear chain of a vertex's adjacnet nodes ordered by least to most costly
	int edges = 0; // this will increment each time an edge is made
};



class Graph {

	// private members
private:
	int V;
	int Vtotal;

	// public members
public:

	int vertexCount = 0; // used to prevent accessing non-existent data
	vector<vertex*> parent; // linked adjacency list
	//unique_ptr<vector<vertex*>> m;

	

	ofstream oFile;

	

	Graph(); // Default Constructor
	Graph(int vertecies); //Copy constructor
	
	// Utilitiy functions
	void addVertex(int); // add a vertex
	void addEdge(int, int, int); // add edge/weight between two existing vertecies. Takes 2 verticies and a weight
	void deleteEdge(int, int); // sets matrix value representing edge to 0/inf
	void addWeight(int, int, int); // increase edge weight by given value
	void subtractWeight(int, int, int); // reduces edgeweight by given value
	int vertecies(); // return amount of verticies in graph
	void printGraph(); // print the current matrix 
	void deleteVertex(int); // delete a vertex, its edges, and any edges to it

	vertex* getVertex(int); // returns a pointer to a vertex

	// close log file in deconstructor
	~Graph();


};


Graph::Graph() {
	V = 0;
	oFile.open("Graph.txt");

}



Graph::Graph(int vertecies) {
	V = vertecies;
	oFile.open("Graph.txt");
}

int Graph::vertecies() {
	return vertexCount;
}



void Graph::printGraph() {
	if (parent.size() == 0) {
		oFile << "\n Nothing in Graph. \n" << endl;
		return;
	} 

	cout << "Printing Graph:\n" << endl;

	vertex* temp;

	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] != NULL) { // if not deleted
			cout << "Vertex Name: " << parent[i]->name << endl;
			oFile << "Vertex Name: " << parent[i]->name << endl;

			if (parent[i]->edges > 0) {
				temp = parent[i]->nextAdjNode;

				cout << "Printing Edges..." << endl;
				for (int j = 0; j < parent[i]->edges; j++) { // print edges of current vertex
					cout << "Edge Name: " << temp->name << " | Edge weight: " << temp->weight << endl;
					oFile << "Edge Name: " << temp->name << " | Edge weight: " << temp->weight << endl;
					temp = temp->nextAdjNode;
				}
				oFile << endl;
			}
			else {
				cout << "Vertex: " << parent[i]->name << " has no edges." << endl;
				oFile << "Vertex: " << parent[i]->name << " has no edges." << endl;
			}

			cout << "\n\n";
		}

	}
	
}





void Graph::addVertex(int vert) {

	//init a vertex with a name and default values
	vertex* head;
	head = new vertex;

	if (parent.size() > vert) {
		// if the size of the parent is bigger than the number vertex,
		// assume vertex has been previously deleted and add back into old position which is a NULL pointer
		parent[vert - 1] = head;
		parent[vert - 1]->name = vert;
		parent[vert - 1]->known = 0;
		parent[vert - 1]->source = 0;
		parent[vert - 1]->weight = 0;
		parent[vert - 1]->nextAdjNode = NULL;

		vertexCount++;
	}
	else {
		parent.push_back(head);
		parent[vert - 1]->name = vert;
		parent[vert - 1]->known = 0;
		parent[vert - 1]->source = 0;
		parent[vert - 1]->weight = 0;
		parent[vert - 1]->nextAdjNode = NULL;

		vertexCount++;
	}

	cout << "Vertex: " << vert << " added." << endl;
	oFile << "Vertex: " << vert << " added." << endl;

	
}

void Graph::deleteVertex(int vert) {

	// read through the edges of each vertex in parent
	// if the edge name matches vert, delete it.
	// next delete the target vertex at parent vert-1
	// finally set vert-1 to NULL since it is a pointer

	vertex* temp;
	vertex* prev;
	vertex* del; 

	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] != NULL) {

			temp = parent[i]; 
			prev = parent[i]; 

			for (int j = 0; j < parent[i]->edges; j++) {
				temp = temp->nextAdjNode; 

				if (prev->nextAdjNode != temp) {
					prev = prev->nextAdjNode;
				}

				if (temp->name == vert) { 
					del = temp;
					temp = temp->nextAdjNode;
					prev->nextAdjNode = temp;
					// "delete edge x" message
					delete del;
					parent[i]->edges--; // decrement edge count of vertex
					break;
				}
				

			}
		}
	}

	// now to delete the vertex and set it's parent to NULL
	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] != NULL) {

			if (parent[i]->name == vert) {
				del = parent[i];
				parent[i] = NULL;
				delete del;
				break;
			}

		}
	}

	vertexCount--;


	cout << "Vertex: " << vert << " deleted." << endl;
	oFile << "Vertex: " << vert << " deleted." << endl;

}



void Graph::addEdge(int vert1, int vert2, int weight) {


	parent[vert1 - 1]->edges += 1;
	
	if (parent[vert1 - 1]->nextAdjNode == NULL) { // no edges
		parent[vert1 - 1]->nextAdjNode = new vertex;

		// in new edge
		parent[vert1 - 1]->nextAdjNode->name = vert2;
		parent[vert1 - 1]->nextAdjNode->known = 0;
		parent[vert1 - 1]->nextAdjNode->source = vert1;
		parent[vert1 - 1]->nextAdjNode->weight = weight;
		parent[vert1 - 1]->nextAdjNode->nextAdjNode = NULL;
	}
	else if (parent[vert1 - 1]->nextAdjNode != NULL) { // there are more edges

		// init utility pointers
		vertex* temp = parent[vert1 - 1]; // temp is pointing to vertex
		vertex* prev = parent[vert1 - 1];
		vertex* n;

		// traverse edges; insert in ascending order by weight
		while (true) {
			temp = temp->nextAdjNode;

			if (prev->nextAdjNode != temp) {
				prev = prev->nextAdjNode;
			}

			if (temp == NULL) { // end of the list
				temp = new vertex;
				prev->nextAdjNode = temp;

				temp->name = vert2;
				temp->known = 0;
				temp->source = vert1;
				temp->weight = weight;
				temp->nextAdjNode = NULL;
				break; // edge inserted. Done.
			} 
			else if (weight < temp->weight || weight == temp->weight) { // incoming edge is less than weight of temp OR equal to weight of temp 

				// Insert between: new creates a new node. previous points to new node. new node points to temp
				n = new vertex;
				prev->nextAdjNode = n;
				n->nextAdjNode = temp;

				n->name = vert2;
				n->source = vert1;
				n->known = 0;
				n->weight = weight;
				break; // edge inserted. Done
			}
		} // end while true
	} // end else if

	cout << "Edge added between Vertex " << vert1 << " and Vertex " << vert2 << " with a weight of: " << weight << endl;
	oFile << "Edge added between Vertex " << vert1 << " and Vertex " << vert2 << " with a weight of: " << weight << endl;
	
} // end addEgde



void Graph::deleteEdge(int vert1, int vert2) {
	
	vertex* temp;
	vertex* prev;
	vertex* del;
	temp = parent[vert1 - 1];
	prev = parent[vert1 - 1];

	while (true) {
	
		temp = temp->nextAdjNode;

		if (prev->nextAdjNode != temp) {
			prev = prev->nextAdjNode;
		}

		if (temp->name == vert2) {
			del = temp;
			temp = temp->nextAdjNode;
			prev->nextAdjNode = temp;
			delete del;
			parent[vert1 - 1]->edges--; // decrement edge count of vertex
			break;
		}
	}

	temp = parent[vert2 - 1];
	prev = parent[vert2 - 1];

	while (true) {

		temp = temp->nextAdjNode;

		if (prev->nextAdjNode != temp) {
			prev = prev->nextAdjNode;
		}

		if (temp->name == vert1) {
			del = temp;
			temp = temp->nextAdjNode;
			prev->nextAdjNode = temp;
			delete del;
			parent[vert2 - 1]->edges--; // decrement edge count of vertex
			break;
		}
	}

	cout << "Edge deleted between Vertex " << vert1 << " and Vertex " << vert2 << endl;
	oFile << "Edge deleted between Vertex " << vert1 << " and Vertex " << vert2 << endl;
}



void Graph::subtractWeight(int vert1, int vert2, int weight) {
	
	vertex* temp;
	temp = parent[vert1 - 1];

	while (true) {

		temp = temp->nextAdjNode;

		if (temp->name == vert2) {
			temp->weight = temp->weight - weight;
			break;
		}
	}

	// modify other vertex's edge weight as well
	temp = parent[vert2 - 1];

	while (true) {

		temp = temp->nextAdjNode;

		if (temp->name == vert1) {
			temp->weight = temp->weight - weight;
			break;
		}
	}

	cout << "Edge between Vertex " << vert1 << " and Vertex " << vert2 << " has been reduced by: " << weight << endl;
	oFile << "Edge between Vertex " << vert1 << " and Vertex " << vert2 << " has been reduced by: " << weight << endl;

}




void Graph::addWeight(int vert1, int vert2, int weight) {

	vertex* temp;
	temp = parent[vert1 - 1];

	while (true) {

		temp = temp->nextAdjNode;

		if (temp->name == vert2) {
			temp->weight = temp->weight + weight;
			break;
		}
	}

	// modify other vertex's edge weight as well
	temp = parent[vert2 - 1];

	while (true) {

		temp = temp->nextAdjNode;

		if (temp->name == vert1) {
			temp->weight = temp->weight + weight;
			break;
		}
	}

	cout << "Edge between Vertex " << vert1 << " and Vertex " << vert2 << " has been increased by: " << weight << endl;
	oFile << "Edge between Vertex " << vert1 << " and Vertex " << vert2 << " has been increased by: " << weight << endl;
}





vertex* Graph::getVertex(int howMany) { // testing
	return parent[howMany];
}





Graph::~Graph() {
	// free all alocated memory
	oFile << "Freeing Graph data" << endl;
	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] != NULL) {
			deleteVertex(i + 1);
		}
	}
}


