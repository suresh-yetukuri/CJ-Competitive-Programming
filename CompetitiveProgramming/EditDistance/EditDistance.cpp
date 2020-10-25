// EditDistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

/*
TC: Exponential
SC: max(m,n);
*/
namespace BruteForce
{
    int editDistance(string& oInput_F, string& oInput_S, int f_Idx, int s_Idx) {
        if (oInput_F.length() == f_Idx
            || oInput_S.length() == s_Idx)
            return (oInput_S.length() - s_Idx) + (oInput_F.length() - f_Idx);

        if (oInput_F[f_Idx] == oInput_S[s_Idx])
            return editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1);
        else
        {
            auto Option_F = 1 + editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1);
            auto Option_S = 1 + editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx);
            auto Option_T = 1 + editDistance(oInput_F, oInput_S, f_Idx, s_Idx + 1);

            return min(Option_F, min(Option_S, Option_T));
        }
    }
}

/*
TC: m*n
SC: m*n + stackspace(max(m,n));
*/
namespace RecursiveDP
{
    int editDistance(string& oInput_F, string& oInput_S, int f_Idx, int s_Idx, dp_type& pAux) {
        if (oInput_F.length() == f_Idx
            || oInput_S.length() == s_Idx)
            return (oInput_S.length() - s_Idx) + (oInput_F.length() - f_Idx);

        if (pAux[f_Idx][s_Idx] == -1)
        {
            if (oInput_F[f_Idx] == oInput_S[s_Idx])
                pAux[f_Idx][s_Idx] = editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1, pAux);
            else
            {
                auto Option_F = 1 + editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx + 1, pAux);
                auto Option_S = 1 + editDistance(oInput_F, oInput_S, f_Idx + 1, s_Idx, pAux);
                auto Option_T = 1 + editDistance(oInput_F, oInput_S, f_Idx, s_Idx + 1, pAux);

                pAux[f_Idx][s_Idx] = min(Option_F, min(Option_S, Option_T));
            }
        }

        return pAux[f_Idx][s_Idx];
    }
}

/*
TC: m*n
SC: m*n
*/
namespace IterativeDP
{
    int editDistance(string& oInput_F, string& oInput_S) {
        if (oInput_F.empty() || oInput_S.empty())
            return oInput_F.length() + oInput_S.length();

        dp_type pAux(oInput_F.length() + 1, vector<int>(oInput_S.length() + 1, 0));
        for (int iCounter = 0; iCounter <= oInput_S.length(); ++iCounter)
            pAux[oInput_F.length()][iCounter] = oInput_S.length() - iCounter;

        for (int iCounter = 0; iCounter <= oInput_F.length(); ++iCounter)
            pAux[iCounter][oInput_S.length()] = oInput_F.length() - iCounter;

        for(int f_Idx = oInput_F.length() - 1; f_Idx >= 0; --f_Idx)
            for (int s_Idx = oInput_S.length() - 1; s_Idx >= 0; --s_Idx)
            {
                if (oInput_F[f_Idx] == oInput_S[s_Idx])
                    pAux[f_Idx][s_Idx] = pAux[f_Idx + 1][s_Idx + 1];
                else
                {
                    auto Option_F = 1 + pAux[f_Idx + 1][s_Idx + 1];
                    auto Option_S = 1 + pAux[f_Idx + 1][s_Idx];
                    auto Option_T = 1 + pAux[f_Idx][s_Idx + 1];

                    pAux[f_Idx][s_Idx] = min(Option_F, min(Option_S, Option_T));
                }
            }

        return pAux[0][0];
    }
}

int main()
{
    string oFirst{ "abcd" };
    string oSecond{ "gadcb" };
    
    cout << IterativeDP::editDistance(oFirst, oSecond) << endl;
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
