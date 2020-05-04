#ifndef NODE_MGR_H
#define NODE_MGR_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#include "node.h"
#include "heap.h"

class NodeMgr
{
public:
	NodeMgr() {}
	~NodeMgr() {}

	char getGraphType() {return graphType;}
	int  getNumNode() {return numNode;}
	int  getNumEdge() {return numEdge;}
	Node* getNode(int i) {return nodeList[i];}

	void read(int, char**);
	void write(int, char**);
	void MST();
	void output();
	void DFSVisit(Node*);
	void DFS();
	void cutEdge();
	size_t outputSize() {return outputEdge.size();}
	void reset();

private:
	char graphType;
	int  numNode;
	int  numEdge;
	int  outputW;
	int  _time;
	vector<int> outputEdge;
	vector<Node*> nodeList;
    MaxHeap heap;
};


#endif  // NODE_MGR_H