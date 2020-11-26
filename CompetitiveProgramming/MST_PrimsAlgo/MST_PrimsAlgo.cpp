// MST_PrimsAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
using graph_type = vector<vector<int>>;

int getMinVertex(vector<bool>& visited, vector<int>& weight)
{
	int min_weight_vertex = -1;
	for (int iCounter = 0; iCounter < visited.size(); ++iCounter)
	{
		if (!visited[iCounter] && (min_weight_vertex == -1 || weight[iCounter] < weight[min_weight_vertex]))
			min_weight_vertex = iCounter;
	}

	return min_weight_vertex;
}

void mst_prims(graph_type& pInput, int nVertices, int nEdges)
{
	vector<bool> visited(nVertices, false);
	vector<int> parent(nVertices);
	vector<int> weight(nVertices, INT_MAX);
	weight[0] = 0;
	parent[0] = -1;
	
	for (int iCounter = 0; iCounter < (nVertices - 1); ++iCounter)
	{
		// Get Min Weight Vertex
		auto min_weight_vertex = getMinVertex(visited, weight);
		visited[min_weight_vertex] = true;

		// Explore all unvisited neighbours
		for (int iCounter = 0; iCounter < nVertices; ++iCounter)
		{
			if (min_weight_vertex != iCounter && pInput[min_weight_vertex][iCounter] != 0 && !visited[iCounter])
			{
				if (weight[iCounter] > pInput[min_weight_vertex][iCounter])
				{
					weight[iCounter] = pInput[min_weight_vertex][iCounter];
					parent[iCounter] = min_weight_vertex;
				}
			}
		} 
	}

	for (int iCounter = 1; iCounter < nVertices; ++iCounter)
	{
		if (iCounter > parent[iCounter])
			cout << parent[iCounter] << " " << iCounter << " " << weight[iCounter];
		else
			cout << iCounter << " " << parent[iCounter] << " " << weight[iCounter];

		cout << endl;
	}
}

// Impelement using priority_queue & adjaceny list to optimize

int main()
{
	int nVertices = 0;
	int nEdges = 0;
	cin >> nVertices >> nEdges;
	graph_type pGraph(nVertices, vector<int>(nVertices, 0));
	for (int iCounter = 0; iCounter < nEdges; ++iCounter)
	{
		int u, v, w;
		cin >> u >> v >> w;
		pGraph[u][v] = w;
		pGraph[v][u] = w;
	}

	cout << endl;
	mst_prims(pGraph, nVertices, nEdges);
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
