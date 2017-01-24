// A C / C++ program for Dijkstra's single source shortest
// path algorithm. The program is for adjacency matrix
// representation of the graph.
#include <stdio.h>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
 
// Number of vertices in the graph
#define V 154
 
// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(double dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
pair<int, int> countBet[V];

// Function to print shortest path from source to j
// using parent array
void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j]==-1){
        countBet[j].first++;
        return;
    }
    
    printPath(parent, parent[j]);
    
    countBet[j].first++;

    //printf("%d ", j);
}
 
// A utility function to print the constructed distance
// array
int printSolution(double dist[], int n, int parent[], int src)
{
    //printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        //printf("\n%d -> %d \t\t %d\t\t%d", src, i, dist[i], src);
        printPath(parent, i);
    }
    //printf("\n");
}
 
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(double graph[V][V], int src)
{
    double dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];
 
    // Parent array to store shortest path tree
    int parent[V];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 1; i < V; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
    parent[src] = -1;
    // print the constructed distance array
    printSolution(dist, V, parent, src);
}
 
// driver program to test above function
int main()
{
    for(int i=0;i<V;i++)
    {
        countBet[i]=make_pair(0, i);
    }
    /* Let us create the example graph discussed above */
    ifstream file("StationData/final_output.txt");
    string line;
    getline(file, line);
    int src,dest;
    double fare, time1, dist;
    double graph[V][V];
    for (int i = 0; i < 153; ++i)
    {
        file>>src>>dest>>fare>>time1>>dist;

        graph[src][dest] = dist;
    }
 
    for (int i = 1; i < V; ++i)
    {
        dijkstra(graph, i);   
    }
    sort(countBet, countBet+V, std::greater< pair<int, int> >());

    for(int i = 0; i < V; i++)
        printf("%d --> %d \n", countBet[i].second, countBet[i].first);

 
    return 0;
}
