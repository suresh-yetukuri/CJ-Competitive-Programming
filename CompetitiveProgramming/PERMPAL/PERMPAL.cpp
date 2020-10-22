// PERMPAL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


void printPalindromicString(string& oInput)
{
    unordered_map<char, vector<int>> pIndexMap;
    for (int iCounter = 0; iCounter < oInput.length(); ++iCounter)
        pIndexMap[oInput[iCounter]].push_back(iCounter);

    int oddIndexCount = 0;
    char lastOddFreqChar = '\0';

    int pCounter = 0;
    int qCounter = oInput.length() - 1;
    vector<int> oPalindrome(oInput.length(), 0);

    for (auto& oPair : pIndexMap)
    {
        if (oPair.second.size() % 2 != 0) {
            lastOddFreqChar = oPair.first;
            ++oddIndexCount;
            if (oddIndexCount > 1)
            {
                cout << "-1" << endl;
                return;
            }
        }
        else 
        {
            for (int iCounter = 0; iCounter < oPair.second.size(); iCounter += 2)
            {
                oPalindrome[pCounter++] = oPair.second[iCounter];
                oPalindrome[qCounter--] = oPair.second[iCounter + 1];
            }
        }
    }

    if (lastOddFreqChar != '\0')
    {
        copy_n(pIndexMap[lastOddFreqChar].begin()
             , pIndexMap[lastOddFreqChar].size()
             , oPalindrome.begin() + pCounter);
    }

    for (auto& Idx : oPalindrome)
        cout << Idx + 1 << " ";

    cout << endl;
}


int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    while (nTestCase--)
    {
        string oInput;
        cin >> oInput;
        printPalindromicString(oInput);
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
