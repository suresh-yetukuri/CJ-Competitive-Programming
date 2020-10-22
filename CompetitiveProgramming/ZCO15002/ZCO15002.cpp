// ZCO15002.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

namespace UsingTwoPointer
{
    long long CountPairs(vector<int>& pSequence, int nSequence, int kAbsDiff)
    {
        sort(pSequence.begin(), pSequence.end());
        long long nPairCount = 0;
        int pCounter = 0;
        int qCounter = 0;
        while (qCounter < nSequence)
        {
            if (abs(pSequence[qCounter] - pSequence[pCounter]) >= kAbsDiff) {
                nPairCount += (nSequence - qCounter);
                ++pCounter;
            }
            else
                ++qCounter;
        }

        return nPairCount;
    }
}

namespace UsingBinarySearch
{
    int FindLowestIndex(vector<int>& pSequence, int nSequence, int kAbsDiff, int curr_idx)
    {
        int low = curr_idx + 1;
        int high = nSequence - 1;
        int lowest_Idx = -1;
        while (low <= high)
        {
            int mid = low + ((high - low) >> 1);
            if (abs(pSequence[mid] - pSequence[curr_idx]) >= kAbsDiff) {
                high = mid - 1;
                lowest_Idx = mid;
            }
            else
                low = mid + 1;
        }

        return lowest_Idx;
    }

    long long CountPairs(vector<int>& pSequence, int nSequence, int kAbsDiff)
    {
        sort(pSequence.begin(), pSequence.end());
        long long nPairCount = 0;
        for (int iCounter = 0; iCounter < (nSequence - 1); ++iCounter)
        {
            int lowest_Idx = FindLowestIndex(pSequence, nSequence, kAbsDiff, iCounter);
            if(lowest_Idx < nSequence && lowest_Idx > iCounter)
                nPairCount += (nSequence - lowest_Idx);
        }

        return nPairCount;
    }
}

int main()
{
    int nSequence = 0;
    int kAbsDiff = 0;
    cin >> nSequence >> kAbsDiff;

    vector<int> pSequence(nSequence);
    for (int iCounter = 0; iCounter < nSequence; ++iCounter)
        cin >> pSequence[iCounter];
     
    cout << UsingBinarySearch::CountPairs(pSequence, nSequence, kAbsDiff) << endl;

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
