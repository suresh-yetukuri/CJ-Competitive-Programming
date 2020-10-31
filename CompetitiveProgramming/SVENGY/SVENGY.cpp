// SVENGY.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    long long nTownCount = 0;
    cin >> nTownCount;
    vector<long long> pInput(nTownCount, 0);
    for (int iCounter = 0; iCounter < nTownCount; ++iCounter)
        cin >> pInput[iCounter];

    long long curr_city = 0; 
    long long min_energy_cost = 0;
    while (curr_city < (nTownCount-1))
    {
        long long next_city = curr_city + 1;
        while (next_city < (nTownCount - 1))
        {
            if ((abs(pInput[curr_city]) > abs(pInput[next_city]))
                || (abs(pInput[curr_city]) == abs(pInput[next_city]) && pInput[curr_city] > 0))
                break;
            else
                ++next_city;
        }

        min_energy_cost += ((next_city - curr_city) * pInput[curr_city])
            + ((next_city * next_city) - (curr_city * curr_city)) * (pInput[curr_city] * pInput[curr_city]);
        curr_city = next_city;
    }

    cout << min_energy_cost << endl;
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
