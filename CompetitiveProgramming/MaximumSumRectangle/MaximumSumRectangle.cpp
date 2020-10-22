// MaximumSumRectangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct RetVal
{
    long long max_sum;
    pair<int, int> top_lft_coord;
    pair<int, int> bottom_rht_coord;
};

/*
TC:N^6
SC: 1
*/
namespace BruteForce
{
    RetVal GetMaxSumRectangle(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        long long max_sum = INT_MIN;
        pair<int, int> top_lft_coord;
        pair<int, int> bottom_rht_coord;

        auto calRectangleSum = [&pGrid](int tl_rIdx, int tl_cIdx, int br_rIdx, int br_cIdx)->long long {
            long long total_Sum = 0;
            for (int rIdx = tl_rIdx; rIdx <= br_rIdx; ++rIdx)
                for (int cIdx = tl_cIdx; cIdx <= br_cIdx; ++cIdx)
                    total_Sum += pGrid[rIdx][cIdx];

            return total_Sum;
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
                        auto curr_rect_sum = calRectangleSum(tl_rIdx, tl_cIdx, br_rIdx, br_cIdx);
                        if (curr_rect_sum > max_sum)
                        {
                            max_sum = curr_rect_sum;
                            top_lft_coord = make_pair(tl_rIdx, tl_cIdx);
                            bottom_rht_coord = make_pair(br_rIdx, br_cIdx);
                        }
                    }
                }
            }
        }

        return RetVal{ max_sum, top_lft_coord, bottom_rht_coord };
    }
}

/*
TC: N^4
SC: N^2
*/
namespace Prefix2DArrayPlusDP
{
    RetVal GetMaxSumRectangle(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        long long max_sum = INT_MIN;
        pair<int, int> top_lft_coord;
        pair<int, int> bottom_rht_coord;

        vector<vector<long long>> pAux(nRow, vector<long long>(nCol, 0)); 
        auto calSuffix2DArraySum = [&pGrid, &pAux, &nRow, &nCol]()->void {
            pAux[nRow - 1][nCol - 1] = pGrid[nRow - 1][nCol - 1];

            for (int cIdx = nCol - 2; cIdx >= 0; --cIdx)
                pAux[nRow - 1][cIdx] = pGrid[nRow - 1][cIdx] + pAux[nRow - 1][cIdx + 1];

            for (int rIdx = nRow - 2; rIdx >= 0; --rIdx)
                pAux[rIdx][nCol - 1] = pGrid[rIdx][nCol - 1] + pAux[rIdx + 1][nCol - 1];

            for(int rIdx = (nRow - 2); rIdx >= 0; --rIdx)
                for (int cIdx = (nCol - 2); cIdx >= 0; --cIdx) 
                    pAux[rIdx][cIdx] = (pGrid[rIdx][cIdx] + pAux[rIdx + 1][cIdx] + pAux[rIdx][cIdx + 1]) - pAux[rIdx + 1][cIdx + 1]; 
        };
        calSuffix2DArraySum();


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
                        long long curr_rect_sum = 0;
                        if (br_rIdx == (nRow - 1) && br_cIdx == (nCol - 1))
                            curr_rect_sum = pAux[tl_rIdx][tl_cIdx];
                        else if (br_rIdx == (nRow - 1))
                            curr_rect_sum = pAux[tl_rIdx][tl_cIdx] - pAux[tl_rIdx][br_cIdx + 1];
                        else if(br_cIdx == (nCol - 1))
                            curr_rect_sum = pAux[tl_rIdx][tl_cIdx] - pAux[br_rIdx + 1][tl_cIdx];
                        else
                            curr_rect_sum = (pAux[tl_rIdx][tl_cIdx] + pAux[br_rIdx + 1][br_cIdx + 1]) - (pAux[tl_rIdx][br_cIdx + 1] + pAux[br_rIdx + 1][tl_cIdx]);
                        
                        if (curr_rect_sum > max_sum)
                        {
                            max_sum = curr_rect_sum;
                            top_lft_coord = make_pair(tl_rIdx, tl_cIdx);
                            bottom_rht_coord = make_pair(br_rIdx, br_cIdx);
                        }
                    }
                }
            }
        }

        return RetVal{ max_sum, top_lft_coord, bottom_rht_coord };
    }
}

/*
TC: N^3
SC: N
*/
namespace TwoDKadanesAlgorithm
{
    RetVal GetMaxSumRectangle(vector<vector<int>>& pGrid, int nRow, int nCol)
    {
        long long max_sum = INT_MIN;
        pair<int, int> max_top_lft_coord;
        pair<int, int> max_bottom_rht_coord;
         
        auto kadaneAlgo = [](vector<long long> pAux, int& sIdx, int& eIdx)->long long {
            long long max_sum = pAux[0];
            sIdx = eIdx = 0; 
            int curr_start_Idx = 0;
            int curr_end_Idx   = 0;
            for (int rIdx = 1; rIdx < pAux.size(); ++rIdx)
            { 
                if ((pAux[rIdx] + pAux[rIdx - 1]) > pAux[rIdx])
                {
                    pAux[rIdx] = pAux[rIdx] + pAux[rIdx - 1];
                    curr_end_Idx = rIdx;
                }
                else
                {
                    curr_start_Idx = rIdx;
                    curr_end_Idx = rIdx;
                }

                if (pAux[rIdx] > max_sum)
                {
                    max_sum = pAux[rIdx];
                    sIdx = curr_start_Idx;
                    eIdx = curr_end_Idx;
                }
            }

            return max_sum;
        };

        for (int lb_cIdx = 0; lb_cIdx < nCol; ++lb_cIdx)
        {
            vector<long long> pAux(nRow, 0);
            for (int rb_cIdx = lb_cIdx; rb_cIdx < nCol; ++rb_cIdx)
            {
                // Compute Prefix row Sum for each row between left and right bound
                for (int rIdx = 0; rIdx < nRow; ++rIdx)
                    pAux[rIdx] += pGrid[rIdx][rb_cIdx];

                // Run 1D Kadane's Algorithm to find top and bottom bound
                // which can give max sum between left and right bound
                int tb_Idx;
                int bb_Idx;
                auto curr_max_rect_sum = kadaneAlgo(pAux, tb_Idx, bb_Idx);
                if (curr_max_rect_sum > max_sum)
                {
                    max_sum = curr_max_rect_sum;
                    max_top_lft_coord = make_pair(tb_Idx, lb_cIdx);
                    max_bottom_rht_coord = make_pair(bb_Idx, rb_cIdx);
                } 
            }
        }
         
        return RetVal{ max_sum, max_top_lft_coord, max_bottom_rht_coord };
    }
}

int main()
{
    int nRow = 0;
    int nCol = 0;
    cin >> nRow >> nCol;
    vector<vector<int>> pGrid(nRow, vector<int>(nCol));

    for (int rIdx = 0; rIdx < nRow; ++rIdx)
        for (int cIdx = 0; cIdx < nCol; ++cIdx)
            cin >> pGrid[rIdx][cIdx];

    auto return_value = TwoDKadanesAlgorithm::GetMaxSumRectangle(pGrid, nRow, nCol);
    cout << "MaximumSum     : " << return_value.max_sum << endl;
    cout << "Top Left Cell  : " << return_value.top_lft_coord.first << "," << return_value.top_lft_coord.second << endl;
    cout << "Bott Right Cell: " << return_value.bottom_rht_coord.first << "," << return_value.bottom_rht_coord.second << endl;
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
