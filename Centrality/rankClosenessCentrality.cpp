//This file calculates the closeness centrality of each station by finding the inverse of 
//average shortest distance of each node from every other node.

//NOTE : Remove stations 134 and 135 from the output of this file as these stations are non exiting.
#include <bits/stdc++.h>
using namespace std;
#define N 151 //no.of nodes in the network


int main()
{
	ifstream obj1("../Efficiency/allPairShortestPathMatrix(dij).txt");
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

	string outputFile1 = "rankData/closenessRankActualValue.txt";
	ofstream obj2(outputFile1);
	for(int i = 2; i < (int)close.size(); ++i)
	{
		obj2<<close[i].second<<"," << close[i].first << endl;
	}
	cout << "Closeness centrality actual value written to \"" << outputFile1 << "\"" << endl;

	string outputFile = "rankData/closenessRank.txt";
	ofstream obj(outputFile);
	
	obj<<N<<endl;
	for(int i=2;i<(int)close.size();i++)
	{
		obj<<close[i].second<<endl;
		//cout<<close[i].second<<"-->"<<close[i].first<<endl;
	}
	
	obj.close();
	
	cout << "Closeness centrality list written to \"" << outputFile << "\"" << endl;
	return 0;
} 