/*
 * This file calculates the global and local efficiency
 */


#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>


using namespace std;


const int INF 	= 50000;
const int N 	= 151;

const string NEW_EFFICIENCY 	= "../Novelty/";
const string OLD_EFFICIENCY 	= "./";

const string D_IJ = "allPairShortestPathMatrix(dij).txt";
const string A_IJ = "adjacencyMatrix(aij).txt";
const string L_IJ = "sphericalShortestPathMatrix(lij).txt";


double d[N + 2][N + 2];
double l[N + 2][N + 2];
double a[N + 2][N + 2];


// Flyod Warshall - All pair shortest path
// Used for calculating d_ij
void floyd(double** sd, int n)
{
	for(int k = 0; k < n; k++)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(sd[i][k] + sd[k][j] < sd[i][j])
				{
					sd[i][j] = sd[i][k] + sd[k][j];
				}
			}
		}
	}
}

double calculateNormalizedLocalEfficiency()
{
	double sum = 0;
	for(int c = 0; c < N + 2; c++)
	{
		//find neighbours
		set<int> nodes;
		for(int j = 0; j < N + 2; j++)
		{
			if(a[c][j] != 0)
			{
				nodes.insert(j);
			}
		}
		int n = nodes.size();
		if(n == 0 || n == 1) continue;
		//create adjacency matrices
		double sa[n][n];
		double **sd = new double*[n];
		double sl[n][n];
		for(int p = 0; p < n; p++)
		{
			sd[p] = new double[n];
			for(int q = 0; q < n; q++)
			{
				sa[p][q] = 0;
				sd[p][q] = INF;
				sl[p][q] = 0;
			}
		}
		int p = 0, q = 0;
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
					if(sd[i][j]==0){cout<<"c="<<c<<" sd "<<i<<" "<<j<<" = 0"<<endl;exit(0);}
					double temp=1/sd[i][j];
					sum1+=temp;
				}
				if(i!=j && sl[i][j]!=INF)
				{
					if(sl[i][j]==0){cout<<"c="<<c<<" sl "<<i<<" "<<j<<" = 0"<<endl;exit(0);}
					double t=1/sl[i][j];
					sum2+=t;			
				}
			}
		}
		/*if(n==1)
		{
			sum1+=0;
			sum2+=0;
		}
		else
		{
			sum1=sum1/(n*(n-1));
			sum2=sum2/(n*(n-1));
		}*/
		//if(sum1/sum2 !=0)cout<<"see"<<(sum1/sum2)<<endl;
		sum+=(sum1/sum2);
	}
	sum=sum/N;

	return sum;
	//cout<<"E(norm_local) = "<<setprecision(15)<<sum<<endl;
}

struct Efficiency
{
	double global;
	double idle;
	double normalizedGlobal;
	double normalizedLocal;
};

/*
 * 1. a_ij -> Adjacency matrix with weigted edges
 * 2. l_ij -> Geo-distance matrix i.e. calculated using latitutes and longitudes
 * 3. d_ij -> Distance matrix calculated using path length
 */
Efficiency calculateEfficiency(string a_ij, string l_ij, string d_ij)
{
	ifstream obj1(a_ij);
	ifstream obj2(l_ij);
	ifstream obj3(d_ij);

	for(int i = 0; i < N + 2; i++)
	{
		for(int j = 0; j < N + 2; j++)
		{
			obj1 >> a[i][j];
			obj2 >> l[i][j];
			obj3 >> d[i][j];
		}
	}

	obj1.close();
	obj2.close();
	obj3.close();

	double sum1 = 0;
	double sum2 = 0;
	for(int i = 0; i < N + 2; i++)
	{
		for(int j = 0; j < N + 2; j++)
		{
			if(i != j && d[i][j] != -1)
			{
				if(d[i][j] == 0)
				{
					cout<<"d "<<i<<" "<<j<<" = 0"<<endl;
					exit(0);
				}

				double temp = 1 / d[i][j];
				sum1 += temp;
			}

			if(i != j && l[i][j] != -1)
			{
				if(l[i][j] == 0)
				{
					cout<<"l "<<i<<" "<<j<<" = 0"<<endl;
					exit(0);
				}

				double t = 1 / l[i][j];
				sum2 += t;			
			}
		}
	}

	sum1 = sum1 / (N * (N - 1));
	sum2 = sum2 / (N * (N - 1));

	Efficiency efficiency;
	efficiency.global 	= sum1;
	efficiency.idle 	= sum2;
	efficiency.normalizedGlobal 	= sum1 / sum2;
	efficiency.normalizedLocal 		= calculateNormalizedLocalEfficiency();

	return efficiency;
}

inline double percentageImprovement(double original, double improved)
{
	return 100.0 * (improved - original) / original;
}

void printCompareEfficiency(Efficiency original, Efficiency improved)
{
	cout << "\n***** Efficiency Calculations *****\n" << endl;

	cout << left;

	cout << setw(20) << "Efficiency";
	cout << setw(15) << "Original";
	cout << setw(15) << "Improved";
	cout << setw(15) << "% Increased" << endl;
	cout << endl;

	cout << setw(20) << "Global";
	cout << setw(15) << original.global;
	cout << setw(15) << improved.global;
	cout << setw(15) << percentageImprovement(original.global, improved.global) << endl;

	cout << setw(20) << "Normalized Global";
	cout << setw(15) << original.normalizedGlobal;
	cout << setw(15) << improved.normalizedGlobal;
	cout << setw(15) << percentageImprovement(original.normalizedGlobal, improved.normalizedGlobal) << endl;

	cout << setw(20) << "Normalized Local";
	cout << setw(15) << original.normalizedLocal;
	cout << setw(15) << improved.normalizedLocal;
	cout << setw(15) << percentageImprovement(original.normalizedLocal, improved.normalizedLocal) << endl;

	cout << right;
}

int main()
{
	clock_t start = clock();

	string l_ij = L_IJ;
	
	string a_ij = OLD_EFFICIENCY + A_IJ;
	string d_ij = OLD_EFFICIENCY + D_IJ;

	Efficiency original = calculateEfficiency(a_ij, l_ij, d_ij);

	a_ij = NEW_EFFICIENCY + A_IJ;
	d_ij = NEW_EFFICIENCY + D_IJ;

	Efficiency improved = calculateEfficiency(a_ij, l_ij, d_ij);

	printCompareEfficiency(original, improved);

	clock_t timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;
	cout << "\nTime Elapsed: " << timeElapsed << " ms\n" << endl;
	
	return 0;
}