#include <iostream>
#include <vector>
#include <fstream>
#include "nodeMgr.h"
#include "node.h"

using namespace std;

void 
NodeMgr::read(int argc, char* argv[])
{
	fstream fin(argv[1]);
	fin >> graphType >> numNode >> numEdge;
	nodeList.resize(numNode);
	int node1, node2, w;
    for (int i = 0; i < getNumEdge(); i++)
    {
    	fin >> node1 >> node2 >> w;
    	if (nodeList[node1] == 0)
    	{
    		nodeList[node1] = new Node(node1);
    	}
    	if (nodeList[node2] == 0)
    	{
    		nodeList[node2] = new Node(node2);
    	}
    	Edge* fout = new Edge(nodeList[node2], w);
    	if (getGraphType() == 'u')
    	{
           Edge* fin = new Edge(nodeList[node1], w);
           nodeList[node1]->edgeList.push_back(fout);
           nodeList[node2]->edgeList.push_back(fin);
    	}
        else
        {
           nodeList[node1]->fanoutList.push_back(fout);
           _time = 0;
        }
    }
    outputW = 0;
    fin.close();
}

void
NodeMgr::write(int argc, char* argv[])
{
    fstream fout;
    fout.open(argv[2],ios::out);

    fout << outputW << endl;
    for(int i = 0; i < outputEdge.size(); i++)
    {
        if(i % 3 == 2) fout << outputEdge[i] << "\n";
        else fout << outputEdge[i] << " ";
    }
    fout.flush();
    fout.close();
}



void
NodeMgr::MST()
{
    nodeList[0]->key = 0;
    for (int i = 0; i < getNumNode(); i++)
    {
        heap.insert(nodeList[i]);
    }
    while(heap.size())
    {
        Node& u = heap.max();
        heap.delMax();
        if(!u.edgeList.empty())
        {
            for(int i = 0; i < u.edgeList.size(); i++)
            {
                Edge* e = u.edgeList[i];
                Node& v = *(e->getConnect());
                int w = e->getWeight();
                if(v.inHeap && w > v.getKey())
                {
                    v.pre = &u;
                    heap.IncreaseKey(v.heapLoc, w);
                    //break;
                }
            }
        }
    }
}

void
NodeMgr::output()
{
    outputW = 0;
    for(int i = 0; i < getNumNode(); i++)
    {
        Node* n1 = nodeList[i];
        for(int j = 0; j < n1->edgeList.size(); j++)
        {
            Edge* e = n1->edgeList[j];
            Node* n2 = e->getConnect();
            if(n1 != n2->pre && n2 != n1->pre)
            {
                if(n2->getNodeNum() > n1->getNodeNum())
                {
                    outputEdge.push_back(n1->getNodeNum());
                    outputEdge.push_back(n2->getNodeNum());
                    outputEdge.push_back(e->getWeight());
                    outputW += e->getWeight();
                }
            }
        }
    }
}

void
NodeMgr::reset()
{
    for(int i = 0; i < getNumNode(); i++)
    {
        nodeList[i]->setColor("white");
        nodeList[i]->pre = 0;
        nodeList[i]->start = 0;
        nodeList[i]->finish = 0;
        nodeList[i]->fanin.clear();
    }
    _time = 0;
}

void
NodeMgr::DFS()
{
    for(int i = 0; i < getNumNode(); i++)
    {
       if(nodeList[i]->color == "white")
          DFSVisit(nodeList[i]);
    }
}

void
NodeMgr::DFSVisit(Node* root)
{
   if(root->color == "black") return;
   if(root->color == "white")//not discovered yet
   {
      root->color = "gray";
      _time++;
      root->start = _time;
   }
   for(int i = 0; i < root->fanoutList.size(); i++)
   {
      Node* _new = root->fanoutList[i]->getConnect();
      if (root->fanoutList[i]->isfound() == true) continue;
      if(_new->color == "white")
      {
         _new->pre = root;
         Edge* fin = new Edge(root, root->fanoutList[i]->getWeight());
         _new->fanin.push_back(fin);
         _new->fanin.push_back(root->fanoutList[i]);
         _new->color = "gray";
         _time++;
         _new->start = _time;
         DFSVisit(_new);
      }
   }
   root->color = "black";
   _time++;
   root->finish = _time;
}

void
NodeMgr::cutEdge()
{
    for(int i = 0; i < getNumNode(); i++)
    {
        //cerr << "Node num: " << i << endl; 
        Node* n1 = nodeList[i];
        for(int j = 0; j < n1->fanoutList.size(); j++)
        {
           bool run = false;
           Edge* e = n1->fanoutList[j];
           Node* n2 = e->getConnect();
           //cerr << "connect with " << n2->getNodeNum()<<endl;
           if(n1->finish < n2->finish && e->isfound() == false) //cycle exist
           {
              int smallest = e->getWeight();
              Node* currentN = n1; 
              while(currentN != n2)
              {
                 Edge* currentE = currentN->fanin[0];
                 if(currentE->getWeight() < smallest)
                 {
                    run = true;
                    smallest = currentE->getWeight();
                    e = currentN->fanin[1];
                 }
                 currentN = currentN->pre;
              }
              if(e->isfound() == false)
              {
                e->setFound(true);
                outputW += smallest;
                Node* need = e->getConnect();
                if(run == true)
                {
                  Node* p = need->fanin[0]->getConnect();
                  outputEdge.push_back(p->getNodeNum());
                  outputEdge.push_back(need->getNodeNum());
                }
                else
                {
                  outputEdge.push_back(n1->getNodeNum());
                  outputEdge.push_back(n2->getNodeNum());
                }
                outputEdge.push_back(smallest);
              }
           }
        }
    }
}