// TraderProfit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;


/// <summary>
/// TC: Exponential
/// SC: nDays
/// </summary>
namespace BruteForce
{
    int max_profit(vector<int>& pStockPrices, int nDays, int buying_Idx, int nTransaction)
    {
        if ((buying_Idx >= nDays) || nTransaction == 0)
            return 0;

        int max_curr_profit_f = INT_MIN;  // If Transaction start from current day
        int max_curr_profit_s = INT_MIN;  // If Transaction doesn't start from current day
       
        int curr_profit = 0;
        for (int selling_Idx = buying_Idx + 1; selling_Idx < nDays; ++selling_Idx)
        {
            curr_profit = pStockPrices[selling_Idx] - pStockPrices[buying_Idx];
            auto remaining_profit = max_profit(pStockPrices, nDays, selling_Idx + 1, nTransaction - 1);
            curr_profit += remaining_profit;
            max_curr_profit_f = max(max_curr_profit_f, curr_profit);
        }
         
        max_curr_profit_s = max_profit(pStockPrices, nDays, buying_Idx + 1, nTransaction); 
        return max(max_curr_profit_f, max_curr_profit_s);
    }
}


/// <summary>
/// TC: nDays * nTransaction
/// SC: nDays * nTransaction + Stack Space
/// </summary>
namespace RecursiveDP
{
    int max_profit(vector<int>& pStockPrices, int nDays, int buying_Idx, int nTransaction, dp_type& pAux)
    {
        if ((buying_Idx >= nDays) || nTransaction == 0)
            return 0;

        if (pAux[buying_Idx][nTransaction] == -1)
        {
            int max_curr_profit_f = INT_MIN;  // If Transaction start from current day
            int max_curr_profit_s = INT_MIN;  // If Transaction doesn't start from current day

            for (int selling_Idx = buying_Idx + 1; selling_Idx < nDays; ++selling_Idx)
            {
                int curr_profit = pStockPrices[selling_Idx] - pStockPrices[buying_Idx];
                auto remaining_profit = max_profit(pStockPrices, nDays, selling_Idx + 1, nTransaction - 1, pAux);
                curr_profit += remaining_profit;
                max_curr_profit_f = max(max_curr_profit_f, curr_profit);
            }

            max_curr_profit_s = max_profit(pStockPrices, nDays, buying_Idx + 1, nTransaction, pAux);
            pAux[buying_Idx][nTransaction] = max(max_curr_profit_f, max_curr_profit_s);
        }

        return pAux[buying_Idx][nTransaction];
    }
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    while (nTestCase--)
    {
        int nTransaction = 0;
        cin >> nTransaction;

        int nDays = 0;
        cin >> nDays;
        vector<int> pStockPrices(nDays);
        for (int iCounter = 0; iCounter < nDays; ++iCounter)
            cin >> pStockPrices[iCounter];

        dp_type pAux(nDays, vector<int>(nTransaction + 1, -1));
        for (int iCounter = 0; iCounter < nDays; ++iCounter)
            pAux[iCounter][0] = 0;

        for (int iCounter = 0; iCounter <= nTransaction; ++iCounter)
            pAux[nDays - 1][iCounter] = 0;

        auto result = RecursiveDP::max_profit(pStockPrices, nDays, 0, nTransaction, pAux);
        cout << result << endl;
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
