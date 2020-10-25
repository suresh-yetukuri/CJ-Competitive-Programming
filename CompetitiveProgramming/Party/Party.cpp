// Party.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct ret_Type
{
    int fee;
    int fun;

    ret_Type&& operator + (ret_Type oInput)
    {
        return move(ret_Type{ fee + oInput.fee, fun + oInput.fun });
    }
};

/// <summary>
/// TC: Exponential
/// SC: number of parties
/// </summary>
namespace BruteForce
{
    ret_Type maxFun(vector<int>& partyfee
                  , vector<int>& fun
                  , int curr_party_Idx
                  , int nBudget)
    {
        if (partyfee.size() == curr_party_Idx || 0 == nBudget)
            return ret_Type{ 0,0 };

        auto IfPartyAttended = ret_Type{ 0,0 };
        auto IfPartyNotAttended = ret_Type{ 0,0 };

        if (nBudget >= partyfee[curr_party_Idx])
        {
            IfPartyAttended.fee += partyfee[curr_party_Idx]; // Added the fee
            IfPartyAttended.fun += fun[curr_party_Idx];  // Added the fun 
            IfPartyAttended = IfPartyAttended + maxFun(partyfee, fun, curr_party_Idx + 1, nBudget - partyfee[curr_party_Idx]); 
        } 

        IfPartyNotAttended = IfPartyNotAttended + maxFun(partyfee, fun, curr_party_Idx + 1, nBudget);

        if (IfPartyAttended.fun > IfPartyNotAttended.fun)
            return IfPartyAttended;
        else if(IfPartyAttended.fun < IfPartyNotAttended.fun)
            return IfPartyNotAttended;
        else
        {
            if (IfPartyAttended.fee < IfPartyNotAttended.fee)
                return IfPartyAttended;
            else
                return IfPartyNotAttended;
        }
    }
}


/// <summary>
/// TC: N * Budget
/// SC: Budget
/// </summary>
namespace IterativeDP
{
    ret_Type maxFun(vector<int>& partyfee
                  , vector<int>& fun 
                  , int nBudget)
    {
        if (partyfee.size() == 0 || 0 == nBudget)
            return ret_Type{ 0,0 };

        vector<ret_Type> pCurrentAux(nBudget + 1, ret_Type{ 0,0 });
        vector<ret_Type> pLastAux(nBudget + 1, ret_Type{ 0,0 });

        for (int iCounter = partyfee.size() - 1; iCounter >= 0; --iCounter)
        {
            for (int jCounter = 1; jCounter <= nBudget; ++jCounter)
            {
                auto IfPartyAttended = ret_Type{ 0,0 };
                auto IfPartyNotAttended = ret_Type{ 0,0 };

                if (jCounter >= partyfee[iCounter])
                {
                    IfPartyAttended.fee += partyfee[iCounter]; // Added the fee
                    IfPartyAttended.fun += fun[iCounter]; // Added the fun 
                    IfPartyAttended = IfPartyAttended + pLastAux[jCounter - partyfee[iCounter]];
                }
                    
                IfPartyNotAttended = IfPartyNotAttended + pLastAux[jCounter];

                if (IfPartyAttended.fun > IfPartyNotAttended.fun)
                    pCurrentAux[jCounter] = IfPartyAttended;
                else if (IfPartyAttended.fun < IfPartyNotAttended.fun)
                    pCurrentAux[jCounter] = IfPartyNotAttended;
                else
                {
                    if (IfPartyAttended.fee < IfPartyNotAttended.fee)
                        pCurrentAux[jCounter] = IfPartyAttended;
                    else
                        pCurrentAux[jCounter] = IfPartyNotAttended;
                }
            }

            swap(pCurrentAux, pLastAux);
        }

        return pLastAux[nBudget];
    }
}

int main()
{
    
	while (true)
	{
		int nPartyCount = 0;
		int nBudget = 0;
		cin >> nBudget >> nPartyCount;

		// Exit Condition
		if (0 == nPartyCount && 0 == nBudget)
			break;

		vector<int> parties(nPartyCount, 0);
		vector<int> fun(nPartyCount, 0);

		for (int iCounter = 0; iCounter < nPartyCount; ++iCounter)
			cin >> parties[iCounter] >> fun[iCounter];

        auto result = IterativeDP::maxFun(parties, fun, nBudget);
        cout << result.fee << " " << result.fun << endl;
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
