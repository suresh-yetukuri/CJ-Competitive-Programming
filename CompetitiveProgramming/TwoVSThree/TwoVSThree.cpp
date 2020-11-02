// TwoVSThree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int pPower[100001];

inline int lft_Idx(int node_Idx)
{
    return 2 * node_Idx;
}

inline int rht_Idx(int node_Idx)
{
    return (2 * node_Idx) + 1;
}

void CalculatePower()
{
    pPower[0] = 1;
    for (int iCounter = 1; iCounter < 100001; ++iCounter)
        pPower[iCounter] = (pPower[iCounter - 1] * 2) % 3;
}

void BuildTree(vector<int>& pInput
    , vector<int>& pTree
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
    BuildTree(pInput, pTree, start_Idx, mid, lft_Idx(node_Idx));
    BuildTree(pInput, pTree, mid + 1, end_Idx, rht_Idx(node_Idx));

    auto factor = pPower[end_Idx - mid];
    pTree[node_Idx] = (((pTree[lft_Idx(node_Idx)] * factor) % 3) + pTree[rht_Idx(node_Idx)]) % 3;
    return;
}

void UpdateTree(vector<int>& pInput
    , vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx
    , int change_Idx)
{
    if (start_Idx == end_Idx)
    {
        pInput[start_Idx] = 1;
        pTree[node_Idx] = 1;
        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1);
    if (change_Idx <= mid)
        UpdateTree(pInput, pTree, start_Idx, mid, lft_Idx(node_Idx), change_Idx);
    else
        UpdateTree(pInput, pTree, mid + 1, end_Idx, rht_Idx(node_Idx), change_Idx);

    auto factor = pPower[end_Idx - mid];
    pTree[node_Idx] = (((pTree[lft_Idx(node_Idx)] * factor) % 3) + pTree[rht_Idx(node_Idx)]) % 3;
    return;
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
        return (pTree[node_Idx] * pPower[range_rht - end_Idx]) % 3;

    // Partial Overlap
    int mid = ((start_Idx + end_Idx) >> 1);
    auto lft_val = QueryTree(pTree, start_Idx, mid, lft_Idx(node_Idx), range_lft, range_rht);
    auto rht_val = QueryTree(pTree, mid + 1, end_Idx, rht_Idx(node_Idx), range_lft, range_rht);

    return (lft_val + rht_val) % 3;
}

int main()
{
    CalculatePower();
    int nSize = 0;
    int nQueries = 0;
    string oInput;
    cin >> nSize;
    cin >> oInput;
    vector<int> pInput(nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        pInput[iCounter] = oInput[iCounter] - '0';

    int st_size = static_cast<size_t>(nSize * 4);
    vector<int> pTree(st_size, 0);
    BuildTree(pInput, pTree, 0, nSize - 1, 1);

    cin >> nQueries;
    while (nQueries--)
    {
        int query_type = 0;
        cin >> query_type;
        if (0 == query_type)
        {
            int range_lft = 0;
            int range_rht = 0;
            cin >> range_lft >> range_rht;
            auto result = QueryTree(pTree, 0, nSize - 1, 1, range_lft, range_rht);
            cout << result << endl;
        }
        else
        {
            int change_Idx = 0;
            cin >> change_Idx;
            if (pInput[change_Idx] == 0)
                UpdateTree(pInput, pTree, 0, nSize - 1, 1, change_Idx);
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
