// CoinChange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int coin_change(int nRupees, int* pDenomination, int nDenom)
{
    if (nDenom == 0 || nRupees < 0)
        return 0;

    if (nRupees == 0)
        return 1;

    return coin_change(nRupees - pDenomination[0], pDenomination, nDenom)
        +  coin_change(nRupees, pDenomination + 1, nDenom - 1);
}


int coin_change_dp(int nRupees, int* pDenomination, int nDenom, vector<vector<int>>& pAux)
{
    if (nDenom == 0 || nRupees < 0)
        return 0;

    if (nRupees == 0)
        return 1;

    if (pAux[nRupees][nDenom] == -1)
    {
        pAux[nRupees][nDenom] = coin_change_dp(nRupees - pDenomination[0], pDenomination, nDenom, pAux)
                              + coin_change_dp(nRupees, pDenomination + 1, nDenom - 1, pAux);
    }

    return pAux[nRupees][nDenom];
}


int main()
{
    int nDenom = 3;
    int pDenom[] = { 1, 2, 3 };
    int nRupees = 4;
    vector<vector<int>> pAux(nRupees + 1, vector<int>(nDenom + 1, -1));
    cout << coin_change_dp(nRupees, pDenom, nDenom, pAux) << endl;
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
