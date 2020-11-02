// SumOfSquares.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

enum class update_type
{
	no_change,
	increase_value,
	replace_value
};

struct node
{
	ll squares;
	ll sum;

	node&& operator + (node oInput)
	{
		return move(node{ squares + oInput.squares, sum + oInput.sum });
	}
};

struct lazy_node
{
	update_type eType;
	ll value;
	lazy_node()
	{
		eType = update_type::no_change;
		value = 0;
	}
};

void BuildTree(vector<ll>& pInput
	, vector<node>& pTree
	, int start_Idx
	, int end_Idx
	, int node_Idx)
{
	if (start_Idx == end_Idx)
	{
		pTree[node_Idx].squares = pInput[start_Idx] * pInput[start_Idx];
		pTree[node_Idx].sum = pInput[start_Idx];
		return;
	}

	auto lft_Idx = 2 * node_Idx;
	auto rht_Idx = (2 * node_Idx) + 1;
	int mid = ((start_Idx + end_Idx) >> 1);
	BuildTree(pInput, pTree, start_Idx, mid, lft_Idx);
	BuildTree(pInput, pTree, mid + 1, end_Idx, rht_Idx);
	pTree[node_Idx] = pTree[lft_Idx] + pTree[rht_Idx];
	return;
}


void UpdateTreeNode(vector<node>& pTree
	, vector<lazy_node>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx)
{
	if (pLazy[node_Idx].eType != update_type::no_change)
	{
		auto range_length = (end_Idx - start_Idx) + 1;
		if (pLazy[node_Idx].eType == update_type::increase_value)
		{   
			// appending b^2 + 2ab for entire range
			pTree[node_Idx].squares += (pLazy[node_Idx].value * pLazy[node_Idx].value * (range_length)) + (2 * pLazy[node_Idx].value * pTree[node_Idx].sum);
			pTree[node_Idx].sum += pLazy[node_Idx].value * (range_length);
		}
		else
		{
			pTree[node_Idx].squares = pLazy[node_Idx].value * pLazy[node_Idx].value * range_length;
			pTree[node_Idx].sum = pLazy[node_Idx].value * (range_length);
		}

		if (start_Idx != end_Idx)
		{
			auto lft_Idx = 2 * node_Idx;
			auto rht_Idx = (2 * node_Idx) + 1;

			if (pLazy[node_Idx].eType == update_type::increase_value)
			{
				if (pLazy[lft_Idx].eType == update_type::no_change)
					pLazy[lft_Idx].eType = pLazy[node_Idx].eType;

				if (pLazy[rht_Idx].eType == update_type::no_change)
					pLazy[rht_Idx].eType = pLazy[node_Idx].eType;

				pLazy[lft_Idx].value += pLazy[node_Idx].value;
				pLazy[rht_Idx].value += pLazy[node_Idx].value;
			}
			else
			{
				pLazy[lft_Idx].eType = pLazy[node_Idx].eType;
				pLazy[lft_Idx].value = pLazy[node_Idx].value;
				pLazy[rht_Idx].eType = pLazy[node_Idx].eType;
				pLazy[rht_Idx].value = pLazy[node_Idx].value;
			}
		}

		pLazy[node_Idx].eType = update_type::no_change;
		pLazy[node_Idx].value = 0;
	}
}


void UpdateTree(vector<node>& pTree
	, vector<lazy_node>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, update_type eType
	, int range_left
	, int range_right
	, ll val)
{
	if (start_Idx > end_Idx)
		return;

	if (pLazy[node_Idx].eType != update_type::no_change)
		UpdateTreeNode(pTree, pLazy, start_Idx, end_Idx, node_Idx);


	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return;


	auto lft_Idx = 2 * node_Idx;
	auto rht_Idx = (2 * node_Idx) + 1;

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
	{
		auto range_length = (end_Idx - start_Idx) + 1;
		if (eType == update_type::increase_value)
		{ 
			pTree[node_Idx].squares += (val * val * (range_length)) + (2 * val * pTree[node_Idx].sum);
			pTree[node_Idx].sum += val * (range_length); 

			if (start_Idx != end_Idx)
			{ 
				if(pLazy[lft_Idx].eType == update_type::no_change)
					pLazy[lft_Idx].eType = eType;
				 
				if (pLazy[rht_Idx].eType == update_type::no_change)
					pLazy[rht_Idx].eType = eType;

				pLazy[lft_Idx].value += val;
				pLazy[rht_Idx].value += val;
			}
		}
		else if (eType == update_type::replace_value)
		{
			pTree[node_Idx].squares = val * val * range_length;
			pTree[node_Idx].sum = val * (range_length); 

			if (start_Idx != end_Idx)
			{
				pLazy[lft_Idx].eType = eType;
				pLazy[lft_Idx].value = val;
				pLazy[rht_Idx].eType = eType;
				pLazy[rht_Idx].value = val;
			}
		}
		return;
	}

	// Partial Overlap
	int mid = ((start_Idx + end_Idx) >> 1);
	UpdateTree(pTree, pLazy, start_Idx, mid, lft_Idx, eType, range_left, range_right, val);
	UpdateTree(pTree, pLazy, mid + 1, end_Idx, rht_Idx, eType, range_left, range_right, val);
	pTree[node_Idx] = pTree[lft_Idx] + pTree[rht_Idx];
	return;
}


node QueryTree(vector<node>& pTree
	, vector<lazy_node>& pLazy
	, int start_Idx
	, int end_Idx
	, int node_Idx
	, int range_left
	, int range_right)
{

	if (start_Idx > end_Idx)
		return node{ 0, 0 };

	if (pLazy[node_Idx].eType != update_type::no_change)
		UpdateTreeNode(pTree, pLazy, start_Idx, end_Idx, node_Idx);

	// No Overlap
	if (start_Idx > range_right || end_Idx < range_left)
		return node{ 0, 0 };

	// Complete Overlap
	if (start_Idx >= range_left && end_Idx <= range_right)
		return pTree[node_Idx];

	// Partial Overlap
	auto lft_Idx = 2 * node_Idx;
	auto rht_Idx = (2 * node_Idx) + 1;

	int mid = ((start_Idx + end_Idx) >> 1);
	auto left_val = QueryTree(pTree, pLazy, start_Idx, mid, lft_Idx, range_left, range_right);
	auto right_val = QueryTree(pTree, pLazy, mid + 1, end_Idx, rht_Idx, range_left, range_right);
	pTree[node_Idx] = pTree[lft_Idx] + pTree[rht_Idx]; 
	return left_val + right_val;
}

int main()
{
#ifdef TEST
	vector<ll> pInput{ 0, 1, 2, 3, 4 };
	size_t st_size = pInput.size() * 4u;
	vector<node> pTree(st_size);
	vector<lazy_node> pLazyTree(st_size);

	BuildTree(pInput, pTree, 0, pInput.size() - 1, 1);
	cout << "Result[0, 4]: " << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 0, 4).squares << endl;
	UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, update_type::replace_value, 2, 4, 2);
	UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, update_type::increase_value, 0, 4, 3);
	cout << "Result[1, 3]: " << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 1, 3).squares << endl;
	cout << "Result[2, 4]: " << QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, 2, 4).squares << endl;
#endif  
	int nTestCase = 0;
	cin >> nTestCase;

	int testCounter = 1;
	while (nTestCase--)
	{
		int nSize = 0;
		int nQueries = 0;
		cin >> nSize >> nQueries;

		vector<ll> pInput(nSize);
		for (int iCounter = 0; iCounter < nSize; ++iCounter)
			cin >> pInput[iCounter];
		
		size_t st_size = pInput.size() * 4u;
		vector<node> pTree(st_size);
		vector<lazy_node> pLazyTree(st_size);
		BuildTree(pInput, pTree, 0, pInput.size() - 1, 1);

		bool IsCasePrinted = false;
		
		while (nQueries--)
		{
			int query;
			int f_input;
			int s_input;
			ll val = 0;
			cin >> query >> f_input >> s_input;
			if (0 == query || 1 == query)
			{
				cin >> val; 
				if (0 == query)
					UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, update_type::replace_value, f_input - 1, s_input - 1, val);
				else if (1 == query)
					UpdateTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, update_type::increase_value, f_input - 1, s_input - 1, val);
			}
			else
			{
				if (!IsCasePrinted) {
					cout << "Case " << testCounter << ":" << endl;
					IsCasePrinted = true;
				}

				auto result = QueryTree(pTree, pLazyTree, 0, pInput.size() - 1, 1, f_input - 1, s_input - 1);
				std::cout << result.squares << endl;
			}
		}

		++testCounter;
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
