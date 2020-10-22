// AlphCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
 
const long long M = 1e9 + 7;

long long num_codes(vector<int>& Input, int size, vector<long long>& Aux)
{
    if (size <= 1)
        return 1;

    long long output = 0;
    if (Aux[size] == -1)
    {
        if (Input[size - 1] > 0)
            output = num_codes(Input, size - 1, Aux);

        if ((Input[size - 2] == 2 && Input[size - 1] <= 6) || (Input[size - 2] == 1))
            output = (output + num_codes(Input, size - 2, Aux)) % M;

        Aux[size] = output;
    }

    return Aux[size];
}

long long num_codes_Iterative(vector<int>& Input, int size)
{
    vector<long long> pAux(size + 1, 0);
    pAux[0] = pAux[1] = 1;

    for (int length = 2; length <= size; ++length)
    {
        pAux[length] = 0;
        if (Input[length - 1] > 0)
            pAux[length] = pAux[length - 1];

        if ((Input[length - 2] == 2 && Input[length - 1] <= 6) || (Input[length - 2] == 1))
            pAux[length] = (pAux[length] + pAux[length - 2]) % M;
    }

    return pAux[size];
}

int main()
{
    while (true)
    {
        string pLine;
        cin >> pLine;

        if (pLine.length() == 1 && pLine[0] == '0')
            break;

        vector<int> pInput(pLine.length(), 0);
        int iCounter = 0;
        for (auto ch : pLine)
            pInput[iCounter++] = ch - '0';

        vector<long long> pAux(iCounter + 1, -1);
        pAux[0] = pAux[1] = 1;
        // cout << num_codes(pInput, iCounter, pAux) << endl;
        cout << num_codes_Iterative(pInput, iCounter) << endl;
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
