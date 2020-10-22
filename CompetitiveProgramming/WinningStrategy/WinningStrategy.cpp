// WinningStrategy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int getCount(vector<int>& pInput, int nPlayers)
{
    vector<int> pFinal(nPlayers + 1, 0);
    int swap_count = 0;
    int jCounter = nPlayers;
    while (jCounter > 0)
    {
        if (pInput[jCounter] == pFinal[jCounter])
        {
            // player is at correct possibtion
            // no need to reorder
            --jCounter;
            continue;
        }

        if ((jCounter > 0) && pInput[jCounter] == pFinal[jCounter - 1])
        {
            swap(pFinal[jCounter], pFinal[jCounter - 1]);
            --jCounter;
            ++swap_count;
            continue;
        }

        if ((jCounter > 1) && pInput[jCounter] == pFinal[jCounter - 2])
        {
            swap(pFinal[jCounter - 2], pFinal[jCounter - 1]);
            swap(pFinal[jCounter - 1], pFinal[jCounter]);
            swap_count += 2;
            --jCounter;
            continue;
        }

        // If it reaches here
        // then reordering not possible
        return -1;
    }

    return swap_count;
}

int getCountSO(vector<int>& pInput, int nPlayers)
{
    int swap_count = 0;
    for (int iCounter = nPlayers; iCounter > 0; --iCounter)
    {
        if (iCounter != pInput[iCounter])
        {
            if (iCounter == pInput[iCounter - 1])
            {
                swap(pInput[iCounter], pInput[iCounter - 1]);
                ++swap_count;
            }
            else if (iCounter == pInput[iCounter - 2])
            {
                swap(pInput[iCounter - 2], pInput[iCounter - 1]);
                swap(pInput[iCounter - 1], pInput[iCounter]);
                swap_count += 2;
            }
            else
                return -1;

        }
    }

    return swap_count;
}

int main() {

    int nPlayers = 0;
    cin >> nPlayers;

    vector<int> pInput(nPlayers + 1, 0);
    bool IsOrderingPossible = true;
    for (int iCounter = 1; iCounter <= nPlayers; ++iCounter)
    {
        cin >> pInput[iCounter];
        if (abs(pInput[iCounter] - (iCounter + 1)) > 2)
            IsOrderingPossible = false;
    }

    if(IsOrderingPossible)
    {
        int swap_count = getCount(pInput, nPlayers);
        if (swap_count == -1)
            cout << "NO" << endl;
        else
        {
            cout << "YES" << endl;
            cout << swap_count << endl;
        }
    }
    else
        cout << "NO" << endl;

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
