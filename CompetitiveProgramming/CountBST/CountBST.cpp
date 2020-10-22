// CountBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const long long M = 1e9 + 7;

/*
TC: Exponention N^N
SC: N
*/
long long CountBST(int N)
{
    if (N <= 1)
        return 1;

    long long UniqueBSTCount = 0;
    for (int iRootCounter = 1; iRootCounter <= N; ++iRootCounter)
    {
        auto left_unq_bst = CountBST(iRootCounter - 1);
        auto right_unq_bst = CountBST(N - iRootCounter);
        UniqueBSTCount = (UniqueBSTCount + (left_unq_bst * right_unq_bst) % M) % M;
    }

    return UniqueBSTCount;
}

/*
TC: N^2
SC: N + N (Stack Recursion)
*/
long long CountBSTDP(int N, vector<long long>& pAux)
{
    if (N <= 1)
        return 1;

    if (pAux[N] == 0)
    {
        for (int iRootCounter = 1; iRootCounter <= N; ++iRootCounter)
        {
            auto left_unq_bst = CountBSTDP(iRootCounter - 1, pAux);
            auto right_unq_bst = CountBSTDP(N - iRootCounter, pAux);
            pAux[N] = (pAux[N] + (left_unq_bst * right_unq_bst) % M) % M;
        }
    }

    return pAux[N];
}

/*
TC: N^2
SC: N
*/
long long CountBSTDPOpt(int n)
{
    vector<long long> pAux(n + 1, 0);
    pAux[0] = pAux[1] = 1;

    for (int iCounter = 2; iCounter <= n; ++iCounter)
        for (int iRootCounter = 1; iRootCounter <= iCounter; ++iRootCounter)
            pAux[iCounter] = (pAux[iCounter] + (pAux[iRootCounter - 1] * pAux[iCounter - iRootCounter]) % M) % M;

    return pAux[n];
}


int main()
{
    int N = 0;
    cin >> N;
    vector<long long> pAux(N + 1, 0);
    pAux[0] = pAux[1] = 1;
    cout << CountBSTDP(N, pAux) << endl;
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
