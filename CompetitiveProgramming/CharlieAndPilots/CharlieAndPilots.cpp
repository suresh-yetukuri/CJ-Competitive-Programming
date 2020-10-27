// CharlieAndPilots.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

struct pilot
{
    int assistant_sal;
    int captain_sal;
};

/// TC: Exponenetial
/// SC: nPilots
namespace BruteForce
{
    /// crew_diff = (no of assistant selected - no of captains selected)
    int min_cost(vector<pilot>& pSalary, int& nPilots, int curr_pilot_Idx, int crew_diff)
    {
        if (curr_pilot_Idx == nPilots)
            return 0;

        if (0 == crew_diff)
            return pSalary[curr_pilot_Idx].assistant_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff + 1);
        else if(crew_diff == (nPilots- curr_pilot_Idx))
            return pSalary[curr_pilot_Idx].captain_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff - 1);
        else
        {
            // If selected as assistant
            auto IfAssistant = pSalary[curr_pilot_Idx].assistant_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff + 1);
            // If selected as captain
            auto IfCaptain = pSalary[curr_pilot_Idx].captain_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff - 1);
            
            return min(IfAssistant, IfCaptain);
        }
    }
}

/// TC: nPilots * ((nPilots/2) + 1)
/// SC: nPilots * ((nPilots/2) + 1) + StackSpace(nPilots)
namespace RecursiveDP
{
    /// crew_diff = (no of assistant selected - no of captains selected)
    int min_cost(vector<pilot>& pSalary, int& nPilots, int curr_pilot_Idx, int crew_diff, dp_type& pAux)
    {
        if (curr_pilot_Idx == nPilots)
            return 0;

        if (pAux[curr_pilot_Idx][crew_diff] == -1)
        {
            if (0 == crew_diff)
                pAux[curr_pilot_Idx][crew_diff] = pSalary[curr_pilot_Idx].assistant_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff + 1, pAux);
            else if (crew_diff == (nPilots - curr_pilot_Idx))
                pAux[curr_pilot_Idx][crew_diff] = pSalary[curr_pilot_Idx].captain_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff - 1, pAux);
            else
            {
                // If selected as assistant
                auto IfAssistant = pSalary[curr_pilot_Idx].assistant_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff + 1, pAux);
                // If selected as captain
                auto IfCaptain = pSalary[curr_pilot_Idx].captain_sal + min_cost(pSalary, nPilots, curr_pilot_Idx + 1, crew_diff - 1, pAux);

                pAux[curr_pilot_Idx][crew_diff] = min(IfAssistant, IfCaptain);
            }
        }

        return pAux[curr_pilot_Idx][crew_diff];
    }
}

int main()
{
    int nPilots = 0;
    cin >> nPilots;
    vector<pilot> pSalary(nPilots);
    for (int iCounter = 0; iCounter < nPilots; ++iCounter)
        cin >> pSalary[iCounter].captain_sal >> pSalary[iCounter].assistant_sal;

    dp_type pAux(nPilots, vector<int>((nPilots / 2) + 1, -1));
    auto result = RecursiveDP::min_cost(pSalary, nPilots, 0, 0, pAux);
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
