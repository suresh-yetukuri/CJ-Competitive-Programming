// StairCase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

const long long M = 1e9 + 7;

/*
TC: 3^n
SC: n
*/
long long CountWays_BF(int nSteps)
{
    if (1 >= nSteps)
        return 1ll;

    if (2 == nSteps)
        return 2ll;

    return CountWays_BF(nSteps - 1)
         + CountWays_BF(nSteps - 2) 
         + CountWays_BF(nSteps - 3);
}

/*
Dynamic programming
TC: n
SC: n
*/
long long CountWays_TOpt(int nSteps, vector<long long>& pAux)
{
    if (1 >= nSteps)
        return 1ll;

    if (2 == nSteps)
        return 2ll;

    if (pAux[nSteps] == 0)
    {
        pAux[nSteps] = CountWays_TOpt(nSteps - 1, pAux)
                     + CountWays_TOpt(nSteps - 2, pAux)
                     + CountWays_TOpt(nSteps - 3, pAux);
    }

    return pAux[nSteps];
}

long long CountWays_SOpt(int nSteps)
{
    long long a = 1;
    long long b = 1;
    long long c = 2;
    long long next_step_ways = 0;
    while (nSteps > 2)
    {
        next_step_ways = (a + b + c)% M;
        a = b;
        b = c;
        c = next_step_ways;
        --nSteps;
    }

    return c;
}

int main()
{
    int nSteps = 0;
    cin >> nSteps;
    vector<long long> pAux(nSteps + 1ll, 0);
    // cout << CountWays_TOpt(nSteps, pAux) << endl;
    cout << CountWays_SOpt(nSteps) << endl;
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
