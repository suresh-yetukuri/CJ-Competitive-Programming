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
ELogE + E*V, V
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


/*
ELogE + ELogV, V
Cycle Detection: Union By Rank and Path Compression
*/
struct disnode
{
    int parent;
    int rank;
};

int FindParentPlusCompression(vector<disnode>& pParentArray, int target)
{
    if (pParentArray[target].parent != target)
        pParentArray[target].parent = FindParentPlusCompression(pParentArray, pParentArray[target].parent);

    return pParentArray[target].parent;
}

void Union(vector<disnode>& pParentArray, int sParent, int dParent)
{
    if (pParentArray[sParent].rank < pParentArray[dParent].rank)
        pParentArray[sParent].parent = dParent;
    else if(pParentArray[sParent].rank > pParentArray[dParent].rank)
        pParentArray[dParent].parent = sParent;
    else
    {
        pParentArray[dParent].parent = sParent;
        pParentArray[sParent].rank++;
    }
}

void mst_kruskalOpt(vector<node>& pInput, int nVertices, int nEdges)
{
    int nCount = 0;
    vector<node> pMST;
    vector<disnode> pParentArray(nVertices);
    for (int iCounter = 0; iCounter < nVertices; ++iCounter) {
        pParentArray[iCounter].parent = iCounter;
        pParentArray[iCounter].rank = 0;
    }

    for (auto& oNode : pInput)
    {
        auto srcParent = FindParentPlusCompression(pParentArray, oNode.src);
        auto destParent = FindParentPlusCompression(pParentArray, oNode.dest);

        if (srcParent != destParent)
        { 
            Union(pParentArray, srcParent, destParent);
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

    mst_kruskalOpt(pInput, nVertices, nEdges);

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
