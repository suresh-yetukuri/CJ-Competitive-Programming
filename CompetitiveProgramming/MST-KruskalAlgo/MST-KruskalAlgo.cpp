// MST-KruskalAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct node
{
    int src;
    int dest;
    int weight;
};

int getParent(vector<int>& pParentArray, int curr_Idx)
{
    if (curr_Idx == pParentArray[curr_Idx])
        return curr_Idx;

    return getParent(pParentArray, pParentArray[curr_Idx]);
}

/*
ELogE + E*V
Cycle Detection: Union Find Algorithm
*/
void mst_kruskal(vector<node>& pInput, int nVertices, int nEdges)
{
    int nCount = 0;
    vector<node> pMST;
    vector<int> pParentArray(nVertices);
    for (int iCounter = 0; iCounter < nVertices; ++iCounter)
        pParentArray[iCounter] = iCounter;

    for (auto& oNode : pInput)
    {
        auto srcParent = getParent(pParentArray, oNode.src);
        auto destParent = getParent(pParentArray, oNode.dest);

        if (srcParent != destParent)
        {
            pParentArray[srcParent] = destParent;
            pMST.push_back(oNode);
            ++nCount;
        }

        if (nCount == nVertices - 1)
            break;
    }

    for (auto& oNode : pMST) {
        if (oNode.src > oNode.dest)
            swap(oNode.src, oNode.dest);

        cout << oNode.src << " " << oNode.dest << " " << oNode.weight << endl;
    }
}

// Learn Cycle Detection: Union By Rank and Path Compression

int main()
{
    int nVertices = 0;
    int nEdges = 0;
    cin >> nVertices >> nEdges;
    vector<node> pInput(nEdges);
    for (int iCounter = 0; iCounter < nEdges; ++iCounter)
        cin >> pInput[iCounter].src >> pInput[iCounter].dest >> pInput[iCounter].weight;

    sort(pInput.begin(), pInput.end(), [](node& fnode, node& snode)->bool {
        return fnode.weight < snode.weight;
        });

    mst_kruskal(pInput, nVertices, nEdges);

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
