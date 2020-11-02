// LazyPropagation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void BuildTree(vector<int>& pInput, vector<int>& pTree, int start_Idx, int end_Idx, int node_Idx)
{
	if (start_Idx == end_Idx)
	{
		pTree[node_Idx] = pInput[start_Idx];
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	BuildTree(pInput, pTree, start_Idx, mid, 2 * node_Idx);
	BuildTree(pInput, pTree, mid + 1, end_Idx, (2 * node_Idx) + 1);
	pTree[node_Idx] = min(pTree[2 * node_Idx], pTree[(2 * node_Idx) + 1]);
	return;
}

void UpdateTree(vector<int>& pTree
	, vector<int>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, int range_left
	, int range_right
	, int val)
{
	if (start_Idx > end_Idx)
		return;

	// Update Tree Base on pending computation of lazy tree
	if (pLazy[node_Idx] != 0)
	{
		pTree[node_Idx] += pLazy[node_Idx];
		if (start_Idx != end_Idx) {
			pLazy[2 * node_Idx] += pLazy[node_Idx];
			pLazy[(2 * node_Idx) + 1] += pLazy[node_Idx];
		}
		pLazy[node_Idx] = 0;
	}

	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return;

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
	{
		pTree[node_Idx] += val;
		if (start_Idx != end_Idx)
		{
			pLazy[2 * node_Idx] += val;
			pLazy[(2 * node_Idx) + 1] += val;
		}

		return;
	}

	// Partial Overlap
	int mid = ((start_Idx + end_Idx) >> 1);
	UpdateTree(pTree, pLazy, start_Idx, mid, 2 * node_Idx, range_left, range_right, val);
	UpdateTree(pTree, pLazy, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right, val);
	pTree[node_Idx] = min(pTree[2 * node_Idx], pTree[(2 * node_Idx) + 1]);
	return;
}


int QueryTree(vector<int>& pTree
	, vector<int>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, int range_left
	, int range_right)
{
	if (start_Idx > end_Idx)
		return INT_MAX;

	// Update Tree Base on pending computation of lazy tree
	if (pLazy[node_Idx] != 0)
	{
		pTree[node_Idx] += pLazy[node_Idx];
		if (start_Idx != end_Idx) {
			pLazy[2 * node_Idx] += pLazy[node_Idx];
			pLazy[(2 * node_Idx) + 1] += pLazy[node_Idx];
		}
		pLazy[node_Idx] = 0;
	}

	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return INT_MAX;

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
		return pTree[node_Idx];

	// Partial Overlap
	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_val = QueryTree(pTree, pLazy, start_Idx, mid, 2 * node_Idx, range_left, range_right);
	auto right_val = QueryTree(pTree, pLazy, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right);
	pTree[node_Idx] = min(pTree[2 * node_Idx], pTree[(2 * node_Idx) + 1]);
	return min(left_val, right_val);
}

int main()
{
    vector<int> pInput{ 1, 3, -2, 4 };
    size_t st_size = pInput.size() * 4u;
    vector<int> pTree(st_size, 0);
	vector<int> pLazyTree(st_size, 0);
	BuildTree(pInput, pTree, 0, pInput.size() - 1, 1);
	UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 0, 3, 3);
	UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 0, 1, 2);

	/*cout << "Segment Tree: " << endl;
	for (int iCounter = 1; iCounter < st_size; ++iCounter)
		cout << pTree[iCounter] << endl;

	cout << "Lazy Tree: " << endl;
	for (int iCounter = 1; iCounter < st_size; ++iCounter)
		cout << pLazyTree[iCounter] << endl;*/

	cout << "Min [0, 3]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 0, 3) << endl;
	cout << "Min [1, 3]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 3) << endl;
	cout << "Min [0, 2]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 3) << endl;

	cout << "Update Tree: " << endl;
	UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 2, -4);
	cout << "Min [0, 3]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 0, 3) << endl;
	cout << "Min [1, 3]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 3) << endl;
	cout << "Min [0, 2]" << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 3) << endl;

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
