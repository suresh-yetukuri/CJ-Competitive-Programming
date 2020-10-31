// ProblemDiscussion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using ll = long long;
namespace BruteForce
{
    ll Utility(vector<ll>& pInput, int Idx, int nSize, ll k, ll min_ele, ll max_ele)
    {
        if (Idx == nSize)
            return (max_ele - min_ele);

        auto option_decrease = Utility(pInput, Idx + 1, nSize, k, min(min_ele, pInput[Idx] - k), max(max_ele, pInput[Idx] - k));
        auto option_increase = Utility(pInput, Idx + 1, nSize, k, min(min_ele, pInput[Idx] + k), max(max_ele, pInput[Idx] + k));
        return min(option_increase, option_decrease);
    }
}

/*
TC: NLogN + N
SC: 1
*/
namespace Greedy
{
    ll Utility(vector<ll>& pInput, int nSize, ll k)
    {
        if (nSize <= 1)
            return 0;

        sort(pInput.begin(), pInput.end());
        auto actual_diff = pInput[nSize - 1] - pInput[0];
        ll small = pInput[0] + k;
        ll big = pInput[nSize - 1] - k;
        if (small > big)
            swap(small, big);

        for (int iCounter = 1; iCounter < (nSize - 1); ++iCounter)
        {
            auto IfAdded = pInput[iCounter] + k;
            auto IfSubtracted = pInput[iCounter] - k;

            if ((IfSubtracted >= small) || (IfAdded <= big))
                continue;
            else
            {
                if ((IfAdded - small) <= (big - IfSubtracted))
                    big = IfAdded;
                else
                    small = IfSubtracted;
            }
        }

        return min(actual_diff, big - small);
    }
}

int main()
{
    int nSize = 0;
    ll k = 0;
    cin >> nSize >> k;
    vector<ll> pInput(nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> pInput[iCounter];  


    ll min_ele = INT_MAX;
    ll max_ele = INT_MIN;
    auto result = Greedy::Utility(pInput, nSize, k);
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
