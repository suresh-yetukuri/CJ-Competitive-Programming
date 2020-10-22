// Subsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void GenerateSubsequence(string oInput)
{
    long long nSize = oInput.length();
    long long nTotal_Subsequenced = 1ll << nSize;
    for (long long iCounter = 0; iCounter < nTotal_Subsequenced; ++iCounter)
    {
        string curr_subsequence;
        for (long long jCounter = 0; jCounter < nSize; ++jCounter)
        {
            if ((iCounter & (1ll << jCounter)))
                curr_subsequence.push_back(oInput[jCounter]);
        }
        
        if (curr_subsequence.empty())
            curr_subsequence.push_back('\0');

        cout << curr_subsequence << endl;
    }
}

vector<string> GenerateSubsequenceRecursive(string oInput)
{
    vector<string> oSubsequence;
    if (oInput.empty())
    {
        oSubsequence.push_back("");
        return move(oSubsequence);
    }

    string oSubInput = oInput.substr(1);
    oSubsequence = GenerateSubsequenceRecursive(oSubInput);
    long long curr_subseq_size = oSubsequence.size();

    for (long long int iCounter = 0; iCounter < curr_subseq_size; ++iCounter)
        oSubsequence.push_back(oInput[0] + oSubsequence[iCounter]);

    return move(oSubsequence);
}

void PrintSubsequence(string oInput, string oOutput)
{
    if (oInput.empty())
    {
        cout << oOutput << endl;
        return;
    }

    PrintSubsequence(oInput.substr(1), oOutput);
    PrintSubsequence(oInput.substr(1), oOutput + oInput[0]);
}


int main()
{
    string oInput;
    cin >> oInput;
    PrintSubsequence(oInput, string{});
    /*auto oResult = GenerateSubsequenceRecursive(oInput);
    for(auto& cInput : oResult)
        cout << cInput << endl;*/

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
