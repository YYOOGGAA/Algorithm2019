#ifndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <vector>
#include "node.h"

using namespace std;

class MaxHeap
{
public:
   MaxHeap(size_t s = 0) { if (s != 0) _data.reserve(s); }
   ~MaxHeap() {}

   size_t size() const { return _data.size(); }
   Node* getData(int i) {return _data[i];}

   // TODO
   Node& max() const {
      if (!_data.empty()) return *_data[0]; 
    }
   void insert(Node* d) {
      _data.push_back(d);
      d->setInHeap(true);
   }
   void delMax() {
      delData(0);  
   }
   void delData(size_t i) {
      _data[i]->setInHeap(false);
      _data[i] = _data.back();
      _data[i]->setHeapLoc(i);
      _data.pop_back();
      if(_data.empty()) return;
      size_t l;
      size_t r;
      size_t biggest;
      while(true)
      {
         l = 2*i+1;
         r = 2*i+2;
         biggest = i;
         if (l <= _data.size()-1 && *_data[l] > *_data[i])
         {
            biggest = l;
         }
         else biggest = i;
         if (r <= _data.size()-1 && *_data[r] > *_data[biggest])
         {
            biggest = r;
         }
         if (biggest == i) return;
         swap(_data[i], _data[biggest]);
         _data[i]->setHeapLoc(i);
         _data[biggest]->setHeapLoc(biggest);
         i = biggest;
      }
   }


   void IncreaseKey(int loc, int w)
   {
      int p = (loc-1)/2;
      _data[loc]->setKey(w);
      while(loc > 0 && *_data[loc] > *_data[p])
      {
         swap(_data[loc],  _data[p]);
         _data[p]->setHeapLoc(p);
         _data[loc]->setHeapLoc(loc);  
         loc = p;
         p = (loc-1)/2;       
      }
   }

private:
   // DO NOT add or change data members
   vector<Node*>   _data;
};

#endif // HEAP_H