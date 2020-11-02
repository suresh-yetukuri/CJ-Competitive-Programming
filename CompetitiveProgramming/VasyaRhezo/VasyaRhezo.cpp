// VasyaRhezo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
    int warrior;
    int a_val;
    int b_val;

    node()
    {
        warrior = INT_MAX;
        a_val = INT_MIN;
        b_val = INT_MAX;
    }

};

inline int lft_Idx(int node_Idx)
{
    return 2 * node_Idx;
}

inline int rht_Idx(int node_Idx)
{
    return (2 * node_Idx) + 1;
}

inline node getSuperWarrior(node& first, node& second)
{
    if (first.a_val > second.a_val)
        return first;
    else if (first.a_val == second.a_val)
    {
        if (first.b_val < second.b_val)
            return first;
        else if (first.b_val == second.b_val)
        {
            if (first.warrior < second.warrior)
                return first;
            else
                return second;
        }
    }

    return second;
}

void BuildTree(vector<int>& pInputA
    , vector<int>& pInputB
    , vector<node>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx)
{
    if (start_Idx == end_Idx)
    {
        pTree[node_Idx].warrior = start_Idx + 1;
        pTree[node_Idx].a_val = pInputA[start_Idx];
        pTree[node_Idx].b_val = pInputB[start_Idx];
        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1);
    BuildTree(pInputA, pInputB, pTree, start_Idx, mid, lft_Idx(node_Idx));
    BuildTree(pInputA, pInputB, pTree, mid + 1, end_Idx, rht_Idx(node_Idx));
    pTree[node_Idx] = getSuperWarrior(pTree[lft_Idx(node_Idx)], pTree[rht_Idx(node_Idx)]);
    return;
}

node QueryTree(vector<node>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx
    , int range_lft
    , int range_rht)
{

    // No Overlap
    if (start_Idx > range_rht || end_Idx < range_lft)
        return node{};

    // Complete Overlap
    if (start_Idx >= range_lft && end_Idx <= range_rht)
        return pTree[node_Idx];

    // Partial Overlap
    int mid = ((start_Idx + end_Idx) >> 1);
    auto lft_val = QueryTree(pTree, start_Idx, mid, lft_Idx(node_Idx), range_lft, range_rht);
    auto rht_val = QueryTree(pTree, mid + 1, end_Idx, rht_Idx(node_Idx), range_lft, range_rht);
    return getSuperWarrior(lft_val, rht_val);
}

int main()
{
    int nWarriors = 0;
    cin >> nWarriors;
    vector<int> pInputA(nWarriors);
    vector<int> pInputB(nWarriors);
    for (int iCounter = 0; iCounter < nWarriors; ++iCounter)
        cin >> pInputA[iCounter];

    for (int iCounter = 0; iCounter < nWarriors; ++iCounter)
        cin >> pInputB[iCounter];

    size_t st_size = static_cast<size_t>(nWarriors * 4);
    vector<node> pTree(st_size, node{});
    BuildTree(pInputA, pInputB, pTree, 0, nWarriors - 1, 1);

    int nDays = 0;
    cin >> nDays;

    while (nDays--)
    {
        int range_lft = 0;
        int range_rht = 0;
        cin >> range_lft >> range_rht;
        auto result = QueryTree(pTree, 0, nWarriors - 1, 1, range_lft - 1, range_rht - 1);
        cout << result.warrior << endl;
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
