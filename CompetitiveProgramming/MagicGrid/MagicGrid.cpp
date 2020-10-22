// MagicGrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
TC: 2^N
SC: N
Considering N*N matrix
*/
namespace BruteForce
{
    long long GetMinHealth(vector<vector<int>>& pGrid, int curr_row_Idx, int curr_col_Idx, int dest_row_Idx, int dest_col_Idx)
    {
        if (curr_row_Idx == dest_row_Idx && curr_col_Idx == dest_col_Idx)
            return 1;

        if (curr_row_Idx > dest_row_Idx || curr_col_Idx > dest_col_Idx)
            return INT_MAX;

        long long rt_dir_health = GetMinHealth(pGrid, curr_row_Idx, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
        long long dw_dir_health = GetMinHealth(pGrid, curr_row_Idx + 1, curr_col_Idx, dest_row_Idx, dest_col_Idx);
        rt_dir_health = max(1ll, rt_dir_health - pGrid[curr_row_Idx][curr_col_Idx]);
        dw_dir_health = max(1ll, dw_dir_health - pGrid[curr_row_Idx][curr_col_Idx]);
        return min(rt_dir_health, dw_dir_health);
    }
}

/*
TC: N*N
SC: N*N + Stack Space(Recursive)
Considering N*N matrix
*/
namespace DynamicProgramming
{
    long long GetMinHealth(vector<vector<int>>& pGrid
        , vector<vector<long long>>& pAux
        , int curr_row_Idx
        , int curr_col_Idx
        , int dest_row_Idx
        , int dest_col_Idx)
    {
        if (curr_row_Idx == dest_row_Idx && curr_col_Idx == dest_col_Idx)
            return 1;

        if (curr_row_Idx > dest_row_Idx || curr_col_Idx > dest_col_Idx)
            return INT_MAX;

        if (pAux[curr_row_Idx][curr_col_Idx] == -1)
        {
            long long rt_dir_health = GetMinHealth(pGrid, pAux, curr_row_Idx, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
            long long dw_dir_health = GetMinHealth(pGrid, pAux, curr_row_Idx + 1, curr_col_Idx, dest_row_Idx, dest_col_Idx);
            rt_dir_health = max(1ll, rt_dir_health - pGrid[curr_row_Idx][curr_col_Idx]);
            dw_dir_health = max(1ll, dw_dir_health - pGrid[curr_row_Idx][curr_col_Idx]);
            pAux[curr_row_Idx][curr_col_Idx] = min(rt_dir_health, dw_dir_health);
        }

        return pAux[curr_row_Idx][curr_col_Idx];
    }
}

/*
TC: N*N
SC: N*N 
Considering N*N matrix
*/
namespace DynamicProgrammingSpaceOptimized
{
    long long GetMinHealth(vector<vector<int>>& pGrid, int curr_row_Idx, int curr_col_Idx, int dest_row_Idx, int dest_col_Idx)
    {
        vector<vector<long long>> pAux(dest_row_Idx + 1, vector<long long>(dest_col_Idx + 1));
        pAux[dest_row_Idx][dest_col_Idx] = 1;

        for (int rIdx = dest_row_Idx - 1; rIdx >= 0; --rIdx)
            pAux[rIdx][dest_col_Idx] = max(1ll, pAux[rIdx + 1][dest_col_Idx] - pGrid[rIdx][dest_col_Idx]);

        for (int cIdx = dest_col_Idx - 1; cIdx >= 0; --cIdx)
            pAux[dest_row_Idx][cIdx] = max(1ll, pAux[dest_row_Idx][cIdx + 1] - pGrid[dest_row_Idx][cIdx]);

        for(int rIdx = dest_row_Idx - 1; rIdx >= 0; --rIdx)
            for (int cIdx = dest_col_Idx - 1; cIdx >= 0; --cIdx)
            { 
               long long rt_dir_health = max(1ll, pAux[rIdx][cIdx + 1] - pGrid[rIdx][cIdx]);
               long long dw_dir_health = max(1ll, pAux[rIdx + 1][cIdx] - pGrid[rIdx][cIdx]);
               pAux[rIdx][cIdx] = min(rt_dir_health, dw_dir_health);
            } 

        return pAux[0][0];
    }
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    while (nTestCase--)
    {
        int nRow, nCol;
        cin >> nRow >> nCol;

        vector<vector<int>> pGrid(nRow, vector<int>(nCol));
        for (int iCounter = 0; iCounter < nRow; ++iCounter)
            for (int jCounter = 0; jCounter < nCol; ++jCounter)
                cin >> pGrid[iCounter][jCounter];

        // vector<vector<long long>> pAux(nRow, vector<long long>(nCol, -1));
        cout << DynamicProgrammingSpaceOptimized::GetMinHealth(pGrid, 0, 0, nRow - 1, nCol - 1) << endl;
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
