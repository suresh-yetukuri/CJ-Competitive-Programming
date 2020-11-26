// DijkstrasAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
using graph_type = vector<vector<int>>;

int getMinVertex(vector<bool>& visited, vector<int>& distance)
{
	int min_distance_vertex = -1;
	for (int iCounter = 0; iCounter < visited.size(); ++iCounter)
	{
		if (!visited[iCounter] && (min_distance_vertex == -1 || distance[iCounter] < distance[min_distance_vertex]))
			min_distance_vertex = iCounter;
	}

	return min_distance_vertex;
}


void dijkstras(graph_type& pInput, int nVertices, int nEdges)
{
	vector<bool> visited(nVertices, false);
	vector<int> distance(nVertices, INT_MAX);
	distance[0] = 0;

	for (int iCounter = 0; iCounter < (nVertices - 1); ++iCounter)
	{
		// Get Min Weight Vertex
		auto min_distance_vertex = getMinVertex(visited, distance);
		visited[min_distance_vertex] = true;

		// Explore all unvisited neighbours
		for (int iCounter = 0; iCounter < nVertices; ++iCounter)
		{
			if (min_distance_vertex != iCounter && pInput[min_distance_vertex][iCounter] != 0 && !visited[iCounter])
			{
				if (distance[iCounter] > (distance[min_distance_vertex] + pInput[min_distance_vertex][iCounter]))
				{
					distance[iCounter] = distance[min_distance_vertex] + pInput[min_distance_vertex][iCounter];
				}
			}
		}
	}

	for (int iCounter = 0; iCounter < nVertices; ++iCounter)
		cout << iCounter << " " << distance[iCounter] << endl;
}

int main()
{
	int nVertices = 0;
	int nEdges = 0;
	cin >> nVertices >> nEdges;
	graph_type pGraph(nVertices, vector<int>(nVertices, 0));
	for (int iCounter = 0; iCounter < nEdges; ++iCounter)
	{
		int u, v, d;
		cin >> u >> v >> d;
		pGraph[u][v] = d;
		pGraph[v][u] = d;
	}

	cout << endl;
	dijkstras(pGraph, nVertices, nEdges);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
