// BasicsOfSegmentTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void BuildSegmentTree(vector<int>& pInput
    , vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int fill_Idx)
{
    if (start_Idx == end_Idx)
    {
        pTree[fill_Idx] = pInput[start_Idx];
        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1); 

    // LeftST call
    BuildSegmentTree(pInput, pTree, start_Idx, mid, 2 * fill_Idx);
    // RightST call
    BuildSegmentTree(pInput, pTree, mid + 1, end_Idx, (2 * fill_Idx) + 1);

    pTree[fill_Idx] = pTree[2 * fill_Idx] + pTree[(2 * fill_Idx) + 1];
    return;
}

void UpdateSegmentTree(vector<int>& pInput
    , vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int fill_Idx
    , int change_Idx
    , int new_val)
{
    if (start_Idx == end_Idx)
    {
        pInput[start_Idx] = new_val;
        pTree[fill_Idx] = new_val;
        return;
    }

    int mid = ((start_Idx + end_Idx) >> 1);
    if (change_Idx <= mid)
        UpdateSegmentTree(pInput, pTree, start_Idx, mid, 2 * fill_Idx, change_Idx, new_val);
    else
        UpdateSegmentTree(pInput, pTree, mid + 1, end_Idx, (2 * fill_Idx) + 1, change_Idx, new_val);

    pTree[fill_Idx] = pTree[2 * fill_Idx] + pTree[(2 * fill_Idx) + 1];
    return;
}


int QuerySegmentTree(vector<int>& pTree
    , int start_Idx
    , int end_Idx
    , int node_Idx
    , int range_left
    , int range_right)
{ 
    // 3 Possibilities
    // 1. Completely outside the range
    if (start_Idx > range_right || end_Idx < range_left)
        return 0;

    // 2. Completely inside  the range
    if (start_Idx >= range_left && end_Idx <= range_right)
        return pTree[node_Idx];

    // 3. Partially inside the range
    int mid = ((start_Idx + end_Idx) >> 1);
    auto left_value = QuerySegmentTree(pTree, start_Idx, mid, 2 * node_Idx, range_left, range_right);
    auto right_value = QuerySegmentTree(pTree, mid + 1, end_Idx, (2 * node_Idx) + 1, range_left, range_right);
    return left_value + right_value;
}

int main()
{


    vector<int> pInput{ 1, 2, 3, 4, 5 };
    size_t st_size = pInput.size() * 4u;
    vector<int> pTree(st_size, 0);
    BuildSegmentTree(pInput, pTree, 0, 4, 1);
     
    for (int iCounter = 1; iCounter < st_size; ++iCounter)
        cout << pTree[iCounter] << endl;

    UpdateSegmentTree(pInput, pTree, 0, 4, 1, 2, 10);
    cout << "After Update" << endl;
    for (int iCounter = 1; iCounter < st_size; ++iCounter)
        cout << pTree[iCounter] << endl;

    cout << "Query" << endl;
    auto result = QuerySegmentTree(pTree, 0, 4, 1, 3, 3);
    cout << result;
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
