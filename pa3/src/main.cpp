#include <iostream>
#include "nodeMgr.h"

using namespace std;

int main(int argc, char* argv[])
{
	NodeMgr nodeMgr;
	nodeMgr.read(argc, argv);
	//cerr << "read successfully" << endl;
	if (nodeMgr.getGraphType() == 'u')
	{
		nodeMgr.MST();
		//cerr << "MST successfully"<< endl;
		nodeMgr.output();
		//cerr << "output successfully" << endl;
	}
	else
	{
		size_t s = 1;
		while(nodeMgr.outputSize() != s)
		{
		   s = nodeMgr.outputSize();
           nodeMgr.DFS();
		   //cerr << "DFS successfully" << endl;
		   nodeMgr.cutEdge();
		   //cerr << "cutEdge successfully" << endl;
		   nodeMgr.reset();
		}
	}

	nodeMgr.write(argc, argv);
    //cerr << "write successfully"<<endl;
}