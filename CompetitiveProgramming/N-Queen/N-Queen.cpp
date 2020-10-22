// N-Queen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

bool checkLinearCollision(int nCross, int p_row, int p_col, vector<pair<int, int>>& oTracker)
{
    for (auto oPlace : oTracker)
    {
        if (oPlace.first == p_row
            || oPlace.second == p_col)
            return false;
    }
    return true;
}

bool checkDiagonalCollision(int nCross, int p_row, int p_col, vector<pair<int, int>>& oTracker)
{
    for (auto oPlace : oTracker)
    {
        // Location (Left->Right) towards bottom
        for (int rCounter = oPlace.first + 1,
            cCounter = oPlace.second + 1;
            rCounter < nCross && cCounter < nCross;
            ++rCounter, ++cCounter)
        {
            if (rCounter == p_row && cCounter == p_col)
                return false;
        }

        // Location (Left->Right) towards top
        for (int rCounter = oPlace.first - 1,
            cCounter = oPlace.second - 1;
            rCounter >= 0 && cCounter >= 0;
            --rCounter, --cCounter)
        {
            if (rCounter == p_row && cCounter == p_col)
                return false;
        }

        // Location (Right->Left) towards bottom
        for (int rCounter = oPlace.first + 1,
            cCounter = oPlace.second - 1;
            rCounter < nCross && cCounter >= 0;
            ++rCounter, --cCounter)
        {
            if (rCounter == p_row && cCounter == p_col)
                return false;
        }

        // Location (Right->Left) towards bottom
        for (int rCounter = oPlace.first - 1,
             cCounter = oPlace.second + 1;
            cCounter < nCross && rCounter >= 0;
            ++cCounter, --rCounter)
        {
            if (rCounter == p_row && cCounter == p_col)
                return false;
        }
    }


    return true;
}

bool IsValidToPlace(int nCross, int p_row, int p_col, vector<pair<int, int>>& oTracker)
{
    return (checkLinearCollision(nCross, p_row, p_col, oTracker)
        && checkDiagonalCollision(nCross, p_row, p_col, oTracker));
}

void Utility(int nCross, int target_row_Idx, vector<pair<int, int>>& oTracker)
{
    if (target_row_Idx >= nCross)
    {
        // print tracker
        //if (oTracker.size() == nCross)
        {
            for (int iCounter = 0; iCounter < nCross; ++iCounter)
            {
                for (int jCounter = 0; jCounter < nCross; ++jCounter)
                {
                    if (oTracker[iCounter].second == jCounter)
                        cout << 1 << " ";
                    else
                        cout << 0 << " ";
                }
            }
            cout << endl;
        }

        return;
    }

    for (int jCounter = 0; jCounter < nCross; ++jCounter)
    {
        if (IsValidToPlace(nCross, target_row_Idx, jCounter, oTracker))
        {
            oTracker.push_back(make_pair(target_row_Idx, jCounter));
            Utility(nCross, target_row_Idx + 1, oTracker);
            oTracker.pop_back();
        }
    }
}

int main()
{
    int nCross;
    cin >> nCross; 

    vector<pair<int, int>> oTracker;
    Utility(nCross, 0, oTracker);
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
