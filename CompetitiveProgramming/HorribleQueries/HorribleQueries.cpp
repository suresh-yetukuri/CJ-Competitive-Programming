// HorribleQueries.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

inline int lft_Idx(int node_Idx)
{
	return 2 * node_Idx;
}

inline int rht_Idx(int node_Idx)
{
	return (2 * node_Idx) + 1;
}

void BuildTree(vector<ll>& pInput
	, vector<ll>& pTree
	, int start_Idx
	, int end_Idx
	, int node_Idx)
{
	if (start_Idx == end_Idx)
	{
		pTree[node_Idx] = pInput[start_Idx];
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	BuildTree(pInput, pTree, start_Idx, mid, 2 * node_Idx);
	BuildTree(pInput, pTree, mid + 1, end_Idx, (2 * node_Idx) + 1);
	pTree[node_Idx] = pTree[lft_Idx(node_Idx)] + pTree[rht_Idx(node_Idx)];
	return;
}


void UpdateTree(vector<ll>& pTree
	, vector<ll>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, int range_left
	, int range_right
	, ll val)
{
	if (start_Idx > end_Idx)
		return;

	// Update Tree Base on pending computation of lazy tree
	if (pLazy[node_Idx] != 0)
	{
		auto range_length = (end_Idx - start_Idx) + 1;
		pTree[node_Idx] += pLazy[node_Idx] * range_length;
		if (start_Idx != end_Idx) {
			pLazy[lft_Idx(node_Idx)] += pLazy[node_Idx];
			pLazy[rht_Idx(node_Idx)] += pLazy[node_Idx];
		}
		pLazy[node_Idx] = 0;
	}

	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return;

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
	{
		auto range_length = (end_Idx - start_Idx) + 1;
		pTree[node_Idx] += (val * range_length);
		if (start_Idx != end_Idx)
		{
			pLazy[lft_Idx(node_Idx)] += val;
			pLazy[rht_Idx(node_Idx)] += val;
		}
		return;
	}

	// Partial Overlap
	int mid = ((start_Idx + end_Idx) >> 1);
	UpdateTree(pTree, pLazy, start_Idx, mid, 2 * node_Idx, range_left, range_right, val);
	UpdateTree(pTree, pLazy, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right, val);
	pTree[node_Idx] = pTree[lft_Idx(node_Idx)] + pTree[rht_Idx(node_Idx)];
	return;
}


ll QueryTree(vector<ll>& pTree
	, vector<ll>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, int range_left
	, int range_right)
{
	if (start_Idx > end_Idx)
		return 0;

	// Update Tree Base on pending computation of lazy tree
	if (pLazy[node_Idx] != 0)
	{
		auto range_length = (end_Idx - start_Idx) + 1;
		pTree[node_Idx] += pLazy[node_Idx] * range_length;
		if (start_Idx != end_Idx) {
			pLazy[lft_Idx(node_Idx)] += pLazy[node_Idx];
			pLazy[rht_Idx(node_Idx)] += pLazy[node_Idx];
		}
		pLazy[node_Idx] = 0;
	}

	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return 0;

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
		return pTree[node_Idx];

	// Partial Overlap
	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_val = QueryTree(pTree, pLazy, start_Idx, mid, 2 * node_Idx, range_left, range_right);
	auto right_val = QueryTree(pTree, pLazy, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right);
	pTree[node_Idx] = pTree[lft_Idx(node_Idx)] + pTree[rht_Idx(node_Idx)];
	return left_val + right_val;
}

int main()
{
	int nTestCase = 0;
	cin >> nTestCase;
	while (nTestCase--)
	{
		int nSize = 0;
		int nQueries = 0;
		cin >> nSize >> nQueries;
		vector<ll> pInput(nSize, 0);

		ll st_size = nSize * 4;
		vector<ll> pTree(st_size, 0);
		vector<ll> pLazy(st_size, 0);
		BuildTree(pInput, pTree, 0, nSize - 1, 1);

		while (nQueries--)
		{
			int query_type = 0;
			int range_lft = 0;
			int range_rht = 0;
			cin >> query_type >> range_lft >> range_rht;
			if (0 == query_type)
			{ 
				ll val = 0;
				cin >> val;
				UpdateTree(pTree, pLazy, 0, nSize - 1, 1, range_lft - 1, range_rht - 1, val);
			}
			else
			{
				auto result = QueryTree(pTree, pLazy, 0, nSize - 1, 1, range_lft - 1, range_rht - 1);
				cout << result << endl;
			}
		}
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
