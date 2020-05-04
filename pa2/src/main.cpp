#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int MIS(vector<int>&, int, int);
void save(vector<int>&, int, int, vector<int>&);

vector<vector<int>> m;

int main(int argc, char* argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int num, _v;
    fin >> num;
    vector<int> vertice;
    while (fin >> _v)
        vertice.push_back(_v);

    vector<int> chord;
    chord.resize(num);
    for(int i = 0; i < num; i++)
    {
    	if (i % 2 == 0) chord[vertice[i]] = vertice[i+1];
    	else chord[vertice[i]] = vertice[i-1];
    }

    m.resize(num);
    for(int i = 0; i < num; i++)
    {
        m[i].resize(num);
    }

    vector<int> output;
    int _onum;
    _onum = MIS(chord,0,num-1);
    save(chord,0,num-1,output);

    fout << _onum << endl;
    for (int i = 0; i < output.size(); i++)
    {
        if (i%2 == 1) fout << output[i] << endl;
        else fout << output[i] << " ";
    }
    fin.close();
    fout.close();
}

int MIS(vector<int>& c, int i, int j)
{
    if (i >= j) return 0;

    int k = c[j];
    int r;
    if(m[i][j] != 0) return m[i][j];
    
	if (k >= i && k < j)
	{
		if (k == i) 
		{
            r = MIS(c, i+1, j-1) + 1;
            m[i][j] = r;
			return r;
		}
		else
		{
			int a = MIS(c,i,k-1)+1+MIS(c,k+1,j-1);
		    int b = MIS(c,i,j-1);
		    if (a > b)
		    {
                m[i][j] = a;
		    	return a;
		    }
			else {m[i][j] = b; return b;}
        }
	}
	else 
    {
        r = MIS(c,i,j-1);
        m[i][j] = r;
        return  r;
    }
}

void save(vector<int>& c, int i, int j, vector<int>& o)
{
    int k = c[j];
    if (i >= j) return;
    
    if(m[i][j] != 0)
    {
       if (k >= i && k < j)
       {
          if (k == i) 
          {
             o.push_back(k);
             o.push_back(j);
             save(c, i+1, j-1,o);
          }
          else
          {
             int a = m[i][k-1]+1+m[k+1][j-1];
             int b = m[i][j-1];
             if (a > b)
             {
                save(c, i, k-1,o);
                o.push_back(k);
                o.push_back(j);
                save(c, k+1, j-1,o);
             }
             else {save(c, i, j-1,o);}
          }
        }
        else 
        { 
          save(c,i,j-1,o);
        }
    }
}
