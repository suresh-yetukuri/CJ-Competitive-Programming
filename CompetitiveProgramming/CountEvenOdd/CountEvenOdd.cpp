// CountEvenOdd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

inline bool IsOdd(int input)
{
    return (input & 1);
}

inline int lft_Idx(int node_Idx)
{
    return 2 * node_Idx;
}

inline int rht_Idx(int node_Idx)
{
    return (2 * node_Idx) + 1;
}

void BuildTree(vector<int>& pInput
    , vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx)
{
    if (start_Idx == end_Idx)
    {
        if (IsOdd(pInput[start_Idx]))
            pTree[node_Idx] = 0;
        else
            pTree[node_Idx] = 1;

        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1);
    BuildTree(pInput, pTree, start_Idx, mid, lft_Idx(node_Idx));
    BuildTree(pInput, pTree, mid + 1, end_Idx, rht_Idx(node_Idx));
    pTree[node_Idx] = pTree[lft_Idx(node_Idx)] + pTree[rht_Idx(node_Idx)];
    return;
}

void UpdateTree(vector<int>& pInput
    , vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx
    , int change_Idx
    , int new_val)
{
    if (start_Idx == end_Idx)
    {
        pInput[start_Idx] = new_val;
        if (IsOdd(pInput[start_Idx]))
            pTree[node_Idx] = 0;
        else
            pTree[node_Idx] = 1;

        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1);
    if (change_Idx <= mid)
        UpdateTree(pInput, pTree, start_Idx, mid, lft_Idx(node_Idx), change_Idx, new_val);
    else
        UpdateTree(pInput, pTree, mid + 1, end_Idx, rht_Idx(node_Idx), change_Idx, new_val);

    pTree[node_Idx] = pTree[lft_Idx(node_Idx)] + pTree[rht_Idx(node_Idx)];
}

int QueryTree(vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx
    , int range_lft
    , int range_rht)
{


    // No Overlap
    if (start_Idx > range_rht || end_Idx < range_lft)
        return 0;

    // Complete Overlap
    if (start_Idx >= range_lft && end_Idx <= range_rht)
        return pTree[node_Idx];

    // Partial Overlap
    int mid = ((start_Idx + end_Idx) >> 1);
    auto lft_val = QueryTree(pTree, start_Idx, mid, lft_Idx(node_Idx), range_lft, range_rht);
    auto rht_val = QueryTree(pTree, mid + 1, end_Idx, rht_Idx(node_Idx), range_lft, range_rht);
    return lft_val + rht_val;
}


int main()
{
    int nSize = 0;
    int nQueries = 0;
    cin >> nSize;
    vector<int> pInput(nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> pInput[iCounter];

    size_t st_size = static_cast<size_t>(nSize * 4);
    vector<int> pTree(st_size, 0);
    BuildTree(pInput, pTree, 0, nSize - 1, 1);

    cin >> nQueries;
    while (nQueries--)
    {
        int query_type = 0;
        int f_input = 0;
        int s_input = 0;
        cin >> query_type >> f_input >> s_input;
        if (0 == query_type)
            UpdateTree(pInput, pTree, 0, nSize - 1, 1, f_input - 1, s_input);
        else
        {
            auto even_count = QueryTree(pTree, 0, nSize - 1, 1, f_input - 1, s_input - 1);
            if (1 == query_type)
                cout << even_count << endl;
            else
                cout << (((s_input - f_input) + 1) - even_count) << endl;
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
