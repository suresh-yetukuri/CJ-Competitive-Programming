// ShortestUncommonSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

/*
TC: Exponential
SC: s length
*/
namespace Bruteforce
{
    int shortestUncommonSubseq(string& oInput_f, string& oInput_s, int f_Idx, int s_Idx)
    {
        if (oInput_f.length() == f_Idx && oInput_s.length() != s_Idx)
            return 1001;

        if (oInput_s.length() <= s_Idx)
            return 1;

        auto f_Itr = find(oInput_s.begin() + s_Idx, oInput_s.end(), oInput_f[f_Idx]);
        if (f_Itr == oInput_s.end())
            return 1;

        auto charIdx = f_Itr - oInput_s.begin();
        auto option_f = shortestUncommonSubseq(oInput_f, oInput_s, f_Idx + 1, s_Idx);
        auto option_s = 1 + shortestUncommonSubseq(oInput_f, oInput_s, f_Idx + 1, charIdx + 1);
        return min(option_f, option_s);
    }
}


/*
TC: f*s
SC: f*s + stakspace
*/
namespace RecursiveDP
{
    int shortestUncommonSubseq(string& oInput_f, string& oInput_s, int f_Idx, int s_Idx, dp_type& pAux)
    {
        if (oInput_f.length() == f_Idx && oInput_s.length() != s_Idx)
            return 1001;

        if (oInput_s.length() <= s_Idx)
            return 1;

        if (pAux[f_Idx][s_Idx] == 1003)
        {
            auto f_Itr = find(oInput_s.begin() + s_Idx, oInput_s.end(), oInput_f[f_Idx]);
            if (f_Itr == oInput_s.end())
                pAux[f_Idx][s_Idx] = 1;
            else
            {
                auto charIdx = f_Itr - oInput_s.begin();
                auto option_f = shortestUncommonSubseq(oInput_f, oInput_s, f_Idx + 1, s_Idx, pAux);
                auto option_s = 1 + shortestUncommonSubseq(oInput_f, oInput_s, f_Idx + 1, charIdx + 1, pAux);
                pAux[f_Idx][s_Idx] = min(option_f, option_s);
            }
        }

        return pAux[f_Idx][s_Idx];
    }
}

// Go through Iterative approach later
// https://www.geeksforgeeks.org/shortest-uncommon-subsequence/
int main()
{
    string oInput_f;
    string oInput_s;
    cin >> oInput_f >> oInput_s;
    dp_type pAux(oInput_f.length(), vector<int>(oInput_s.length(), 1003));// 1003 marker for not computed 
    auto result = RecursiveDP::shortestUncommonSubseq(oInput_f, oInput_s, 0, 0, pAux);
    cout << result << endl;
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
