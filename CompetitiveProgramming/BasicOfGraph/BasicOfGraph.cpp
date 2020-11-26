// BasicOfGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <optional>
using namespace std;
using graph_type = vector<vector<bool>>;

void DFS(graph_type& pGraph
	, vector<bool>& pVisited
	, int nVertices
	, int curr_vertex)
{
	cout << curr_vertex << endl;
	pVisited[curr_vertex] = true;

	for (int adjVertex = 0; adjVertex < nVertices; ++adjVertex)
	{
		if (pGraph[curr_vertex][adjVertex]
			&& curr_vertex != adjVertex
			&& !pVisited[adjVertex])
			DFS(pGraph, pVisited, nVertices, adjVertex);
	}
}


void BFS(graph_type& pGraph
	, vector<bool>& pVisited
	, int nVertices
	, int start_vertex)
{
	queue<int> pPendingVertices;
	pVisited[start_vertex] = true;
	pPendingVertices.push(start_vertex);
	while (!pPendingVertices.empty())
	{
		auto curr_vertex = pPendingVertices.front();
		pPendingVertices.pop();
		cout << curr_vertex << endl;
		for (auto adjVertex = 0; adjVertex < nVertices; ++adjVertex)
		{
			if (pGraph[curr_vertex][adjVertex]
				&& curr_vertex != adjVertex
				&& !pVisited[adjVertex])
			{
				pVisited[adjVertex] = true;
				pPendingVertices.push(adjVertex);
			}
		}
	}
}

void print_dfs_connected(graph_type& pGraph, int nVertices)
{
	cout << "Printing DFS for Connected Graph" << endl;
	vector<bool> pVisited(nVertices, false);
	DFS(pGraph, pVisited, nVertices, 0);
	cout << endl;
}

void print_bfs_connected(graph_type& pGraph, int nVertices)
{
	cout << "Printing BFS for Connected Graph" << endl;
	vector<bool> pVisited(nVertices, false);
	BFS(pGraph, pVisited, nVertices, 0);
	cout << endl;
}

void print_dfs_disconnected(graph_type& pGraph, int nVertices)
{
	cout << "Printing DFS for Disconnected Graph" << endl;
	vector<bool> pVisited(nVertices, false);
	for (auto curr_vertex = 0; curr_vertex < nVertices; ++curr_vertex)
	{
		if (!pVisited[curr_vertex])
			DFS(pGraph, pVisited, nVertices, curr_vertex);
	}
	cout << endl;
}

void print_bfs_disconnected(graph_type& pGraph, int nVertices)
{
	cout << "Printing BFS for Disconnected Graph" << endl;
	vector<bool> pVisited(nVertices, false);
	for (auto curr_vertex = 0; curr_vertex < nVertices; ++curr_vertex)
	{
		if (!pVisited[curr_vertex])
			BFS(pGraph, pVisited, nVertices, curr_vertex);
	}

	cout << endl;
}

bool has_path_dfs(graph_type& pGraph
	, vector<bool>& pVisited
	, int nVertices
	, int curr_vertex
	, int end_vertex)
{
	if (curr_vertex == end_vertex)
		return true;

	pVisited[curr_vertex] = true;
	for (int adjVertex = 0; adjVertex < nVertices; ++adjVertex)
	{
		if (pGraph[curr_vertex][adjVertex]
			&& curr_vertex != adjVertex
			&& !pVisited[adjVertex])
		{
			if (has_path_dfs(pGraph, pVisited, nVertices, adjVertex, end_vertex))
				return true;
		}
	}

	return false;
}

bool has_path_bfs(graph_type& pGraph
	, vector<bool>& pVisited
	, int nVertices
	, int start_vertex
	, int end_vertex)
{ 
	if (start_vertex == end_vertex)
		return true;

	queue<int> pPendingVertices;
	pVisited[start_vertex] = true;
	pPendingVertices.push(start_vertex);
	while (!pPendingVertices.empty())
	{
		auto curr_vertex = pPendingVertices.front();
		pPendingVertices.pop();
		for (auto adjVertex = 0; adjVertex < nVertices; ++adjVertex)
		{
			if (pGraph[curr_vertex][adjVertex]
				&& curr_vertex != adjVertex
				&& !pVisited[adjVertex])
			{
				if (adjVertex == end_vertex)
					return true;

				pVisited[adjVertex] = true;
				pPendingVertices.push(adjVertex);
			}
		}
	}


	return true;
}

bool has_path_dfs(graph_type& pGraph
	, int nVertices
	, int start_vertex
	, int end_vertex)
{
	vector<bool> pVisited(nVertices, false);
	return has_path_dfs(pGraph, pVisited, nVertices, start_vertex, end_vertex);
}


bool has_path_bfs(graph_type& pGraph
	, int nVertices
	, int start_vertex
	, int end_vertex)
{
	vector<bool> pVisited(nVertices, false);
	return has_path_bfs(pGraph, pVisited, nVertices, start_vertex, end_vertex);
}


vector<int> get_path_bfs(graph_type& pGraph
	, int nVertices
	, int start_vertex
	, int end_vertex)
{
	vector<bool> pVisited(nVertices, false);
	queue<int> pPendingVertices;
	unordered_map<int, int> pHashMap;
	vector<int> pPath;

	pVisited[start_vertex] = true;
	pPendingVertices.push(start_vertex);
	pHashMap[start_vertex] = -1;

	while (!pPendingVertices.empty())
	{
		auto curr_vertex = pPendingVertices.front();
		pPendingVertices.pop();

		for (int adj = 0; adj < nVertices; ++adj)
		{
			if (pGraph[curr_vertex][adj]
				&& curr_vertex != adj
				&& !pVisited[adj])
			{
				if (adj == end_vertex)
				{
					// We got the path
					pPath.push_back(end_vertex);
					while (curr_vertex != start_vertex)
					{
						pPath.push_back(curr_vertex);
						curr_vertex = pHashMap[curr_vertex];
					}

					pPath.push_back(start_vertex);
					return pPath;
				}
				 
				pVisited[adj] = true;
				pPendingVertices.push(adj);
				pHashMap[adj] = curr_vertex;
			}
		}
	}

	return pPath;
}


optional<vector<int>> get_path_dfs(graph_type& pGraph
	, vector<bool>& pVisited
	, int nVertices
	, int curr_vertex
	, int end_vertex)
{
	if (curr_vertex == end_vertex) {
		vector<int> pPath;
		pPath.push_back(end_vertex);
		return pPath;
	}
	else
	{
		pVisited[curr_vertex] = true;
		for (int adjVertex = 0; adjVertex < nVertices; ++adjVertex)
		{
			if (pGraph[curr_vertex][adjVertex]
				&& curr_vertex != adjVertex
				&& !pVisited[adjVertex])
			{
				auto prevPath = get_path_dfs(pGraph, pVisited, nVertices, adjVertex, end_vertex);
				if (prevPath)
				{
					(*prevPath).push_back(curr_vertex);
					return prevPath;
				}
			}
		}
	}

	return nullopt;
}

vector<int> get_path_dfs(graph_type& pGraph
	, int nVertices
	, int start_vertex
	, int end_vertex)
{

	vector<bool> pVisited(nVertices, false);
	auto pPath = get_path_dfs(pGraph, pVisited, nVertices, start_vertex, end_vertex);
	return *pPath;
}



bool IsConnected_bfs(graph_type& pGraph, int nVertices)
{
	vector<bool> pVisited(nVertices, false);
	queue<int> pPendingVertices;
	pVisited[0] = true;
	pPendingVertices.push(0);
	while (!pPendingVertices.empty())
	{
		auto curr_vertex = pPendingVertices.front();
		pPendingVertices.pop();
		cout << curr_vertex << endl;
		for (auto adjVertex = 0; adjVertex < nVertices; ++adjVertex)
		{
			if (pGraph[curr_vertex][adjVertex]
				&& curr_vertex != adjVertex
				&& !pVisited[adjVertex])
			{
				pVisited[adjVertex] = true;
				pPendingVertices.push(adjVertex);
			}
		}
	}
	 
	for (int vertex = 0; vertex < nVertices; ++vertex) 
		if (!pVisited[vertex])
			return false;

	return true;
}


void dfs_parse(graph_type& pGraph
	, vector<bool>& pVisited
	, vector<int>& pComponent
	, int nVertices
	, int curr_vertex)
{
	pComponent.push_back(curr_vertex);
	pVisited[curr_vertex] = true;
	for (int adjVertex = 0; adjVertex < nVertices; ++adjVertex)
	{
		if (pGraph[curr_vertex][adjVertex]
			&& curr_vertex != adjVertex
			&& !pVisited[adjVertex])
			dfs_parse(pGraph, pVisited, pComponent, nVertices, adjVertex);
	}
}

vector<vector<int>> getConnectedComponents(graph_type& pGraph, int nVertices)
{
	vector<bool> pVisited(nVertices, false);
	vector<vector<int>> pConnectedComponents;
	for (auto curr_vertex = 0; curr_vertex < nVertices; ++curr_vertex)
	{
		vector<int> pComponents;
		if (!pVisited[curr_vertex]) {
			dfs_parse(pGraph, pVisited, pComponents, nVertices, curr_vertex);
			sort(pComponents.begin(), pComponents.end());
			pConnectedComponents.push_back(pComponents);
		}
	}

	return move(pConnectedComponents);
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

	int src = 0;
	int dest = 0;
	cin >> src >> dest;
	 
	auto result = get_path_dfs(pGraph, nVertices, src, dest);
	for (auto& v : result)
		cout << v << " ";
	//auto result = getConnectedComponents(pGraph, nVertices);

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
