// AdjacentBitCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using dp_type = vector<vector<vector<ll>>>;
const long long M = static_cast<ll>(1e9 + 7);

ll findCount(int nSizeBitString, int kAdjBitCount, int first_Bit, dp_type& pAux)
{
    if (1 == nSizeBitString)
    {
        if (kAdjBitCount == 0)
            return 1;

        return 0;
    }

    if (kAdjBitCount < 0)
        return 0;

    
    if (-1 == pAux[nSizeBitString][kAdjBitCount][first_Bit])
    {
        ll curr_Count = 0;
        if (first_Bit)
        {
            curr_Count = (findCount(nSizeBitString - 1, kAdjBitCount - 1, 1, pAux)
                + findCount(nSizeBitString - 1, kAdjBitCount, 0, pAux)) % M;
        }
        else
        {
            curr_Count = (findCount(nSizeBitString - 1, kAdjBitCount, 1, pAux)
                + findCount(nSizeBitString - 1, kAdjBitCount, 0, pAux)) % M;
        }

        pAux[nSizeBitString][kAdjBitCount][first_Bit] = curr_Count;
    }

    return pAux[nSizeBitString][kAdjBitCount][first_Bit];
}

void PreCalculate(int nSizeBitString, int kAdjBitCount, dp_type& pAux)
{
    pAux[nSizeBitString][kAdjBitCount][0] = findCount(nSizeBitString, kAdjBitCount, 0, pAux);
    pAux[nSizeBitString][kAdjBitCount][1] = findCount(nSizeBitString, kAdjBitCount, 1, pAux);
}

int main()
{ 
    const int max_size = 4;
    const int adjBitCount = 3;
    const int bit_possibility = 2;
    dp_type pAux(max_size + 1, vector<vector<ll>>(adjBitCount + 1, vector<ll>(bit_possibility, -1))); 
    PreCalculate(max_size, adjBitCount, pAux);

    int nDataSet = 0;
    cin >> nDataSet;

    while (nDataSet--)
    {
        int dataset_Idx = 0;
        int nSizeBitString = 0;
        int kAdjBitCount = 0;
        cin >> dataset_Idx >> nSizeBitString >> kAdjBitCount;
        auto result = (pAux[nSizeBitString][kAdjBitCount][0] + pAux[nSizeBitString][kAdjBitCount][1]) % M;
        cout << dataset_Idx << " " << result << endl;
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
