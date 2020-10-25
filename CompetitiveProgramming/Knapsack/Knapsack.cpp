// Knapsack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

/// <summary>
/// TC: Exponential
/// SC: number of sack
/// </summary>
namespace BruteForce
{
    int maxKnapsackVal(vector<int>& sack_weight
        , vector<int> sack_value
        , int curr_sack_Idx
        , int nKnapsackCap)
    {
        if (sack_weight.size() == curr_sack_Idx || 0 == nKnapsackCap)
            return 0;

        auto IfSackIncluded = 0;
        auto IfSackExcluded = 0;

        if (nKnapsackCap >= sack_weight[curr_sack_Idx])
            IfSackIncluded = sack_value[curr_sack_Idx]
            + maxKnapsackVal(sack_weight, sack_value, curr_sack_Idx + 1, nKnapsackCap - sack_weight[curr_sack_Idx]);

        IfSackExcluded = maxKnapsackVal(sack_weight, sack_value, curr_sack_Idx + 1, nKnapsackCap);

        return max(IfSackIncluded, IfSackExcluded);
    }
}

/// <summary>
/// TC: nSize*nKnapsackCap
/// SC: nSize*nKnapsackCap + StackSpace(nSize)
/// </summary>
namespace RecursiveDP
{
    int maxKnapsackVal(vector<int>& sack_weight
                     , vector<int> sack_value
                     , int curr_sack_Idx
                     , int nKnapsackCap
                     , dp_type& pAux)
    {
        if (sack_weight.size() == curr_sack_Idx || 0 == nKnapsackCap)
            return 0;

        auto IfSackIncluded = 0;
        auto IfSackExcluded = 0;

        if (pAux[curr_sack_Idx][nKnapsackCap] == -1)
        {
            if (nKnapsackCap >= sack_weight[curr_sack_Idx])
                IfSackIncluded = sack_value[curr_sack_Idx]
                + maxKnapsackVal(sack_weight, sack_value, curr_sack_Idx + 1, nKnapsackCap - sack_weight[curr_sack_Idx], pAux);

            IfSackExcluded = maxKnapsackVal(sack_weight, sack_value, curr_sack_Idx + 1, nKnapsackCap, pAux);

            pAux[curr_sack_Idx][nKnapsackCap] = max(IfSackIncluded, IfSackExcluded);
        }

        return pAux[curr_sack_Idx][nKnapsackCap];
    }
}


/// <summary>
/// TC: nSize*nKnapsackCap
/// SC: nSize*nKnapsackCap
/// </summary>
namespace IterativeDP
{
    int maxKnapsackVal(vector<int>& sack_weight
                     , vector<int> sack_value
                     , int nSize
                     , int nKnapsackCap)
    {
        if (nSize == 0 || 0 == nKnapsackCap)
            return 0;

        dp_type pAux(nSize + 1, vector<int>(nKnapsackCap + 1, 0));

        for (int iCounter = nSize - 1; iCounter >= 0; --iCounter)
        {
            for (int jCounter = 1; jCounter <= nKnapsackCap; ++jCounter)
            {
                auto IfSackIncluded = 0;
                auto IfSackExcluded = 0;

                if (jCounter >= sack_weight[iCounter])
                    IfSackIncluded = sack_value[iCounter] 
                    + pAux[iCounter + 1][jCounter - sack_weight[iCounter]];

                IfSackExcluded = pAux[iCounter + 1][jCounter];
                pAux[iCounter][jCounter] = max(IfSackIncluded, IfSackExcluded);
            }
        }

        return pAux[0][nKnapsackCap];
    }
}

/// <summary>
/// TC: nSize*nKnapsackCap
/// SC: nKnapsackCap + nKnapsackCap
/// </summary>
namespace IterativeDPSapceOptimized
{
    int maxKnapsackVal(vector<int>& sack_weight
        , vector<int> sack_value
        , int nSize
        , int nKnapsackCap)
    {
        if (nSize == 0 || 0 == nKnapsackCap)
            return 0;

        vector<int> pCurrentAux(nKnapsackCap + 1, 0);
        vector<int> pLastAux(nKnapsackCap + 1, 0);

        for (int iCounter = nSize - 1; iCounter >= 0; --iCounter)
        {
            for (int jCounter = 1; jCounter <= nKnapsackCap; ++jCounter)
            {
                auto IfSackIncluded = 0;
                auto IfSackExcluded = 0;

                if (jCounter >= sack_weight[iCounter])
                    IfSackIncluded = sack_value[iCounter]
                    + pLastAux[jCounter - sack_weight[iCounter]];

                IfSackExcluded = pLastAux[jCounter];
                pCurrentAux[jCounter] = max(IfSackIncluded, IfSackExcluded);
            }

            swap(pCurrentAux, pLastAux);
        }

        return pLastAux[nKnapsackCap];
    }
}

int main()
{
    
    int nSize = 0;
    int nKnapsackCap = 0;
    cin >> nSize;
    vector<int> sack_weight(nSize, 0);
    vector<int> sack_value(nSize, 0);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> sack_weight[iCounter];

    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> sack_value[iCounter];

    cin >> nKnapsackCap;

    //dp_type pAux(nSize, vector<int>(nKnapsackCap + 1, -1));
    auto result = IterativeDPSapceOptimized::maxKnapsackVal(sack_weight, sack_value, nSize, nKnapsackCap);
    cout << result << endl;
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
