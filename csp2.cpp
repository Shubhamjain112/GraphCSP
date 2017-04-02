#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sys/time.h>
#include <queue>
using namespace std;

int V ;

bool revise(vector<vector<int> > &graph,vector<vector<int> > &domains,int x,int y)
{
	int i,j;
	bool revised = 0;
	for(i=0;i<domains[x].size();i++)
	{
		for(j=0;j<domains[y].size();j++)
		{
			if(domains[x][i]!=domains[y][j])
			{
				break;
			}
		}
		if(j==domains[y].size())
		{
			domains[x].erase(domains[x].begin()+i);
			revised = 1;
		}
	}
	return revised;
}

bool AC3(vector<vector<int> > &graph,vector<vector<int> > &domains,queue<pair<int,int> > &arcs)
{
	//cout<<"here";
	V = graph.size();
	while(!arcs.empty())
	{
		pair<int,int> temp = arcs.front();
		arcs.pop();
		int x = temp.first;
		int y = temp.second;
		if(revise(graph,domains,x,y))
		{
			if(domains[x].size()==0)
				return 0;
			for(int i=0;i<V;i++)
			{
				if(graph[x][i]==1&&i!=y)
					arcs.push(make_pair(i,x));
			}
		}
	}
	return 1;
}

bool isSafe (int v, vector<vector<int> > &graph, int color[], int c)
{
	V = graph.size();
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

void printSolution(int color[])
{
    cout<<"Solutions Exists with the Following Assignment : "<<endl;
    for (int i = 0; i < V; i++)
      cout<<color[i]<<" ";
    cout<<endl;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/

void forward(int v, vector<vector<int> > &graph,vector<vector<int> > &domains, int c)
{
	//cout<<"here";
	int i,j;
	int V = graph.size();
	for(i=0;i<V;i++)
	{
		if(graph[v][i]==1)
		{
			domains[i].erase(std::remove(domains[i].begin(), domains[i].end(),c), domains[i].end());
		}
	}
}

bool graphColoringUtil2(vector<vector<int> > &graph, int m, int color[], int v,vector<vector<int> > &domains)
{
	V = graph.size();
    if (v == V)
        return true;

    for(int i=0;domains[v].size();i++)
    {
    	if(isSafe(v,graph,color,domains[v][i]))
    	{
    		color[v] = domains[v][i];
    		vector<vector<int> > d = domains;
    		forward(v,graph,domains,domains[v][i]);
    		if (graphColoringUtil2 (graph, m, color, v+1,domains) == true)
             	return true;	
         	domains = d;
    		color[v]=0;
    	}
    }
    return false;
}

bool BTF(vector<vector<int> > &graph, int m,vector<vector<int> > &domains)
{
	V = graph.size();
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;
 
    if (graphColoringUtil2(graph, m, color, 0,domains) == false)
    {
      cout<<"Solution doesnt exists";
      return false;
    }

    printSolution(color);
    return true;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/
bool graphColoringUtil3(vector<vector<int> > &graph, int m, int color[], int v,vector<vector<int> > &domains, queue<pair<int,int> > &arcs)
{
	V = graph.size();
    if (v == V)
        return true;

    for(int i=0;domains[v].size();i++)
    {
    	if(isSafe(v,graph,color,domains[v][i]))
    	{
    		color[v] = domains[v][i];
    		vector<vector<int> > d = domains;
    		for(int j=0;j<V;j++)
    		{
    			if(graph[v][j]==1&&color[j]==0)
    				arcs.push(make_pair(j,v));
    		}
    		AC3(graph,domains,arcs);
    		if (graphColoringUtil3 (graph, m, color, v+1,domains,arcs) == true)
             	return true;	
         	domains = d;
    		color[v]=0;
    	}
    }
    return false;
}
bool BTM(vector<vector<int> > &graph, int m,vector<vector<int> > &domains,queue<pair<int,int> > &arcs)
{
	V = graph.size();
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;
 
    if (graphColoringUtil3(graph, m, color, 0,domains,arcs) == false)
    {
      cout<<"Solution doesnt exists";
      return false;
    }

    printSolution(color);
    return true;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/

bool min_conflicts(vector<vector<int> > &graph, int m,vector<vector<int> > &domains)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/
 
bool graphColoringUtil(vector<vector<int> > &graph, int m, int color[], int v)
{
	V = graph.size();
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, graph, color, c))
        {
           color[v] = c;

           if (graphColoringUtil (graph, m, color, v+1) == true)
             return true;

           color[v] = 0;
        }
    }

    return false;
}

bool BT(vector<vector<int> > &graph, int m)
{
  
  	V = graph.size();
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;
 
    if (graphColoringUtil(graph, m, color, 0) == false)
    {
      cout<<"Solution doesnt exists";
      return false;
    }

    printSolution(color);
    return true;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------*/


int main()
{
	vector<vector<int> > domains;
	timeval tv1;
	timeval tv2;
	int i,j,t;
	int n = 6;
	fstream fin;
	queue<pair<int,int> > arcs;
	queue<pair<int,int> > arcs2;
	fin.open("input.txt");
	int a;
	vector<vector<int> > graph(n,vector<int> (n));
	vector<int> v;
	cout<<"Enter Graph : "<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fin>>a;
			if(a==1)
				arcs.push(make_pair(i,j));
			graph[i][j] = a;
		}
	}
	int k = arcs.size()/2;
	for(i=0;i<k;i++)
		arcs.pop();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	V = n;
	int m = 3;
	for(j=0;j<n;j++)
	{
		for(i=1;i<=m;i++)
		{
			v.push_back(i);
		}
		domains.push_back(v);
		v.clear();
	}
	do
	{	
		cout<<"Choose from the following options : "<<endl;
		cout<<"1. Back Tracking "<<endl;
		cout<<"2. Back Tracking with forward checking "<<endl;
		cout<<"3. Back Tracking with MAC "<<endl;
		cout<<"4. Minimum Conflicts "<<endl;
		cout<<"5. Exit "<<endl;
		cin>>t;
		if(t==1)
		{
			BT(graph,m);
		}
		else if(t==2)
		{
			BTF(graph,m,domains);
		}
		else if(t==3)
		{
			BTM(graph,m,domains,arcs2);
		}
		else if(t==4)
		{
			min_conflicts(graph,m,domains);
		}
		else if(t==5)
		{
			cout<<"Exitting"<<endl;
		}
		else
		{
			cout<<"Invalid Option : "<<endl;
		}
	}while(t!=5);
	return 0;
}