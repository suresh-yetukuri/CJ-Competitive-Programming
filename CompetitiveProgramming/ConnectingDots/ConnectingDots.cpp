// ConnectingDots.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;
using graph_type = vector<vector<char>>;


bool IsCycleExist(graph_type& pGraph
	, int rCounter
	, int cCounter
	, int n
	, int m
	, vector<vector<int>>& pVisited
	, int parentIdx
	, char dot_color)
{
	if (rCounter < 0 || rCounter >= n || cCounter < 0 || cCounter >= m)
		return false;

	int lastRowIdx = parentIdx / m;
	int lastColIdx = parentIdx % m;
	int curr_Idx = (rCounter * m) + cCounter;
	
	if (dot_color != pGraph[rCounter][cCounter])
		return false;

	if (pVisited[rCounter][cCounter] != -1)
	{
		if (curr_Idx == pVisited[lastRowIdx][lastColIdx])
			return false;
		else
			return true;
	}


	pVisited[rCounter][cCounter] = parentIdx;
	auto option1 = IsCycleExist(pGraph, rCounter, cCounter + 1, n, m, pVisited, curr_Idx, dot_color);
	if (option1)
		return true;

	auto option2 = IsCycleExist(pGraph, rCounter + 1, cCounter, n, m, pVisited, curr_Idx, dot_color);
	if (option2)
		return true;

	auto option3 = IsCycleExist(pGraph, rCounter, cCounter - 1, n, m, pVisited, curr_Idx, dot_color);
	if (option3)
		return true;

	auto option4 = IsCycleExist(pGraph, rCounter - 1, cCounter, n, m, pVisited, curr_Idx, dot_color);
	if (option4)
		return true;

	return false;
}


namespace IshaanApproachNaive
{
	bool searchcycle(char board[][MAXN], int n, int m, int i, int j, bool** visited, int length, int si, int sj) {
		if (length >= 4 && si == i && sj == j) {
			return true;
		}
		if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || board[i][j] != board[si][sj]) {
			return false;
		}

		visited[i][j] = true;
		bool a = searchcycle(board, n, m, i, j - 1, visited, length + 1, si, sj);

		bool b = searchcycle(board, n, m, i - 1, j, visited, length + 1, si, sj);

		bool c = searchcycle(board, n, m, i, j + 1, visited, length + 1, si, sj);

		bool d = searchcycle(board, n, m, i + 1, j, visited, length + 1, si, sj);

		bool p = a || b || c || d;
		visited[i][j] = false;
		return p;


	}

	int solve(char board[][MAXN], int n, int m)
	{
		// Write your code here.
		bool** visited = new bool* [n];
		for (int i = 0; i < n; i++) {
			visited[i] = new bool[m];
			for (int j = 0; j < m; j++) {
				visited[i][j] = false;
			}
		}


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (searchcycle(board, n, m, i, j, visited, 0, i, j)) {
					return 1;
				}
			}
		}
		return 0;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	graph_type pGraph(n, vector<char>(m));
	for (int iCounter = 0; iCounter < n; ++iCounter)
		for (int jCounter = 0; jCounter < m; ++jCounter)
			cin >> pGraph[iCounter][jCounter];
	
	auto total_dots = n * m;
	bool result = false;
	vector<vector<int>> pVisited(n, vector<int>(m, -1));
	for (int iCounter = 0; iCounter < total_dots; ++iCounter)
	{
		int rowIdx = iCounter / m;
		int colIdx = iCounter % m;
		if (pVisited[rowIdx][colIdx] != -1)
			continue;

		auto curr_color_dot = pGraph[rowIdx][colIdx];
		result = IsCycleExist(pGraph, rowIdx, colIdx, n, m, pVisited, -2, curr_color_dot);
		
		if (result)
			break;
	}

	cout << boolalpha;
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
