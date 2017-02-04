#include <bits/stdc++.h>
using namespace std;

#define MAX 154

double x[MAX];
double y[MAX];

int main()
{
	cout<<"Enter file containing x y values for area calculation\n>";
	string f;
	cin>>f;
	ifstream file1(f.c_str());
	int n;
	file1>>n;
	for (int i = 0; i < n; ++i)
	{
		file1>> x[i] >> y[i];
	}
	double area=0;
	for(int i=0;i<n-1;i++)
	{
		area+=(((x[i]+x[i+1])*abs(y[i+1]-y[i]))/2);
		cout<<area<<endl;
	}
	cout<<area<<endl;
	return 0;
}