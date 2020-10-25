// Subset.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<bool>>;

/// <summary>
/// TC: Exponential
/// SC: N(Stack Space)
/// </summary>
namespace BruteForce
{
    bool IsSubsetSumExist(vector<int>& pInput, int nSize, int curr_Idx, int target)
    {
        if (nSize == curr_Idx && target > 0)
            return false;

        if (target == 0)
            return true;

        bool IfIncluded = false;
        bool IfExcluded = false;
        if(target >= pInput[curr_Idx])
            IfIncluded = IsSubsetSumExist(pInput, nSize, curr_Idx + 1, target - pInput[curr_Idx]);

        if(!IfIncluded)
            IfExcluded = IsSubsetSumExist(pInput, nSize, curr_Idx + 1, target);

        return (IfIncluded || IfExcluded);
    }
}

/// <summary>
/// TC: nSize * target
/// SC: nSize * target
/// </summary>
namespace IterativeDP
{
    bool IsSubsetSumExist(vector<int>& pInput, int nSize, int target)
    { 
        if (target == 0)
            return true;


        dp_type pAux(nSize + 1, vector<bool>(target + 1, false));
        for (int iCounter = 0; iCounter <= nSize; ++iCounter)
            pAux[iCounter][0] = true;


        for(int iCounter = nSize - 1; iCounter >= 0; --iCounter)
            for (int jCounter = 1; jCounter <= target; ++jCounter)
            {
                bool IfIncluded = false;
                bool IfExcluded = false;
                if (jCounter >= pInput[iCounter])
                    IfIncluded = pAux[iCounter + 1][jCounter - pInput[iCounter]];

                if (!IfIncluded)
                    IfExcluded = pAux[iCounter + 1][jCounter];

                pAux[iCounter][jCounter] = IfIncluded || IfExcluded;
            }
         
        return pAux[0][target];
    }
}


/// <summary>
/// TC: nSize * target
/// SC: target
/// </summary>
namespace IterativeDPSapceOptimized
{
    bool IsSubsetSumExist(vector<int>& pInput, int nSize, int target)
    {
        if (target == 0)
            return true;

        vector<bool> pLastAux(target + 1, false);
        vector<bool> pCurrentAux(target + 1, false);
        pLastAux[0] = true;

        for (int iCounter = nSize - 1; iCounter >= 0; --iCounter)
        {
            pCurrentAux[0] = true; // To achieve zero sum, always possible with empty subset
            for (int jCounter = 1; jCounter <= target; ++jCounter)
            {
                bool IfIncluded = false;
                bool IfExcluded = false;
                if (jCounter >= pInput[iCounter])
                    IfIncluded = pLastAux[jCounter - pInput[iCounter]];

                if (!IfIncluded)
                    IfExcluded = pLastAux[jCounter];

                pCurrentAux[jCounter] = IfIncluded || IfExcluded;
            }

            swap(pLastAux, pCurrentAux);
        }

        return pLastAux[target];
    }
}

int main()
{
    int nSize = 0;
    int target = 0;
    cin >> nSize;
    vector<int> pInput(nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> pInput[iCounter];

    cin >> target;
    auto result = IterativeDPSapceOptimized::IsSubsetSumExist(pInput, nSize, target);
    if (result)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
     
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
