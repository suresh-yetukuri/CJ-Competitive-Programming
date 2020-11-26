// CodingNinjas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 102


int DFS(char Graph[][MAXN]
	, vector<vector<bool>>& pVisited
	, string& oTarget
	, int N
	, int M
	, int rCounter
	, int cCounter
	, int target_char_Idx)
{
	if (oTarget.length() == target_char_Idx)
		return true;

	if (rCounter < 0 || cCounter < 0 || rCounter >= N || cCounter >= M)
		return false;

	if ((Graph[rCounter][cCounter] != oTarget[target_char_Idx]) || pVisited[rCounter][cCounter]) 
		return false;

	pVisited[rCounter][cCounter] = true;
	if (DFS(Graph, pVisited, oTarget, N, M, rCounter - 1, cCounter - 1, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter - 1, cCounter, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter - 1, cCounter + 1, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter, cCounter - 1, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter, cCounter + 1, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter + 1, cCounter - 1, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter + 1, cCounter, target_char_Idx + 1))
		return 1;

	if (DFS(Graph, pVisited, oTarget, N, M, rCounter + 1, cCounter + 1, target_char_Idx + 1))
		return 1;

	pVisited[rCounter][cCounter] = false;
	return 0;
}

int solve(char Graph[][MAXN], int N, int M)
{
	string oTarget{ "CODINGNINJA" };
	int target_char_Idx = 0;
	for(int rCounter = 0; rCounter < N; ++rCounter)
		for (int cCounter = 0; cCounter < M; ++cCounter)
		{
			if (Graph[rCounter][cCounter] == oTarget[target_char_Idx])
			{
				vector<vector<bool>> pVisited(N, vector<bool>(M, false)); 
				if (DFS(Graph, pVisited, oTarget, N, M, rCounter, cCounter, target_char_Idx)) 
					return 1; 
			}
		}

	return 0;
}

int main()
{
	int N = 2;
	int M = 11;
	char Graph[2][MAXN];
	for(int iCounter = 0; iCounter < N; ++iCounter)
		for (int jCounter = 0; jCounter < M; ++jCounter) 
			cin >> Graph[iCounter][jCounter];

	auto result = solve(Graph, N, M);
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
