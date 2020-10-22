// LightBulbs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


long long getMinCost(string oInput, int nBulbCount, int reverse_cost, int flip_cost)
{
    int nZeroCount = 0;
    int iCounter = 0;

    while (iCounter < nBulbCount)
    {
        if (oInput[iCounter] = '0' && ((iCounter - 1) < 0 || oInput[iCounter - 1] == '1'))
            ++nZeroCount;

        ++iCounter;
    }

    return nZeroCount;

    if (nZeroCount > 0)
        return ((nZeroCount)*min(reverse_cost, flip_cost)) + (long long)flip_cost;

    return 0;
}

int main()
{
    int nBulbCount = 0;
    int reverse_cost = 0;
    int flip_cost = 0;
    string oInput;
    cin >> nBulbCount >> reverse_cost >> flip_cost;
    cin >> oInput;

    cout << getMinCost(oInput, nBulbCount, reverse_cost, flip_cost) << endl;

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
