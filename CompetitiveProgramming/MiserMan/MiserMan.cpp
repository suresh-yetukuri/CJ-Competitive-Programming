// MiserMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;


namespace BruteForce
{
    int min_fare(vector<vector<int>>& pGrid
        , int nCity
        , int nBus
        , int curr_city_idx
        , int prev_bus_idx)
    {

        if (nCity == curr_city_idx)
            return 0;

        auto option_f = INT_MAX;
        auto option_s = INT_MAX;
        auto option_t = INT_MAX;

        option_f = pGrid[curr_city_idx][prev_bus_idx] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx);

        if ((prev_bus_idx - 1) >= 0)
            option_s = pGrid[curr_city_idx][prev_bus_idx - 1] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx - 1);

        if ((prev_bus_idx + 1) < nBus)
            option_t = pGrid[curr_city_idx][prev_bus_idx + 1] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx + 1);

        return min(option_f, min(option_s, option_t));
    }
}

/*
TC:M*(N-1 * M)
SC:M*N + Stack space
*/
namespace RecursiveDP
{
    int min_fare(vector<vector<int>>& pGrid
        , int nCity
        , int nBus
        , int curr_city_idx
        , int prev_bus_idx
        , dp_type& pAux)
    { 
        if (nCity == curr_city_idx)
            return 0;
         
        if (pAux[curr_city_idx][prev_bus_idx] == INT_MAX)
        { 
            auto option_f = INT_MAX;
            auto option_s = INT_MAX;
            auto option_t = INT_MAX;

            option_f = pGrid[curr_city_idx][prev_bus_idx] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx, pAux);

            if ((prev_bus_idx - 1) >= 0)
                option_s = pGrid[curr_city_idx][prev_bus_idx - 1] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx - 1, pAux);

            if ((prev_bus_idx + 1) < nBus)
                option_t = pGrid[curr_city_idx][prev_bus_idx + 1] + min_fare(pGrid, nCity, nBus, curr_city_idx + 1, prev_bus_idx + 1, pAux);

            pAux[curr_city_idx][prev_bus_idx] = min(option_f, min(option_s, option_t));
        }

        return pAux[curr_city_idx][prev_bus_idx];
    }
}


int main()
{
    int nCity = 0;
    int nBus = 0;
    cin >> nCity >> nBus;
    vector<vector<int>> pGrid(nCity, vector<int>(nBus));
    for (int iCounter = 0; iCounter < nCity; ++iCounter)
        for (int jCounter = 0; jCounter < nBus; ++jCounter)
            cin >> pGrid[iCounter][jCounter];

    
    auto result = INT_MAX;
    // We need to explore all option to go from 1->2
    for (int iCounter = 0; iCounter < nBus; ++iCounter)
    {
        dp_type pAux(nCity, vector<int>(nBus, INT_MAX));
        auto curr_fare = pGrid[0][iCounter] + RecursiveDP::min_fare(pGrid, nCity, nBus, 1, iCounter, pAux);
        result = min(result, curr_fare);
    }

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
