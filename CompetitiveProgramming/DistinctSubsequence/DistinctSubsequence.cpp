// DistinctSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
const long long M = static_cast<long long>(1e9 + 7);

/// TC: N
/// SC: N + N
/// https://www.youtube.com/watch?v=9UEHPiK53BA
/// @param oInput 
/// @return 
long long countDistinctSubseq(string& oInput)
{
    if (oInput.length() == 0)
        return 1;

    vector<long long> pAux(oInput.length() + 1);
    unordered_map<char, int> last_occ;
    pAux[0] = 1;
    for (int iCounter = 1; iCounter <= oInput.length(); ++iCounter)
    {
        pAux[iCounter] = (2 * pAux[iCounter - 1]) % M;
        if (last_occ.find(oInput[iCounter - 1]) != last_occ.end())
        {
            auto lst_occ_Idx = last_occ[oInput[iCounter - 1]];
            pAux[iCounter] = pAux[iCounter] - pAux[lst_occ_Idx - 1];
        }
        last_occ[oInput[iCounter - 1]] = iCounter;
    }

    return pAux[oInput.length()];
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;
    while (nTestCase--)
    {
        string oInput;
        cin >> oInput;
        auto result = countDistinctSubseq(oInput);
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
