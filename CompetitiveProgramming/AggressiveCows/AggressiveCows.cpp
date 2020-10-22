#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;


bool IsValidArrangement(vector<int>& pArrangement, int nStalls, int nCows, int target_distance)
{
    // we have arranged one cow at first stall by default
    int nCows_Arranged = 1;
    int current_stall = 1;
    int last_stall_arranged = 0;
    while ((nCows_Arranged < nCows) && (current_stall < nStalls))
    {
        if ((pArrangement[current_stall] - pArrangement[last_stall_arranged]) >= target_distance)
        {
            ++nCows_Arranged;
            last_stall_arranged = current_stall;
        }

        ++current_stall;
    }

    if (nCows_Arranged == nCows)
        return true;

    return false;
}

int getLargestMinDistance(vector<int>& pArrangement, int nStalls, int nCows)
{
    // sort the distances
    sort(pArrangement.begin(), pArrangement.end());

    int min_distance = 0;
    int max_distance = pArrangement[nStalls - 1] - pArrangement[0];
    while (min_distance < max_distance)
    {
        int mid = min_distance + (((max_distance - min_distance) + 1) >> 1);
        if (IsValidArrangement(pArrangement, nStalls, nCows, mid))
            min_distance = mid;
        else
            max_distance = mid - 1;
    }

    return max_distance;
}

int main() {

    int nTestCase = 0;
    cin >> nTestCase;
    while (nTestCase--)
    {
        int nStalls;
        int nCows;
        cin >> nStalls >> nCows;

        vector<int> pArrangement(nStalls);
        for (int iCounter = 0; iCounter < nStalls; ++iCounter)
            cin >> pArrangement[iCounter];

        cout << getLargestMinDistance(pArrangement, nStalls, nCows) << endl;
    }

    return 0;
}