/*This file calculates the global and local effieciency
  */
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
#define INF 50000
const int N=151;
double d[N+2][N+2];
double l[N+2][N+2];
double a[N+2][N+2];

void floyd(double **sd, int n)
{
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(sd[i][k]+sd[k][j]<sd[i][j])
				{
					sd[i][j]=sd[i][k]+sd[k][j];
				}
			}
		}
	}
}

void eloc()
{
	double sum=0;
	for(int c=0;c<N+2;c++)
	{
		//find neighbours
		set<int> nodes;
		for(int j=0;j<N+2;j++)
		{
			if(a[c][j]!=0)
			{
				nodes.insert(j);
			}
		}
		int n=nodes.size();
		if(n==0)continue;
		//create adjacency matrices
		double sa[n][n];
		double **sd=new double*[n];
		double sl[n][n];
		for(int p=0;p<n;p++)
		{
			sd[p]=new double[n];
			for(int q=0;q<n;q++)
			{
				sa[p][q]=0;
				sd[p][q]=INF;
				sl[p][q]=0;
			}
		}
		int p=0,q=0;
		for(set<int>::iterator it1=nodes.begin();it1!=nodes.end();it1++)
		{
			q=0;
			for(set<int>::iterator it2=nodes.begin();it2!=nodes.end();it2++)
			{
				if((*it1)!=(*it2))
				{
					sa[p][q]=a[*it1][*it2];
					if(sa[p][q]==1)sd[p][q]=d[*it1][*it2];
					sl[p][q]=l[*it1][*it2];
				}
				else
				{
					sd[p][q]=0;
				}
				q++;
			}
			p++;
		}
		//apply floyd-warshall on saij to get sdij
		floyd(sd,n);
		double sum1=0;
		double sum2=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(i!=j && sd[i][j]!=INF)
				{
					if(sd[i][j]==0){cout<<"c="<<c<<" sd "<<i<<" "<<j<<" = 0"<<endl;return;}
					double temp=1/sd[i][j];
					sum1+=temp;
				}
				if(i!=j && sl[i][j]!=INF)
				{
					if(sl[i][j]==0){cout<<"c="<<c<<" sl "<<i<<" "<<j<<" = 0"<<endl;return;}
					double t=1/sl[i][j];
					sum2+=t;			
				}
			}
		}
		if(n==1)
		{
			sum1=1;
			sum2=1;
		}
		else
		{
			sum1=sum1/(n*(n-1));
			sum2=sum2/(n*(n-1));
		}
		sum+=(sum1/sum2);
	}
	sum=sum/N;
	cout<<"E(norm_local) = "<<sum<<endl;
}

int main()
{
	clock_t st=clock();
	ifstream obj1("allPairShortestPathMatrix(dij).txt");
	ifstream obj2("sphericalShortestPathMatrix(lij).txt");
	ifstream obj3("AdjacencyMatrix(aij).txt");
	for(int i=0;i<N+2;i++)
	{
		for(int j=0;j<N+2;j++)
		{
			obj1>>d[i][j];
			obj2>>l[i][j];
			obj3>>a[i][j];
		}
	}
	double sum1=0;
	double sum2=0;
	for(int i=0;i<N+2;i++)
	{
		for(int j=0;j<N+2;j++)
		{
			if(i!=j && d[i][j]!=-1)
			{
				if(d[i][j]==0){cout<<"d "<<i<<" "<<j<<" = 0"<<endl;return 0;}
				double temp=1/d[i][j];
				sum1+=temp;
			}
			if(i!=j && l[i][j]!=-1)
			{
				if(l[i][j]==0){cout<<"l "<<i<<" "<<j<<" = 0"<<endl;return 0;}
				double t=1/l[i][j];
				sum2+=t;			
			}
		}
	}
	sum1=sum1/(N*(N-1));
	sum2=sum2/(N*(N-1));
	cout<<"E(global) = "<<sum1<<endl;
	cout<<"E(idle) = "<<sum2<<endl;
	cout<<"E(norm_global) = "<<sum1/sum2<<endl;
	eloc();
	clock_t difftime=(double)(clock()-st)/CLOCKS_PER_SEC*1000;
	cout<<"time taken:- "<<difftime<<endl;
	return 0;
}
/*
1. aij -> adjacency matrix with weigted edges
2. dij -> distance matrix calculated using path length
3. lij -> geodistance matrix i.e. calculated using latitutes and longitudes
*/