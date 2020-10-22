// LongestCommonSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

bool IsNullCharacter(const char& oInput)
{
    return ('\0' == oInput);
}

/*
TC: Exponential
SC: max(m,n)Stack space 
*/
namespace BruteForce
{
    int lcs(const char* s1, const char* s2)
    {
        if (IsNullCharacter(s1[0]) || IsNullCharacter(s2[0]))
            return 0;

        if (s1[0] == s2[0])
            return 1 + lcs(s1 + 1, s2 + 1);
        else
        {
            auto Option_F = lcs(s1 + 1, s2);
            auto Option_S = lcs(s1, s2 + 1);
            return max(Option_F, Option_S);
        }
    }
}

/*
TC: mn
SC: mn + max(m,n)Stack space
*/
namespace UsingRecursiveDP
{
    int lcs(string& oInput_F
          , string& oInput_S
          , int curr_fIdx
          , int curr_sIdx
          , dp_type& pAux)
    {
        if (oInput_F.length() == curr_fIdx 
         || oInput_S.length() == curr_sIdx)
            return 0;

        if (pAux[curr_fIdx][curr_sIdx] == -1)
        {
            int possible_result = 0;
            if (oInput_F[curr_fIdx] == oInput_S[curr_sIdx])
                possible_result = 1 + lcs(oInput_F, oInput_S, curr_fIdx + 1, curr_sIdx + 1, pAux);
            else
            {
                auto Option_F = lcs(oInput_F, oInput_S, curr_fIdx, curr_sIdx + 1, pAux);
                auto Option_S = lcs(oInput_F, oInput_S, curr_fIdx + 1, curr_sIdx, pAux);
                possible_result = max(Option_F, Option_S);
            }

            pAux[curr_fIdx][curr_sIdx] = possible_result;
        }

        return pAux[curr_fIdx][curr_sIdx];
    }
}

/*
TC: mn
SC: mn
*/
namespace UsingIterativeDP
{
    int lcs(string& oInput_F, string& oInput_S)
    {
        if (oInput_F.length() == 0
            || oInput_S.length() == 0)
            return 0;

        dp_type pAux(oInput_F.length() + 1, vector<int>(oInput_S.length() + 1, 0));

        for (int f_Idx = oInput_F.length() - 1; f_Idx >= 0; --f_Idx)
        {
            for (int s_Idx = oInput_S.length() - 1; s_Idx >= 0; --s_Idx)
            {
                if (oInput_F[f_Idx] == oInput_S[s_Idx])
                    pAux[f_Idx][s_Idx] = 1 + pAux[f_Idx + 1][s_Idx + 1];
                else 
                    pAux[f_Idx][s_Idx] = max(pAux[f_Idx][s_Idx + 1], pAux[f_Idx + 1][s_Idx]);
            }
        }

        return pAux[0][0];
        return 0;
    }
}

int main()
{
    string s1{ "adebc" };
    string s2{ "dcadb" };
    dp_type pAux(s1.length(), vector<int>(s2.length(), -1));

    auto resultIDP = UsingIterativeDP::lcs(s1, s2);
    auto resultRDP = UsingRecursiveDP::lcs(s1, s2, 0, 0, pAux);
    auto resultBF = BruteForce::lcs(s1.data(), s2.data());
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
