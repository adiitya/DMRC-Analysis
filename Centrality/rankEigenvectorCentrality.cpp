//this file calculates the eigenvector centrality of each node.
#include <bits/stdc++.h>
using namespace std;
#define N 151

int adj[N+2][N+2];

int main()
{
	vector<pair<double, int> > v;
	ifstream obj1("../Efficiency/adjacencyMatrix(aij).txt");
	
	string degreeFile = "rankData/degree.txt";
	ofstream degree(degreeFile);
	

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
		if(i + 1 != 134 && i + 1 != 135)
		degree<<(i+1) << ","<<b[i]<<endl;
				
		//cout<<i+1<<"-->"<<b[i]<<endl;
	}
	cout<<"Degree data written to \""<<degreeFile<<"\""<<endl;



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

	string outputFile1 = "rankData/eigenvectorRankActualValue.txt";
	ofstream obj2(outputFile1);

	for(int i = 0; i < N + 2; ++i)
	{
		if(v[i].second != 134 && v[i].second != 135)
		{
			obj2 << v[i].second << "," << v[i].first <<endl;
		}
	}
	cout << "Eigenvector centrality actual value written to \"" << outputFile1 << "\"" << endl;


	string outputFile = "rankData/eigenvectorRank.txt";
	ofstream obj(outputFile);

	obj<<N<<endl;
	for(int i=0;i<N+2;i++)
	{
		if(v[i].second!=134 && v[i].second!=135)
			obj<<v[i].second<<endl;
		//cout<<v[i].second<<"-->"<<v[i].first<<endl;
	}

	obj.close();

	cout << "Eigenvector centrality list written to \"" << outputFile << "\"" << endl;

	return 0;
} 