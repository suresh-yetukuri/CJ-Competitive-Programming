// LongestBitonicSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.youtube.com/watch?v=66w10xKzbRM

vector<int> BuildLRLISArray(vector<int>& pInput, int nSize)
{
    if (nSize <= 1)
        return vector<int>(nSize, 1);

    vector<int> pOutput(nSize, 1);
    vector<int> pLIS(nSize + 1ll);
    pLIS[1] = pInput[0];
    int lengthCounter = 1;

    for (int iCounter = 1; iCounter < nSize; ++iCounter)
    {
        if (pInput[iCounter] > pLIS[lengthCounter])
        {
            pLIS[++lengthCounter] = pInput[iCounter];
            pOutput[iCounter] = lengthCounter;
        }
        else if (pInput[iCounter] < pLIS[1])
            pLIS[1] = pInput[iCounter];
        else
        {
            auto lb_itr = lower_bound(pLIS.begin() + 1, pLIS.begin() + lengthCounter + 1, pInput[iCounter]);
            auto actual_length = lb_itr - pLIS.begin();
            if (*lb_itr != pInput[iCounter])
                pLIS[actual_length] = pInput[iCounter];

            pOutput[iCounter] = actual_length;
        }
    }

    return pOutput;
}

vector<int> BuildRLLISArray(vector<int>& pInput, int nSize)
{
    if (nSize <= 1)
        return vector<int>(nSize, 1);

    vector<int> pOutput(nSize, 1);
    vector<int> pLIS(nSize + 1ll);
    pLIS[1] = pInput[nSize - 1ll];
    int lengthCounter = 1;

    for (int iCounter = (nSize - 2); iCounter >= 0; --iCounter)
    {
        if (pInput[iCounter] > pLIS[lengthCounter])
        {
            pLIS[++lengthCounter] = pInput[iCounter];
            pOutput[iCounter] = lengthCounter;
        }
        else if (pInput[iCounter] < pLIS[1])
            pLIS[1] = pInput[iCounter];
        else
        {
            auto lb_itr = lower_bound(pLIS.begin() + 1, pLIS.begin() + lengthCounter + 1, pInput[iCounter]);
            auto actual_length = lb_itr - pLIS.begin();
            if (*lb_itr != pInput[iCounter])
                pLIS[actual_length] = pInput[iCounter];

            pOutput[iCounter] = actual_length;
        }
    }

    return pOutput;
}

int main()
{
    vector<int> pInput = { 5, 1 };
    auto pLR_LIS = BuildLRLISArray(pInput, pInput.size());
    auto pRL_LIS = BuildRLLISArray(pInput, pInput.size());
    
    int max_length = 0;
    for (int iCounter = 0; iCounter < pInput.size(); ++iCounter) 
        max_length = max(max_length, (pLR_LIS[iCounter] + pRL_LIS[iCounter]) - 1); 
     
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
