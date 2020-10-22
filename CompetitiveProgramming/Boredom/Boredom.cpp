// Boredom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <optional>
using namespace std;

namespace BruteForce
{
    int Utility(unordered_map<int, int>& freq_map)
    {
#pragma region Base Condition
        if (freq_map.empty())
            return 0;

        if (freq_map.size() == 1)
        {
            auto curr_item = *(freq_map.begin());
            return curr_item.first * curr_item.second;
        }
#pragma endregion


        int max_possibility = 0;
        int curr_possibility = 0;

        vector<int> unique_set(freq_map.size());
        int fill_counter = 0;
        for (const auto& epair : freq_map)
            unique_set[fill_counter++] = epair.first;


        for (const auto& val : unique_set)
        {
            curr_possibility = val;
            freq_map[val]--;
            if (freq_map[val] == 0)
                freq_map.erase(val);

            // remove x + 1 value
            optional<int> inc_freq = nullopt;
            optional<int> dec_freq = nullopt;
            if (freq_map.find(val + 1) != freq_map.end())
            {
                inc_freq = freq_map[val + 1];
                freq_map.erase(val + 1);
            }

            // remove x - 1 value
            if (freq_map.find(val - 1) != freq_map.end())
            {
                dec_freq = freq_map[val - 1];
                freq_map.erase(val - 1);
            }


            curr_possibility += Utility(freq_map);
            max_possibility = max(curr_possibility, max_possibility);
            
            // restore the state of map
            freq_map[val]++;

            if (inc_freq)
                freq_map[val + 1] = *inc_freq;

            if (dec_freq)
                freq_map[val - 1] = *dec_freq;
        }

        return max_possibility;
    }

    int solve(int n, vector<int> Input) {
       
        // Created Frequency
        unordered_map<int, int> freq_map;
        for (const auto& val : Input)
            freq_map[val]++;
         
        return Utility(freq_map);
    }
}

namespace UsingDP
{
    const int max_value = 1000;
    int solve(int n, vector<int> pInput) {
        if (n == 1)
            return pInput[0];

        vector<int> pAux(max_value + 1, 0);
        for (const auto& val : pInput)
            pAux[val]++;

        for (int iCounter = 2; iCounter <= max_value; ++iCounter)
        {
            auto if_included = (pAux[iCounter] * iCounter) + pAux[iCounter - 2];
            auto if_not_included = pAux[iCounter - 1];
            pAux[iCounter] = max(if_included, if_not_included);
        }

        return pAux[max_value];
    }
}

int main()
{
    vector<int> pInput{ 11, 1, 1, 1, 1, 1 };
    int oResult = UsingDP::solve(pInput.size(), pInput);
    
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
