//This file calculates the closeness centrality of each station by finding the inverse of 
//average shortest distance of each node from every other node.

#include <bits/stdc++.h>
using namespace std;
#define N 151 //no.of nodes in the network


int main()
{
	ifstream obj1("../Efficiency-calc/AllPairShortestPathMatrix(dij).txt");
	vector<pair<double, int> > close;
	for(int i=1;i<=N+2;i++)
	{
		double sum=0;
		for(int j=1;j<=N+2;j++)
		{
			double val;
			obj1>>val;
			if(val!=-1)
				sum+=val;
		}
		sum/=N-1;
		close.push_back(make_pair(1/sum, i));
	}
	sort(close.begin(), close.end(), greater<pair<double, int> >() );
	for(int i=0;i<close.size();i++)
	{
		cout<<close[i].second<<"-->"<<close[i].first<<endl;
	}
	return 0;
} 