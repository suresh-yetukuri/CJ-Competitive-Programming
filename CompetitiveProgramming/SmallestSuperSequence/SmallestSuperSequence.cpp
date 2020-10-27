// SmallestSuperSequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;


/*
TC: Exponenetial
SC: max(flength, slength)
*/
namespace Bruteforce
{
    int smallestSuperSequence(const char* oInput_f
        , const char* oInput_s
        , int f_idx
        , int s_idx
        , int flength
        , int slength) 
    {
        if (f_idx == flength || s_idx == slength)
            return (flength - f_idx) + (slength - s_idx);

        if (oInput_f[f_idx] == oInput_s[s_idx])
            return 1 + smallestSuperSequence(oInput_f, oInput_s, f_idx + 1, s_idx + 1, flength, slength);
        else
        {
            auto option_f = smallestSuperSequence(oInput_f, oInput_s, f_idx, s_idx + 1, flength, slength);
            auto option_s = smallestSuperSequence(oInput_f, oInput_s, f_idx + 1, s_idx, flength, slength);
            return 1 + min(option_f, option_s);
        }
    }
}


/*
TC: flength*slength
SC: flength*slength + stackspace(max(flength, slength))
*/
namespace RecursiveDP
{
    int smallestSuperSequence(const char* oInput_f
        , const char* oInput_s
        , int f_idx
        , int s_idx
        , int flength
        , int slength
        , dp_type& pAux)
    {
        if (f_idx == flength || s_idx == slength)
            return (flength - f_idx) + (slength - s_idx);

        if (pAux[f_idx][s_idx] == INT_MAX)
        {
            if (oInput_f[f_idx] == oInput_s[s_idx])
                pAux[f_idx][s_idx] = 1 + smallestSuperSequence(oInput_f, oInput_s, f_idx + 1, s_idx + 1, flength, slength, pAux);
            else
            {
                auto option_f = smallestSuperSequence(oInput_f, oInput_s, f_idx, s_idx + 1, flength, slength, pAux);
                auto option_s = smallestSuperSequence(oInput_f, oInput_s, f_idx + 1, s_idx, flength, slength, pAux);
                pAux[f_idx][s_idx] = 1 + min(option_f, option_s);
            }
        }

        return pAux[f_idx][s_idx];
    }
}


/*
TC: flength*slength
SC: flength*slength
*/
namespace IterativeDP
{
    int smallestSuperSequence(const char* oInput_f
        , const char* oInput_s
        , int flength
        , int slength)
    {
        if (0 == flength || 0 == slength)
            return flength + slength;

        dp_type pAux(flength + 1, vector<int>(slength + 1, 0));
        for (int sIdx = 0; sIdx <= slength; ++sIdx)
            pAux[flength][sIdx] = (slength - sIdx);

        for (int fIdx = 0; fIdx <= flength; ++fIdx)
            pAux[fIdx][slength] = (flength - fIdx);

        for(int fIdx = flength - 1; fIdx >= 0; --fIdx)
            for (int sIdx = slength - 1; sIdx >= 0; --sIdx)
            {
                if (oInput_f[fIdx] == oInput_s[sIdx])
                    pAux[fIdx][sIdx] = 1 + pAux[fIdx + 1][sIdx + 1];
                else
                {
                    auto option_f = pAux[fIdx][sIdx + 1];
                    auto option_s = pAux[fIdx + 1][sIdx];
                    pAux[fIdx][sIdx] = 1 + min(option_f, option_s);
                }
            } 

        return pAux[0][0];
    }
}


/*
TC: flength*slength
SC: flength
*/
namespace IterativeDPSapceOptimized
{
    int smallestSuperSequence(const char* oInput_f
        , const char* oInput_s
        , int flength
        , int slength)
    {
        if (0 == flength || 0 == slength)
            return flength + slength;

        vector<int> pLastAux(slength + 1, 0);
        vector<int> pCurrentAux(slength + 1, 0);

        for (int sIdx = 0; sIdx <= slength; ++sIdx)
            pLastAux[sIdx] = (slength - sIdx);
         
        
        for (int fIdx = flength - 1; fIdx >= 0; --fIdx)
        {
            pCurrentAux[slength] = (flength - fIdx);
            for (int sIdx = slength - 1; sIdx >= 0; --sIdx)
            {
                if (oInput_f[fIdx] == oInput_s[sIdx])
                    pCurrentAux[sIdx] = 1 + pLastAux[sIdx + 1];
                else
                {
                    auto option_f = pCurrentAux[sIdx + 1];
                    auto option_s = pLastAux[sIdx];
                    pCurrentAux[sIdx] = 1 + min(option_f, option_s);
                }
            }

            swap(pCurrentAux, pLastAux);
        }

        return pLastAux[0];
    }
}


int main()
{
    string oInput_f;
    string oInput_s;
    cin >> oInput_f >> oInput_s;
     
    dp_type pAux(oInput_f.length(), vector<int>(oInput_s.length(), INT_MAX));
    auto result = IterativeDPSapceOptimized::smallestSuperSequence(oInput_f.data(), oInput_s.data(), oInput_f.length(), oInput_s.length());
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
