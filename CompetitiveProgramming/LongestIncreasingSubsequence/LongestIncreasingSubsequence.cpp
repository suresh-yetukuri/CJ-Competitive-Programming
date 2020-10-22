// LongestIncreasingSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Using Only Dynamic Programming
TC: O(N^2)
SC: O(N)
*/
int getLISLength(vector<int>& pInput, int nSize)
{
    vector<int> pLIS(nSize, 1);
    int max_lis_length = 1;

    for (int iCounter = 1; iCounter < nSize; ++iCounter)
    {
        for (int jCounter = iCounter - 1; jCounter >= 0; --jCounter)
        {
            if (pInput[jCounter] <= pInput[iCounter]) 
                pLIS[iCounter] = max(pLIS[jCounter] + 1, pLIS[iCounter]); 
        }

        max_lis_length = max(max_lis_length, pLIS[iCounter]);
    } 

    return max_lis_length;
}

/*
Using BinarySearch + Dynamic Programming
TC: O(NLogN)
SC: O(N)
*/
int getLISLengthOpt(vector<int>& pInput, int nSize)
{
    if (nSize <= 1)
        return nSize;

    vector<int> pLIS(nSize + 1ll);
    pLIS[1] = pInput[0]; 
    int lengthCounter = 1;

    for (int iCounter = 1; iCounter < nSize; ++iCounter)
    {
        if (pInput[iCounter] > pLIS[lengthCounter])
            pLIS[++lengthCounter] = pInput[iCounter];
        else if (pInput[iCounter] < pLIS[1])
            pLIS[1] = pInput[iCounter];
        else
        {
            auto lb_itr = lower_bound(pLIS.begin() + 1, pLIS.begin() + lengthCounter + 1, pInput[iCounter]);
            if (*lb_itr != pInput[iCounter])
            {
                auto actual_pos = lb_itr - pLIS.begin();
                pLIS[actual_pos] = pInput[iCounter];
            }
        }
    }

    return lengthCounter;
}


vector<int> BuildLISArray(vector<int>& pInput, int nSize)
{
    if (nSize <= 1)
        return vector<int>(nSize, 1);

    vector<int> pLIS(nSize, 1); 
    for (int iCounter = 1; iCounter < nSize; ++iCounter)
    {
        for (int jCounter = iCounter - 1; jCounter >= 0; --jCounter)
        {
            if (pInput[jCounter] < pInput[iCounter])
                pLIS[iCounter] = max(pLIS[jCounter] + 1, pLIS[iCounter]);
        } 
    }

    return pLIS;
}

vector<int> BuildLISArrayOpt(vector<int>& pInput, int nSize)
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

void print(vector<int>& pInput)
{
    for_each(pInput.begin(), pInput.end(), [](int val)->void{
        cout << val << " ";
    });
    cout << endl;
}

int main()
{ 
    // vector<int> pInput = { 10,9,2,5,3,7,101,18 };
    vector<int> pInput = { 7, 3, 5, 3, 6, 2, 9, 8 };
    auto pDynamic = BuildLISArray(pInput, pInput.size());
    auto pBSDynamic = BuildLISArrayOpt(pInput, pInput.size());

    print(pDynamic);
    print(pBSDynamic);
    if (pDynamic == pBSDynamic)
        cout << "True";
    else
        cout << "False";
    
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
