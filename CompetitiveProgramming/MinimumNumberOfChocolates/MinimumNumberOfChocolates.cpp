// MinimumNumberOfChocolates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMin(const int* arr, int n) {
    if (n <= 1)
        return n; // Either return 1 or 0

    int min_chocolates_req = 0;

    vector<int> pAux(n, 1);
    // Considering if Left student is smaller than current
    // then value of chocolates will one greater than left element
    for (int iCounter = 1; iCounter < n; ++iCounter)
    {
        if (arr[iCounter] > arr[iCounter - 1])
            pAux[iCounter] = pAux[iCounter - 1] + 1;
    }

    // Considering if right student is smaller than current
    // then value of chocolates will one greater than right element
    min_chocolates_req += pAux[n - 1];
    for (int iCounter = n - 2; iCounter >= 0; --iCounter)
    {
        if ((arr[iCounter] > arr[iCounter + 1])
            && (pAux[iCounter] <= pAux[iCounter + 1]))
            pAux[iCounter] = pAux[iCounter + 1] + 1;

        min_chocolates_req += pAux[iCounter];
    }

    return min_chocolates_req;
}

int main()
{
    vector<int> pInput = { 1, 4, 4, 6 };
    int oResult = getMin(pInput.data(), pInput.size());
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
