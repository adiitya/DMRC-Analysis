#include <bits/stdc++.h>

using namespace std;

const int MAX = 155;
const int N = 153;

vector<int> graph[MAX];
bool active[MAX];
bool vis[MAX];
int comp[MAX];
int compSZ[MAX];

void dfs(int u, int c)
{
	vis[u] = 1;
	comp[u] = c;

	for(auto itr = graph[u].begin(); itr != graph[u].end(); ++itr)
		if(active[*itr] && !vis[*itr])
			dfs(*itr, c);
}

pair<int, int> query(int v, bool type)
{

	active[v] = type;
	for(int i = 1; i <= N; ++i)
		vis[i] = 0, compSZ[i] = 0;

	int c = 1;
	for(int i = 1; i <= N; ++i)
		if(active[i] && !vis[i])
			dfs(i, c++);
	
	//cout<<c-1<<endl;
	for(int i = 1; i <= N; ++i)
		if(active[i])
			compSZ[comp[i]]++;

	int ans = compSZ[1];
	for(int i = 1; i < c; ++i)
		ans = max(ans, compSZ[i]);

	int cc = 0;
	for(int i = 1; i <= N; ++i)
		cc += active[i];

	return pair<int, int>(ans, cc);
}

int main()
{
	ifstream file("../StationData/final_output.txt");
	string s;
	getline(file, s);
	
	int u, v;
	double a, b, c;	
	for(int i = 1; i <= 153; ++i)
	{
		file>>u>>v>>a>>b>>c;
		graph[u].push_back(v);
		graph[v].push_back(u);
		active[u] = 1;
		active[v] = 1;
	}
	file.close();


	cout<<"Enter file name\n>";
	string f;
	cin>>f;

	ifstream file2("../Centrality/" + f);
	cout<<"Type of query:"<<endl;
	int type;
	cin>>type;
	int q;
	file2>>q;

	while(q--)
	{
		int id;//, type;
		file2>>id;//>>type;

		pair<int, int> output = query(id, type);
		//cout<<output.first<<" "<<output.second<<endl;
		double scf = 1.0 * output.first / (N - 2);
		double fsa = 1.0 * output.second / (N - 2);

		cout<<scf<<" "<<fsa<<endl;
	}

	file2.close();
}