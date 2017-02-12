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

	for(vector<int>::iterator itr = graph[u].begin(); itr != graph[u].end(); ++itr)
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

vector< pair<double, double> > scf(const set<int> &down, const vector<int> &upOrder)
{
	vector< pair<double, double> > xy;
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

	active[134]=0;
	active[135]=0;
	
	file.close();

	for (set<int>::iterator i = down.begin(); i != down.end(); ++i)
	{
		active[(*i)]=0;
	}

	for(int i=0;i<upOrder.size();i++)
	{
		int id=upOrder[i];

		pair<int, int> output = query(id, 1);
		//cout<<output.first<<" "<<output.second<<endl;
		double scf = 1.0 * output.first / (N - 2);
		double fsa = 1.0 * output.second / (N - 2);
		//obj<<scf<<" "<<fsa<<endl;
		xy.push_back(make_pair(fsa, scf));
		//cout<<scf<<" "<<fsa<<endl;
	}
	return xy;
}

double area(const vector< pair<double, double> > &xy)
{
	double ans=0;
	for(int i=0;i<(int)xy.size()-1;i++)
	{
		ans+= ( ( (xy[i].first + xy[i+1].first) * abs(xy[i].second - xy[i+1].second) ) /2);
	}
	//cout<<ans<<endl;
	return ans;
}

int main()
{
	set<int> down;
	ifstream downFile("downStationList.txt");
	int n; //no. of stations down
	downFile>>n;
	for (int i = 0; i < n; ++i)
	{
		int temp;
		downFile>>temp;
		down.insert(temp);
	}
	vector<string> centrality;
	centrality.push_back("../Centrality/betweennessRank.txt");
	centrality.push_back("../Centrality/closenessRank.txt");
	centrality.push_back("../Centrality/eigenvector.txt");
	vector<double> areas;
	for(int i=0;i<centrality.size();i++)
	{
		vector<int> upOrder;
		ifstream upFile(centrality[i]);
		int s;//no.of stations
		upFile>>s;
		for (int j=0; j<s; j++)
		{
			int t;
			upFile>>t;
			if(down.find(t)!=down.end())
				upOrder.push_back(t);
		}
		areas.push_back(area(scf(down, upOrder)));
	}
	double min=INT_MAX;
	int res=-1;
	for (int i = 0; i < areas.size(); ++i)
	{
		cout<<centrality[i]<<"  "<<areas[i]<<endl;
		if(min>areas[i])
		{
			min=areas[i];
			res=i;
		}
	}
	cout<<"Use this:"<<centrality[res]<<endl;
	return 0;
}

