// MinimumPathSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
TC: 3^N
SC: N
*/
namespace BruteForce
{
    int min_cost(vector<vector<int>>& pGrid
        , int curr_row_Idx
        , int curr_col_Idx
        , int dest_row_Idx
        , int dest_col_Idx)
    {
        if (curr_row_Idx == dest_row_Idx && curr_col_Idx == dest_col_Idx)
            return pGrid[curr_row_Idx][curr_col_Idx];

        if (curr_row_Idx > dest_row_Idx || curr_col_Idx > dest_col_Idx)
            return INT_MAX;

        auto rt_move_cost   = min_cost(pGrid, curr_row_Idx, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
        auto diag_move_cost = min_cost(pGrid, curr_row_Idx + 1, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
        auto dwn_move_cost  = min_cost(pGrid, curr_row_Idx + 1, curr_col_Idx, dest_row_Idx, dest_col_Idx);

        return pGrid[curr_row_Idx][curr_col_Idx] + min(rt_move_cost, min(diag_move_cost, dwn_move_cost));
    }
}

/*
TC: N*N
SC: N*N + Stack Space
*/
namespace DynamicProgramming
{
    int min_cost(vector<vector<int>>& pGrid
        , vector<vector<int>>& pAux
        , int curr_row_Idx
        , int curr_col_Idx
        , int dest_row_Idx
        , int dest_col_Idx)
    {
        if (curr_row_Idx == dest_row_Idx && curr_col_Idx == dest_col_Idx)
            return pGrid[curr_row_Idx][curr_col_Idx];

        if (curr_row_Idx > dest_row_Idx || curr_col_Idx > dest_col_Idx)
            return INT_MAX;

        if (pAux[curr_row_Idx][curr_col_Idx] == -1)
        {
            auto rt_move_cost = min_cost(pGrid, pAux, curr_row_Idx, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
            auto diag_move_cost = min_cost(pGrid, pAux, curr_row_Idx + 1, curr_col_Idx + 1, dest_row_Idx, dest_col_Idx);
            auto dwn_move_cost = min_cost(pGrid, pAux, curr_row_Idx + 1, curr_col_Idx, dest_row_Idx, dest_col_Idx);
            pAux[curr_row_Idx][curr_col_Idx] = pGrid[curr_row_Idx][curr_col_Idx] + min(rt_move_cost, min(diag_move_cost, dwn_move_cost));
        }

        return pAux[curr_row_Idx][curr_col_Idx];
    }
}

/*
TC: N*N
SC: N*N
*/
namespace DP_iterative
{
    int min_cost(vector<vector<int>>& pGrid
               , int curr_row_Idx
               , int curr_col_Idx
               , int dest_row_Idx
               , int dest_col_Idx)
    {
        vector<vector<int>> pAux(dest_row_Idx + 1, vector<int>(dest_col_Idx + 1, -1));
        pAux[dest_row_Idx][dest_col_Idx] = pGrid[dest_row_Idx][dest_col_Idx];

        for (int rowIdx = dest_row_Idx - 1; rowIdx >= 0; --rowIdx)
            pAux[rowIdx][dest_col_Idx] = pGrid[rowIdx][dest_col_Idx] + pAux[rowIdx + 1][dest_col_Idx];

        for(int colIdx = dest_col_Idx - 1; colIdx >= 0; --colIdx)
            pAux[dest_row_Idx][colIdx] = pGrid[dest_row_Idx][colIdx] + pAux[dest_row_Idx][colIdx + 1];

        for (int rowIdx = dest_row_Idx - 1; rowIdx >= 0; --rowIdx)
        {
            for (int colIdx = dest_col_Idx - 1; colIdx >= 0; --colIdx)
            {
                pAux[rowIdx][colIdx] 
                    = pGrid[rowIdx][colIdx]
                    + min(pAux[rowIdx][colIdx + 1], min(pAux[rowIdx + 1][colIdx], pAux[rowIdx + 1][colIdx + 1]));
            }
        }

        return pAux[0][0];
    }
}

int main()
{
    std::cout << "Hello World!\n";
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
