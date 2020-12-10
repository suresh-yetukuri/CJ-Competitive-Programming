// PermutationSwaps.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
using graph_type = vector<vector<int>>;

void DFS(graph_type& pGraph, vector<bool>& pVisited, int curr_vertex, unordered_set<int>& pComp)
{
	pVisited[curr_vertex] = true;
	pComp.insert(curr_vertex);
	for (auto& adj_vertex : pGraph[curr_vertex])
	{
		if (!pVisited[adj_vertex])
			DFS(pGraph, pVisited, adj_vertex, pComp);
	}
}

vector<unordered_set<int>> getComponents(graph_type& pGraph, size_t total_vertex)
{
	vector<bool> pVisited(total_vertex + 1u, false);
	vector<unordered_set<int>> pComponents;
	for (int iCounter = 1; iCounter <= total_vertex; ++iCounter)
	{
		if (!pVisited[iCounter])
		{
			unordered_set<int> pSet;
			DFS(pGraph, pVisited, iCounter, pSet);
			pComponents.push_back(move(pSet));
		}
	}

	return move(pComponents);
}

bool IsChangeable(vector<int>& pFormat, vector<int>& qFormat, graph_type& pGraph, size_t total_vertex)
{
	auto pComponentCol = getComponents(pGraph, total_vertex);
	for (auto& pSet : pComponentCol)
	{
		unordered_set<int> pAux;
		for (auto& Idx : pSet)
			pAux.insert(pFormat[Idx]);

		for (auto& Idx : pSet)
		{
			if (pAux.find(qFormat[Idx]) == pAux.end())
				return false;
		}
	}

	return true;
}

int main()
{
    int nTestCase = 0;
	cin >> nTestCase;
	while (nTestCase--)
	{
		size_t N = 0;
		size_t M = 0;
		cin >> N >> M;
		vector<int> pFormat(N + 1u, 0);
		vector<int> qFormat(N + 1u, 0);
		graph_type swap_col(N + 1u);

		for (int iCounter = 1; iCounter <= N; ++iCounter)
			cin >> pFormat[iCounter];

		for (int iCounter = 1; iCounter <= N; ++iCounter)
			cin >> qFormat[iCounter];

		for (int iCounter = 1; iCounter <= M; ++iCounter)
		{
			int u, v;
			cin >> u >> v;
			swap_col[u].push_back(v);
			swap_col[v].push_back(u);
		}

		if (IsChangeable(pFormat, qFormat, swap_col, N))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

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
