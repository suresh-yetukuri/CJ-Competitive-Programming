// Equalize.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

///
// https://codeforces.com/contest/1037/problem/c
///

int main()
{
    int nLength = 0;
    string input, target;
    cin >> nLength;
    cin >> input >> target;

    int min_cost = 0;
    int iCounter = 0;
    while(iCounter < nLength)
    {
        if (input[iCounter] != target[iCounter])
        {
            // Now either we can swap or flip
            if ((iCounter < (nLength - 1))
                && (input[iCounter] != input[iCounter + 1])
                && (input[iCounter + 1] != target[iCounter + 1]))
            {
                swap(input[iCounter], input[iCounter + 1]);
                iCounter += 2;
            }
            else
            {
                input[iCounter] = target[iCounter];
                ++iCounter;
            }
            ++min_cost;
        }
        else
            ++iCounter;
    }

    if (input == target)
        cout << min_cost << endl;

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
