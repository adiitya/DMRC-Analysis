#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


const int MAX 			= 154;
const int INPUT_LINE 	= 151;
const int TOP 			= 50;


struct NodeRank
{
	int idx;
	int degree;
	string name;
	double betweennessRank;
	double closenessRank;
	double eigenvectorRank;
};


NodeRank data[MAX];
// 134, 135


bool comp(const NodeRank& lhs, const NodeRank& rhs)
{
	return lhs.betweennessRank + lhs.closenessRank + lhs.eigenvectorRank > 
			rhs.betweennessRank + rhs.closenessRank + rhs.eigenvectorRank;
}


int main()
{
	string dir = "rankData/";

	ifstream degree(dir + "degree.txt");
	ifstream betweennessRank(dir 	+ "betweennessRankActualValue.txt");
	ifstream closenessRank(dir 		+ "closenessRankActualValue.txt");
	ifstream eigenvectorRank(dir 	+ "eigenvectorRankActualValue.txt");
	ifstream stationName("../StationData/station_code_name.txt");

	char dump;
	int idx;
	int intData;
	double doubleData;
	for(int i = 0; i != INPUT_LINE; ++i)
	{
		stationName >> idx;
		getline(stationName, data[idx].name);

		data[i + 1].idx = i + 1;
		degree >> idx >> dump >> intData;
		data[idx].degree = intData;

		betweennessRank >> idx >> dump >> doubleData;
		data[idx].betweennessRank = doubleData;

		closenessRank >> idx >> dump >> doubleData;
		data[idx].closenessRank = doubleData;

		eigenvectorRank >> idx >> dump >> doubleData;
		data[idx].eigenvectorRank = doubleData;
	}

	degree.close();
	betweennessRank.close();
	closenessRank.close();
	eigenvectorRank.close();


	sort(data + 1, data + MAX, comp);

	ofstream output(dir + "topStation.txt");
	for(int i = 1; i <= TOP; ++i)
	{
		output << data[i].name << "," << data[i].degree << ",";
		output << data[i].betweennessRank << "," << data[i].closenessRank << ",";
		output << data[i].eigenvectorRank << endl;
	}

	output.close();
}