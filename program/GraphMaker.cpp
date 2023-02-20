// Graph Maker
// Takes a set of data from a file and generates/modifies a weighted graph representation. Least costly path is modeled by an MST on screen.
// Xavier Eavsns
// 3/31/22

#include <iostream>
#include <vector>
#include <fstream>
#include "Graph.h"
#include "MST.h"
using namespace std;


// function recieves a string and returns an integer if it is valid
// if not valid, returns a special case number that will activate a case that terminates the program with a message

int getCase(string command) {

	if (command == "PG") {
		// Print Graph
		return 1;
	}
	else if (command == "PM") {
		// Print MST
		return 2;
	}
	else if (command == "IV") {
		// Insert Vertex
		return 3;
	}
	else if (command == "IE") {
		// Insert Edge
		return 4;
	}
	else if (command == "IW") {
		// Add Weight
		return 5;
	}
	else if (command == "DW") {
		// Subtract Weight
		return 6;
	}
	else if (command == "DV") {
		// Delete Vertex
		return 7;
	}
	else if (command == "DE") {
		// Delete Edge
		return 8;
	}
	else {
		// special case
		return 9;
	}

}




int main() {
	int V = 0; // ve indicates how many times we need to loop, looking for a verticy
	string vertex1 = "";
	string vertex2 = "";
	string vertex3 = "";
	string inFile = "";
	string command = "";
	bool failed = false;
	int caseNumber = 0;
	int E = 0; // indicates how many times we have to loop, looking for edge addition instructions
	int weight = 0;

	int verticy1 = 0;
	int verticy2 = 0;
	int verticy3 = 0;

	//Graph graph(V);
	
	ifstream iFile; // required test

	cout << "Enter the name of the initial File.(exclude file extention): " << endl;

	cin >> inFile;

	inFile = inFile + ".txt"; // add ext.

	iFile.open(inFile);

	// How many verticies
	iFile >> V;
	MST heap(V);


	if (!iFile.is_open()) {
		cout << "Failed to open: " << inFile << endl;
	}
	else { // continue program in here
		cout << "Starting..." << endl; 

		// add verticies
		for (int i = 0; i < V; i++) {

			iFile >> vertex1;
			if (vertex1.length() == 2) { // between 1 and 9 inclusive
				string number = "";
				number = number + vertex1.at(1); // extract number 
				verticy1 = stoi(number);
			}
			else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
				string temp = "";
				temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
				verticy1 = stoi(temp);
			}

			//graph.addVertex(verticy1); // add vertex 1
			heap.addVertex(verticy1); // add vertex 1  
		}



		// how many edges to add
		iFile >> E;

		for (int i = 0; i < E; i++) {

			// vertex 1
			iFile >> vertex1;

			if (vertex1.length() == 2) { // between 1 and 9 inclusive
				string number = "";
				number = number + vertex1.at(1); // extract number 
				verticy1 = stoi(number);
			}
			else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
				string temp = "";
				temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
				verticy1 = stoi(temp);
			}

			// vertex 2
			iFile >> vertex2;
			if (vertex2.length() == 2) { // between 1 and 9 inclusive
				string number = "";
				number = number + vertex2.at(1); // extract number 
				verticy2 = stoi(number);
			}
			else if (vertex2.length() == 3) { // is a between 10 and 100 inclusive
				string temp = "";
				temp = temp + vertex2.at(1) + vertex2.at(2); // extract numbers
				verticy1 = stoi(temp);
			}

			// weight
			iFile >> weight;

			heap.addEdge(verticy1, verticy2, weight);
			heap.addEdge(verticy2, verticy1, weight); //need to show edge in other vertex as well.
		}


		
		iFile.close();

		cout << "Enter the name of the Operations File.(exclude file extention): " << endl;

		cin >> inFile;

		inFile = inFile + ".txt"; // add ext.

		iFile.open(inFile);

		if (!iFile.is_open()) {
			cout << "Failed to open: " << inFile << endl;
		}
		else { 

			while (!iFile.eof()) {

				command = "";
				caseNumber = 0;

				iFile >> command; // read command

				if (command == "") {
					break;
				}

				// call function that returns a case number
				caseNumber = getCase(command);

				switch (caseNumber) {

				case 1:

					heap.printGraph();
					cout << "\n------------------------------------\n\n";

					break;

				case 2:

					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 3:

					iFile >> vertex1;
					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					//graph.addVertex(verticy1); // add vertex 1
					heap.addVertex(verticy1); // add vertex 1

					heap.printGraph(); 
					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 4:

					// vertex 1
					iFile >> vertex1;

					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// vertex 2
					iFile >> vertex2;
					if (vertex2.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex2.at(1); // extract number 
						verticy2 = stoi(number);
					}
					else if (vertex2.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex2.at(1) + vertex2.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// weight
					iFile >> weight;

					heap.addEdge(verticy1, verticy2, weight);
					heap.addEdge(verticy2, verticy1, weight); //need to show edge in other vertex as well.

					heap.printGraph();

					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 5:

					// vertex 1
					iFile >> vertex1;

					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// vertex 2
					iFile >> vertex2;
					if (vertex2.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex2.at(1); // extract number 
						verticy2 = stoi(number);
					}
					else if (vertex2.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex2.at(1) + vertex2.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// weight
					iFile >> weight;

					heap.addWeight(verticy1, verticy2, weight);

					heap.printGraph();
					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 6:

					// vertex 1
					iFile >> vertex1;

					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// vertex 2
					iFile >> vertex2;
					if (vertex2.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex2.at(1); // extract number 
						verticy2 = stoi(number);
					}
					else if (vertex2.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex2.at(1) + vertex2.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// weight
					iFile >> weight;

					heap.subtractWeight(verticy1, verticy2, weight); 

					heap.printGraph();
					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 7:

					iFile >> vertex1;
					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}
					
					heap.deleteVertex(verticy1);

					heap.printGraph();
					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 8:

					// vertex 1
					iFile >> vertex1;

					if (vertex1.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex1.at(1); // extract number 
						verticy1 = stoi(number);
					}
					else if (vertex1.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex1.at(1) + vertex1.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					// vertex 2
					iFile >> vertex2;
					if (vertex2.length() == 2) { // between 1 and 9 inclusive
						string number = "";
						number = number + vertex2.at(1); // extract number 
						verticy2 = stoi(number);
					}
					else if (vertex2.length() == 3) { // is a between 10 and 100 inclusive
						string temp = "";
						temp = temp + vertex2.at(1) + vertex2.at(2); // extract numbers
						verticy1 = stoi(temp);
					}

					heap.deleteEdge(verticy1, verticy2);

					heap.printGraph();
					heap.makeMST();
					cout << "\n------------------------------------\n\n";
					break;

				case 9:

					cout << "Command not recognized. Ending command read." << endl;
					failed = true;
					break;


				} // switch statement


				if (failed == true) {
					break;
				}

			} // end while
			
			


		} // end else



	} // end else

	cout << "Program terminated successfully!" << endl;
	return 0;
}