// CrossWord.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int N = 10;


bool IsVerticallyValid(vector<vector<char>>& pCrossWord, string word, int row, int col)
{
    int Idx = 0;
    for (int curr_row = row; (curr_row < N) && (Idx < word.length()); ++curr_row)
    {
        char curr_char = pCrossWord[curr_row][col];
        if (curr_char == '-' || curr_char == word[Idx])
            ++Idx;
        else
            return false;
    }

    return (Idx == word.length());
}

bool IsHorizontallyValid(vector<vector<char>>& pCrossWord, string word, int row, int col)
{
    int Idx = 0;
    for (int curr_col = col; (curr_col < N) && (Idx < word.length()); ++curr_col)
    {
        char curr_char = pCrossWord[row][curr_col];
        if (curr_char == '-' || curr_char == word[Idx])
            ++Idx;
        else
            return false;
    }

    return (Idx == word.length());
}

void SetVertical(vector<vector<char>>& pCrossWord, string word, vector<bool>& pHelper, int row, int col)
{
    for (int iCounter = 0; iCounter < word.length(); ++iCounter)
    {
        char curr_char = word[iCounter];
        if (pCrossWord[row][col] == '-')
        {
            pCrossWord[row][col] = curr_char;
            pHelper[iCounter] = true;
        }

        ++row;
    }
}

void SetHorizontal(vector<vector<char>>& pCrossWord, string word, vector<bool>& pHelper, int row, int col)
{
    for (int iCounter = 0; iCounter < word.length(); ++iCounter)
    {
        char curr_char = word[iCounter];
        if (pCrossWord[row][col] == '-')
        {
            pCrossWord[row][col] = curr_char;
            pHelper[iCounter] = true;
        }

        ++col;
    }
}

void ResetVertical(vector<vector<char>>& pCrossWord, string word, vector<bool>& pHelper, int row, int col)
{
    for (int iCounter = 0; iCounter < word.length(); ++iCounter)
    {
        if (pHelper[iCounter])
            pCrossWord[row][col] = '-';

        ++row;
    }
}

void ResetHorizontal(vector<vector<char>>& pCrossWord, string word, vector<bool>& pHelper, int row, int col)
{
    for (int iCounter = 0; iCounter < word.length(); ++iCounter)
    {
        if (pHelper[iCounter]) 
            pCrossWord[row][col] = '-';

        ++col;
    }
}

bool solveCrossWord(vector<vector<char>>& pCrossWord, vector<string>& pWords, int Idx)
{
    if (Idx == pWords.size())
    {
        for (auto& pLine : pCrossWord)
        {
            for (auto& ch : pLine)
                cout << ch;

            cout << endl;
        }

        return true;
    }

    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if (pCrossWord[row][col] == '-' || pCrossWord[row][col] == pWords[Idx][0])
            {
                if (IsHorizontallyValid(pCrossWord, pWords[Idx], row, col))
                {
                    vector<bool> pHelper(pWords[Idx].length(), false);
                    SetHorizontal(pCrossWord, pWords[Idx], pHelper, row, col);

                    if (solveCrossWord(pCrossWord, pWords, Idx + 1))
                        return true;

                    ResetHorizontal(pCrossWord, pWords[Idx], pHelper, row, col);
                }

                if (IsVerticallyValid(pCrossWord, pWords[Idx], row, col))
                {
                    vector<bool> pHelper(pWords[Idx].length(), false);
                    SetVertical(pCrossWord, pWords[Idx], pHelper, row, col);

                    if (solveCrossWord(pCrossWord, pWords, Idx + 1))
                        return true;

                    ResetVertical(pCrossWord, pWords[Idx], pHelper, row, col);
                }
            }
        }
    }

    return false;
}


int main() {

    vector<vector<char>> pCrossWord(N, vector<char>(N));
    vector<string> 	     pWords;

    for (int iCounter = 0; iCounter < N; ++iCounter)
    {
        string pLine;
        cin >> pLine;
        int jCounter = 0;
        for (auto ch : pLine)
            pCrossWord[iCounter][jCounter++] = ch;
    }

    string pLine;
    cin >> pLine;

    char* token = strtok(const_cast<char*>(pLine.data()), ";");
    while (nullptr != token)
    {
        pWords.push_back(string{ token });
        token = strtok(NULL, ";");
    }

    bool eResult = solveCrossWord(pCrossWord, pWords, 0);

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
