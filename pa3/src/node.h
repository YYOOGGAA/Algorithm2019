#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
#include "nodeMgr.h"

using namespace std;

class Node;
class Edge;

class Node
{
public:
    Node(int n) : 
       nodeNum(n), pre(0), key(-101), heapLoc(n), inHeap(false), finish(0), start(0), color("white") {}
    ~Node() {}

    friend class NodeMgr;
    
    bool operator == (const Node& n) const { return nodeNum == n.nodeNum; }
    bool operator != (const Node& n) const { return nodeNum != n.nodeNum; }
    bool operator > (const Node& n) const { return key > n.key; }

    int getNodeNum() const {return nodeNum;}
    int getKey() const {return key;}
    void setKey(int w) {key = w;}
    void setHeapLoc(int l) {heapLoc = l;}
    void setInHeap(bool i) {inHeap = i;}
    void setColor(string c) {color = c;}
private:
    int nodeNum;
    int key;
    int heapLoc;
    bool inHeap;
    int finish;
    int start;
    string color;
    Node* pre;
    vector<Edge*> edgeList;
    vector<Edge*> fanin;
    vector<Edge*> fanoutList;
};

class Edge
{
public:
    Edge(Node* c, int w) : connect(c), weight(w), found(false) {}
    ~Edge() {}

    Node* getConnect() {return connect;}
    int  getWeight() {return weight;}
    bool isfound() {return found;}

    void setFound(bool f) {found = f;}

private:
    Node* connect;
    int weight;
    bool found;
};

#endif  // NODE_H
