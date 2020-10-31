// WeightedJobScheduling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job
{
    int start;
    int finish;
    int profit;
};

int binary_search_l(vector<Job>& Jobs, int low, int high, int val)
{
    int ans_Idx = -1;
    while (low <= high)
    {
        int mid = low + ((high - low) >> 1);
        if (Jobs[mid].finish <= val) {
            ans_Idx = mid;
            low = mid + 1;
        }
        else
            high = mid - 1; 
    }

    return ans_Idx;
}

int main()
{  
    int nJobs = 0;
    cin >> nJobs;
    vector<Job> Jobs(nJobs);
    for (int iCounter = 0; iCounter < nJobs; ++iCounter)
        cin >> Jobs[iCounter].start >> Jobs[iCounter].finish >> Jobs[iCounter].profit;

    sort(Jobs.begin(), Jobs.end(), [](Job& first, Job& second)->bool {
        return first.finish < second.finish;
    });

    vector<long long> pAux(nJobs, 0);
    pAux[0] = Jobs[0].profit;
    for (int iCounter = 1; iCounter < nJobs; ++iCounter)
    {
        long long IfExcluded = pAux[iCounter - 1];
        long long IfIncluded = Jobs[iCounter].profit;
        auto Idx = binary_search_l(Jobs, 0, iCounter - 1, Jobs[iCounter].start);
         
        if (Idx != -1)
            IfIncluded += pAux[Idx];

        pAux[iCounter] = max(IfExcluded, IfIncluded);
    }

    cout << pAux[nJobs - 1] << endl; 
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
