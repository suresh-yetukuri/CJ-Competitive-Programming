// MaximumSubarraySum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const ll inf = 16000; // should be greater than 15007(abs(A[i]) <= 15007)

struct node
{
	ll max_sum;
	ll total_sum;
	ll best_prefix_sum;
	ll best_suffix_sum;
};


void BuildTree(vector<int>& pInput, vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx)
{
	if (start_Idx == end_Idx)
	{
		pTree[node_Idx].max_sum = pInput[start_Idx];
		pTree[node_Idx].total_sum = pInput[start_Idx];
		pTree[node_Idx].best_prefix_sum = pInput[start_Idx];
		pTree[node_Idx].best_suffix_sum = pInput[start_Idx];
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_Idx = 2 * node_Idx;
	auto right_Idx = (2 * node_Idx) + 1;
	BuildTree(pInput, pTree, start_Idx, mid, left_Idx);
	BuildTree(pInput, pTree, mid + 1, end_Idx, right_Idx);

	pTree[node_Idx].max_sum = max({ pTree[left_Idx].max_sum
								  , pTree[right_Idx].max_sum
		//, pTree[left_Idx].total_sum + pTree[right_Idx].best_prefix_sum
		//, pTree[right_Idx].total_sum + pTree[left_Idx].best_suffix_sum
		, pTree[left_Idx].best_suffix_sum + pTree[right_Idx].best_prefix_sum });

	pTree[node_Idx].total_sum = pTree[left_Idx].total_sum + pTree[right_Idx].total_sum;
	pTree[node_Idx].best_prefix_sum = max(pTree[left_Idx].best_prefix_sum, pTree[left_Idx].total_sum + pTree[right_Idx].best_prefix_sum);
	pTree[node_Idx].best_suffix_sum = max(pTree[right_Idx].best_suffix_sum, pTree[right_Idx].total_sum + pTree[left_Idx].best_suffix_sum);

	return;
}

void UpdateTree(vector<int>& pInput, vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx, int change_Idx, int new_val)
{
	if (start_Idx == end_Idx)
	{
		pInput[start_Idx] = new_val;
		pTree[node_Idx].max_sum = pInput[start_Idx];
		pTree[node_Idx].total_sum = pInput[start_Idx];
		pTree[node_Idx].best_prefix_sum = pInput[start_Idx];
		pTree[node_Idx].best_suffix_sum = pInput[start_Idx];
		return;
	}

	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_Idx = 2 * node_Idx;
	auto right_Idx = (2 * node_Idx) + 1;

	if (change_Idx <= mid)
		UpdateTree(pInput, pTree, start_Idx, mid, 2 * node_Idx, change_Idx, new_val);
	else
		UpdateTree(pInput, pTree, mid + 1, end_Idx, (2 * node_Idx) + 1, change_Idx, new_val);

	pTree[node_Idx].max_sum = max({ pTree[left_Idx].max_sum
								  , pTree[right_Idx].max_sum
		//, pTree[left_Idx].total_sum + pTree[right_Idx].best_prefix_sum
		//, pTree[right_Idx].total_sum + pTree[left_Idx].best_suffix_sum
		, pTree[left_Idx].best_suffix_sum + pTree[right_Idx].best_prefix_sum });

	pTree[node_Idx].total_sum = pTree[left_Idx].total_sum + pTree[right_Idx].total_sum;
	pTree[node_Idx].best_prefix_sum = max(pTree[left_Idx].best_prefix_sum, pTree[left_Idx].total_sum + pTree[right_Idx].best_prefix_sum);
	pTree[node_Idx].best_suffix_sum = max(pTree[right_Idx].best_suffix_sum, pTree[right_Idx].total_sum + pTree[left_Idx].best_suffix_sum);
	return;
}

node QueryTree(vector<node>& pTree, int start_Idx, int end_Idx, int node_Idx, int range_left, int range_right)
{
	// 3 Possibilities
	// 1. Complete out of range
	if (start_Idx > range_right || end_Idx < range_left)
		return node{ -inf, -inf, -inf, -inf };

	// 2. Completely in range
	if (start_Idx >= range_left && end_Idx <= range_right)
		return pTree[node_Idx];

	// 3. Partially in range
	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_value = QueryTree(pTree, start_Idx, mid, 2 * node_Idx, range_left, range_right);
	auto right_value = QueryTree(pTree, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right);

	auto max_sum = max({ left_value.max_sum
					   , right_value.max_sum
		//, left_value.total_sum + right_value.best_prefix_sum
		//, right_value.total_sum + left_value.best_suffix_sum
		, left_value.best_suffix_sum + right_value.best_prefix_sum });

	auto total_sum = left_value.total_sum + right_value.total_sum;
	auto best_prefix_sum = max(left_value.best_prefix_sum, left_value.total_sum + right_value.best_prefix_sum);
	auto best_suffix_sum = max(right_value.best_suffix_sum, right_value.total_sum + left_value.best_suffix_sum);
	return node{ max_sum, total_sum, best_prefix_sum, best_suffix_sum };
}


int main()
{
	int nSize = 0;
	int nQueries = 0;
	cin >> nSize;
	vector<int> pInput(nSize);
	for (int iCounter = 0; iCounter < nSize; ++iCounter)
		cin >> pInput[iCounter];

	size_t tree_size = 4 * nSize;
	vector<node> pTree(tree_size);
	BuildTree(pInput, pTree, 0, nSize - 1, 1);
	cin >> nQueries;
	while (nQueries--)
	{
		int first_input = 0;
		int second_input = 0;
		cin >> first_input >> second_input;
		auto result = QueryTree(pTree, 0, nSize - 1, 1, first_input - 1, second_input - 1);
		cout << result.max_sum << endl;
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
