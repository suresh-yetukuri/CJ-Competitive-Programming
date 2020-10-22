// MaxSquareSubMatrixZero.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



struct RetVal
{
    int max_size;
    pair<int, int> top_lft_coord;
    pair<int, int> bottom_rht_coord;
};

/*
TC:N^6
SC: 1
*/
namespace BruteForce
{
    RetVal GetMaxSubMatrixSize(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        int max_submatrix_size = 0;
        pair<int, int> top_lft_coord;
        pair<int, int> bottom_rht_coord;
          
        auto IsSquareMatrix = [](int tl_rIdx, int tl_cIdx, int br_rIdx, int br_cIdx)->bool {
            return (abs(tl_rIdx - br_rIdx) == abs(tl_cIdx - br_cIdx));
        };

        auto IsMatrixZero = [&pGrid](int tl_rIdx, int tl_cIdx, int br_rIdx, int br_cIdx)->bool { 
            for (int rIdx = tl_rIdx; rIdx <= br_rIdx; ++rIdx)
                for (int cIdx = tl_cIdx; cIdx <= br_cIdx; ++cIdx)
                {
                    if (pGrid[rIdx][cIdx] != 0)
                        return false;
                } 
            return true;
        };

        for (int tl_rIdx = 0; tl_rIdx < nRow; ++tl_rIdx)
        {
            for (int tl_cIdx = 0; tl_cIdx < nCol; ++tl_cIdx)
            {
                for (int br_rIdx = tl_rIdx; br_rIdx < nRow; ++br_rIdx)
                {
                    for (int br_cIdx = tl_cIdx; br_cIdx < nCol; ++br_cIdx)
                    {
                        // Now we have rectangle top_left and bottorm right cells
                        // Compute Sum
                        if (IsSquareMatrix(tl_rIdx, tl_cIdx, br_rIdx, br_cIdx)
                            && IsMatrixZero(tl_rIdx, tl_cIdx, br_rIdx, br_cIdx))
                        {
                            int curr_matrix_size = abs(tl_rIdx - br_rIdx) + 1;
                            if (curr_matrix_size > max_submatrix_size)
                            {
                                max_submatrix_size = curr_matrix_size;
                                top_lft_coord = make_pair(tl_rIdx, tl_cIdx);
                                bottom_rht_coord = make_pair(br_rIdx, br_cIdx);
                            } 
                        }
                    }
                }
            }
        }

        return RetVal{ max_submatrix_size, top_lft_coord, bottom_rht_coord }; 
    }
}

/*
TC: N^4
SC: N^2
*/
namespace Prefix2DArrayPlusDP
{
    RetVal GetMaxSubMatrixSize(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        int max_submatrix_size = 0;
        pair<int, int> top_lft_coord;
        pair<int, int> bottom_rht_coord;

        auto IsSquareMatrix = [](int tl_rIdx, int tl_cIdx, int br_rIdx, int br_cIdx)->bool {
            return (abs(tl_rIdx - br_rIdx) == abs(tl_cIdx - br_cIdx));
        };

        vector<vector<int>> pAux(nRow, vector<int>(nCol, 0));
        pAux[nRow - 1][nCol - 1] = pGrid[nRow - 1][nCol - 1];

        for (int rIdx = (nRow - 2); rIdx >= 0; --rIdx)
            pAux[rIdx][nCol - 1] = pGrid[rIdx][nCol - 1] + pAux[rIdx + 1][nCol - 1];

        for (int cIdx = (nCol - 2); cIdx >= 0; --cIdx)
            pAux[nRow - 1][cIdx] = pGrid[nRow - 1][cIdx] + pAux[nRow - 1][cIdx + 1];

        for(int rIdx = (nRow - 2); rIdx >= 0; --rIdx)
            for (int cIdx = (nCol - 2); cIdx >= 0; --cIdx) 
                pAux[rIdx][cIdx] = (pGrid[rIdx][cIdx] + pAux[rIdx][cIdx + 1] + pAux[rIdx + 1][cIdx]) - pAux[rIdx + 1][cIdx + 1]; 
          
        for (int tl_rIdx = 0; tl_rIdx < nRow; ++tl_rIdx)
        {
            for (int tl_cIdx = 0; tl_cIdx < nCol; ++tl_cIdx)
            {
                for (int br_rIdx = tl_rIdx; br_rIdx < nRow; ++br_rIdx)
                {
                    for (int br_cIdx = tl_cIdx; br_cIdx < nCol; ++br_cIdx)
                    { 
                        if (IsSquareMatrix(tl_rIdx, tl_cIdx, br_rIdx, br_cIdx))
                        {
                            int curr_matrix_sum = 0;
                            if (br_rIdx == (nRow - 1) && br_cIdx == (nCol - 1))
                                curr_matrix_sum = pAux[tl_rIdx][tl_cIdx];
                            else if (br_rIdx == (nRow - 1))
                                curr_matrix_sum = pAux[tl_rIdx][tl_cIdx] - pAux[tl_rIdx][br_cIdx + 1];
                            else if (br_cIdx == (nCol - 1))
                                curr_matrix_sum = pAux[tl_rIdx][tl_cIdx] - pAux[br_rIdx + 1][tl_cIdx];
                            else 
                                curr_matrix_sum = (pAux[tl_rIdx][tl_cIdx] + pAux[br_rIdx + 1][br_cIdx + 1])
                                    - (pAux[tl_rIdx][br_cIdx + 1] + pAux[br_rIdx + 1][tl_cIdx]); 

                            if (curr_matrix_sum == 0)
                            {
                                int curr_matrix_size = abs(tl_rIdx - br_rIdx) + 1;
                                if (curr_matrix_size > max_submatrix_size)
                                {
                                    max_submatrix_size = curr_matrix_size;
                                    top_lft_coord = make_pair(tl_rIdx, tl_cIdx);
                                    bottom_rht_coord = make_pair(br_rIdx, br_cIdx);
                                }
                            }
                        } 
                    }
                }
            }
        }
         
        return RetVal{ max_submatrix_size, top_lft_coord, bottom_rht_coord };
    }
}

/*
TC: N^2
SC: N^2
*/
namespace DP
{
    int GetMaxSubMatrixSize(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        int max_submatrix_size = 0; 

        vector<vector<int>> pAux(nRow, vector<int>(nCol, 0));
        pAux[0][0] = pGrid[0][0] == 0 ? 1 : 0;

        for(int cIdx = 1; cIdx < nCol; ++cIdx)
            pAux[0][cIdx] = pGrid[0][cIdx] == 0 ? 1 : 0;

        for(int rIdx = 1; rIdx < nRow; ++rIdx)
            pAux[rIdx][0] = pGrid[rIdx][0] == 0 ? 1 : 0;

        for (int rIdx = 1; rIdx < nRow; ++rIdx)
            for (int cIdx = 1; cIdx < nCol; ++cIdx)
            {
                pAux[rIdx][cIdx] = min(pAux[rIdx - 1][cIdx - 1], min(pAux[rIdx - 1][cIdx], pAux[rIdx][cIdx - 1])) + 1;
                if (max_submatrix_size < pAux[rIdx][cIdx])
                    max_submatrix_size = pAux[rIdx][cIdx];
            }

        return max_submatrix_size;
    }
}

int main()
{
    std::cout << "Hello World!\n";



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
