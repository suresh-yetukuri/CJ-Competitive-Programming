// CHEFRES.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    while (nTestCase--)
    {
        int nInterval = 0;
        int nPerson = 0;
        cin >> nInterval >> nPerson;

        vector<pair<int, int>> pIntervals(nInterval);
        for (int iCounter = 0; iCounter < nInterval; ++iCounter)
        {
            pair<int, int> curr_interval;
            cin >> curr_interval.first >> curr_interval.second;
            pIntervals[iCounter] = curr_interval;
        }

        sort(pIntervals.begin(), pIntervals.end());

        while (nPerson--)
        { 
            int curr_time;
            cin >> curr_time;
            int wait_period = -1;
            auto position = lower_bound(pIntervals.begin(), pIntervals.end(), make_pair(curr_time, 0)) - pIntervals.begin();
            if (0 == position)
                wait_period = pIntervals[position].first - curr_time;
            else
            { 
                if (pIntervals[position - 1].second > curr_time)
                    wait_period = 0;
                else if (position < nInterval)
                    wait_period = pIntervals[position].first - curr_time;
                else
                    wait_period = -1;
            }

            cout << wait_period << endl;
        }
    }

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
