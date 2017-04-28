#include <bits/stdc++.h>

using namespace std;



const int MAX = 154;
const int NUM_OF_EDGE = 250;
const int THRESHOLD_DIST = 10;
const int THRESHOLD_DIFF = 8;


double w[MAX][MAX];
double dist[MAX][MAX];
double longdist[MAX][MAX];
int aij[MAX][MAX];


void floyd(double sd[MAX][MAX], int n)
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(sd[i][k]+sd[k][j]<sd[i][j])
				{
					sd[i][j]=sd[i][k]+sd[k][j];
				}
			}
		}
	}
}


int main()
{
	ifstream edge("../StationData/final_output.txt");
	ifstream lij("../Efficiency-Calc/sphericalShortestPathMatrix(lij).txt");

	string temp;
	getline(edge, temp);

	int N = 153;
	int u, v;
	double f,t,d;
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			w[i][j] = 1e9;

	for(int i = 0; i < N; ++i)
	{
		edge>>u>>v>>f>>t>>d;
		w[u][v] = d;
		w[v][u] = d;
		w[u][u] = 0;
		w[v][v] = 0;
		aij[u][v]=1;
		aij[v][u]=1;
		aij[u][u]=0;
		aij[v][v]=0;
	}

	for(int i = 0; i < N; ++i)
		for(int j = 0 ; j < N; ++j)
			lij>>longdist[i + 1][j + 1];

	int a = 0;
	vector<pair<int, int> > newedge;
	while(a < NUM_OF_EDGE)
	{
		for(int j = 1; j <= N; ++j)
			for(int k = 1; k <= N; ++k)
				dist[j][k] = w[j][k];

		floyd(dist, N);
		//for(int j = 1; j <= N; ++j)
		//	for(int k = 1; k <= N; ++k)
		//		cout<<dist[j][k]<<endl;

		//	return 0;
		int s = 0, e = 0;
		double prev = -1;
		for(int j = 1; j <= N; ++j)
		{
			for(int k = 1; k <= N; ++k)
			{
				if(k == 134 || k == 135 || j == 134 || j == 135) continue;

				if(longdist[j][k] < THRESHOLD_DIST && w[j][k] == 1e9)
				{//	cout<<dist[j][k]<<" "<<longdist[j][k]<<endl;
					//cout<<(dist[j][k] - longdist[j][k])<<endl;
					//cout<<"hell"<<endl;
					if((dist[j][k] - longdist[j][k]) > prev)
						prev = dist[j][k] - longdist[j][k], s = j, e = k;
				}
			}
		}

		newedge.push_back(pair<int, int>(s, e));
		if(s == 0 && e == 0)
			cout<<"No new edge"<<endl;

		w[s][e] = longdist[s][e];
		w[e][s] = longdist[s][e];
		aij[s][e]=1;
		aij[e][s]=1;

		a++;
	}

	floyd(dist, N);
	ofstream dij("allPairShortestPathMatrix(dij).txt");
	ofstream obj("adjacencyMatrix(aij).txt");
	dij.precision(3);
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=N;j++)
		{
			dij<<fixed<<((dist[i][j]>=1e9)?-1:dist[i][j])<<" ";
			obj<<aij[i][j]<<" ";
		}
		dij<<endl;
		obj<<endl;
	}




	/*for(int i = 0; i < newedge.size(); ++i)
		cout<<newedge[i].first<<" "<<newedge[i].second<<endl;*/


}