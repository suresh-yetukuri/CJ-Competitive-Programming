// MaximumPairSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
	int f_max;
	int s_max;
};

void BuildTree(vector<int>& pInput, vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx)
{
	if (start_Idx == end_Idx)
	{
		pTree[node_Idx].f_max = pInput[start_Idx];
		pTree[node_Idx].s_max = 0;
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	BuildTree(pInput, pTree, start_Idx, mid, 2 * node_Idx);
	BuildTree(pInput, pTree, mid + 1, end_Idx, (2 * node_Idx) + 1); 

	pTree[node_Idx].f_max = max(pTree[2 * node_Idx].f_max, pTree[(2 * node_Idx) + 1].f_max);
	pTree[node_Idx].s_max = min(max(pTree[(2 * node_Idx) + 1].f_max, pTree[2 * node_Idx].s_max)
						      , max(pTree[(2 * node_Idx) + 1].s_max, pTree[2 * node_Idx].f_max));
	
	return;
}

void UpdateTree(vector<int>& pInput, vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx, int change_Idx, int new_val)
{
	if (start_Idx == end_Idx)
	{
		pInput[start_Idx] = new_val;
		pTree[node_Idx].f_max = new_val;
		pTree[node_Idx].s_max = 0;
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	if (change_Idx <= mid)
		UpdateTree(pInput, pTree, start_Idx, mid, 2 * node_Idx, change_Idx, new_val);
	else
		UpdateTree(pInput, pTree, mid + 1, end_Idx, (2 * node_Idx) + 1, change_Idx, new_val);

	pTree[node_Idx].f_max = max(pTree[2 * node_Idx].f_max, pTree[(2 * node_Idx) + 1].f_max);
	pTree[node_Idx].s_max = min(max(pTree[(2 * node_Idx) + 1].f_max, pTree[2 * node_Idx].s_max)
							  , max(pTree[(2 * node_Idx) + 1].s_max, pTree[2 * node_Idx].f_max));
	return;
}

node QueryTree(vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx, int range_left, int range_right)
{
	// 3 Possibilities
	// 1. Complete out of range
	if (start_Idx > range_right || end_Idx < range_left)
		return node{ 0,0 };

	// 2. Completely in range
	if (start_Idx >= range_left && end_Idx <= range_right)
		return pTree[node_Idx];

	// 3. Partially in range
	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_value = QueryTree(pTree, start_Idx, mid, 2 * node_Idx, range_left, range_right);
	auto right_value = QueryTree(pTree, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right);
	
	auto f_max = max(left_value.f_max, right_value.f_max);
	auto s_max = min(max(right_value.f_max, left_value.s_max)
				   , max(right_value.s_max, left_value.f_max));

	return node{ f_max, s_max };
}


int main()
{
	int nSize = 0;
	int nQueries = 0;
	cin >> nSize;
	vector<int> pInput(nSize);
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
		cin >> pInput[iCounter];

	cin >> nQueries;

	// Building Segment Tree
	size_t tree_size = 4u * nSize;
	vector<node> pTree(tree_size);
	BuildTree(pInput, pTree, 0, nSize - 1, 1);


	while (nQueries--)
	{
		char query_type;
		int first_input = 0;
		int second_input = 0;
		cin >> query_type >> first_input >> second_input;
		if ('Q' == query_type)
		{
			auto result = QueryTree(pTree, 0, nSize - 1, 1, first_input - 1, second_input - 1);
			cout << (result.f_max + result.s_max) << endl;
		}
		else
			UpdateTree(pInput, pTree, 0, nSize - 1, 1, first_input - 1, second_input);
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
