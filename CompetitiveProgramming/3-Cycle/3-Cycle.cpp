// 3-Cycle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using graph_type = vector<vector<bool>>;

int CountThreeCycle(graph_type& pGraph, int nVertices)
{
	int Count = 0;
	for (int iCounter = 0; iCounter < nVertices; ++iCounter)
	{
		for (int jCounter = 0; jCounter < nVertices; ++jCounter)
		{
			if (iCounter == jCounter)
				continue;

			if (pGraph[iCounter][jCounter])
			{
				for (int kCounter = 0; kCounter < nVertices; ++kCounter)
				{
					if (iCounter == kCounter || jCounter == kCounter)
						continue;

					if (pGraph[jCounter][kCounter] && pGraph[kCounter][iCounter])
						++Count;
				}
			}
		}
	}

	return (Count / 6);
}

int main()
{
	int nVertices = 0;
	int nEdges = 0;
	cin >> nVertices >> nEdges;
	graph_type pGraph(nVertices, vector<bool>(nVertices, false));
	for (int iCounter = 0; iCounter < nEdges; ++iCounter)
	{
		int u, v;
		cin >> u >> v;
		pGraph[u][v] = true;
		pGraph[v][u] = true;
	}

	auto result = CountThreeCycle(pGraph, nVertices);
	cout << result << endl;
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
