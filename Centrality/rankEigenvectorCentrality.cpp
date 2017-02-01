//this file calculates the eigenvector centrality of each node.
#include <bits/stdc++.h>
using namespace std;
#define N 151

int adj[N+2][N+2];

int main()
{
	vector<pair<double, int> > v;
	ifstream obj1("../Efficiency-Calc/AdjacencyMatrix(aij).txt");
	double b[N+2];
	for(int i=0;i<N+2;i++)
	{
		int sum=0;
		for(int j=0;j<N+2;j++)
		{
			obj1>>adj[i][j];
			sum+=adj[i][j];
		}
		b[i]=sum;
		//cout<<i+1<<"-->"<<b[i]<<endl;
	}
	double n=0;
	for(int i=0;i<N+2;i++)
	{
		n+=(b[i]*b[i]);
	}
	n=sqrt(n);
	for(int i=0;i<N+2;i++)
	{
		b[i]=b[i]/n;
	}
	for(int itr=0;itr<5;itr++)
	{
		double temp[N+2];
		for(int i=0;i<N+2;i++)
		{
			temp[i]=0;
			for(int j=0;j<N+2;j++)
			{
				temp[i]+=(adj[i][j]*b[i]);
			}
		}
		double norm=0;
		for(int i=0;i<N+2;i++)
		{
			norm+=(temp[i]*temp[i]);
		}
		norm=sqrt(norm);
		//cout<<norm<<endl;
		for(int i=0;i<N+2;i++)
		{
			b[i]=temp[i]/norm;
		}
	}
	for(int i=0;i<N+2;i++)
	{
		v.push_back(make_pair(b[i],i+1));
	}
	sort(v.begin(), v.end(), greater<pair<double, int> >());
	ofstream obj("eigenvector.txt");
	obj<<N<<endl;
	for(int i=0;i<N+2;i++)
	{
		if(v[i].second!=134 && v[i].second!=135)
			obj<<v[i].second<<endl;
		//cout<<v[i].second<<"-->"<<v[i].first<<endl;
	}
	return 0;
} 