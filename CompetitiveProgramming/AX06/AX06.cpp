#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const size_t N = 9;

pair<int, int> findEmptyPosition(vector<vector<int>>& pGrid, int i, int j)
{
    for (int iCounter = i; iCounter < N; ++iCounter)
        for (int jCounter = 0; jCounter < N; ++jCounter)
            if (pGrid[iCounter][jCounter] == 0)
                return make_pair(iCounter, jCounter);

    return make_pair(-1, -1);
}

pair<int, int> findBoundary(int oInput)
{
    auto boundary = make_pair(0, 0);

    if (oInput >= 0 && oInput <= 2) {
        boundary.first = 0;
        boundary.second = 2;
    }
    else if (oInput >= 3 && oInput <= 5)
    {
        boundary.first = 3;
        boundary.second = 5;
    }
    else if (oInput >= 6 && oInput <= 8)
    {
        boundary.first = 6;
        boundary.second = 8;
    }

    return boundary;
}

bool checkLinear(vector<vector<int>>& pGrid, pair<int, int> empty_pos, int target_num)
{
    int curr_row = empty_pos.first;
    int curr_col = empty_pos.second;

    // check vertically + horizontally
    for (int iCounter = 0; iCounter < N; ++iCounter)
        if ((pGrid[iCounter][curr_col] == target_num) || (pGrid[curr_row][iCounter] == target_num))
            return false;

    return true;
}

bool checkBox(vector<vector<int>>& pGrid, pair<int, int> empty_pos, int target_num)
{
    int curr_row = empty_pos.first;
    int curr_col = empty_pos.second;

    // We need to boundary coordinates 
    // of box in which our current empty position exist
    auto row_boundary = findBoundary(curr_row);
    auto col_boundary = findBoundary(curr_col);

    int row_start = row_boundary.first;
    int row_end = row_boundary.second;
    int col_start = col_boundary.first;
    int col_end = col_boundary.second;

    for (int iCounter = row_start; iCounter <= row_end; ++iCounter)
        for (int jCounter = col_start; jCounter <= col_end; ++jCounter)
            if (pGrid[iCounter][jCounter] == target_num)
                return false;

    return true;
}

bool IsValidToFill(vector<vector<int>>& pGrid, pair<int, int> empty_pos, int target_num)
{
    return checkLinear(pGrid, empty_pos, target_num)
        && checkBox(pGrid, empty_pos, target_num);
}

bool solveSudoko(vector<vector<int>>& pGrid, int i, int j)
{
    auto curr_empty_pos = findEmptyPosition(pGrid, i, j);
    if (curr_empty_pos.first == -1)
        return true;

    for (int iCounter = 1; iCounter <= 9; ++iCounter)
    {
        if (IsValidToFill(pGrid, curr_empty_pos, iCounter))
        {
            pGrid[curr_empty_pos.first][curr_empty_pos.second] = iCounter;
            if (solveSudoko(pGrid, curr_empty_pos.first, curr_empty_pos.second))
                return true;
            else
                pGrid[curr_empty_pos.first][curr_empty_pos.second] = 0;
        }
    }

    return false;
}

int main()
{
    vector<vector<int>> pGrid(N, vector<int>(N, 0));
    for (int iCounter = 0; iCounter < N; ++iCounter)
    {
        string oRowInput;
        cin >> oRowInput;
        for (int jCounter = 0; jCounter < oRowInput.length(); ++jCounter)
            pGrid[iCounter][jCounter] = oRowInput[jCounter] - '0';
    }

    if (solveSudoko(pGrid, 0, 0))
    {
        for (int iCounter = 0; iCounter < N; ++iCounter) {
            for (int jCounter = 0; jCounter < N; ++jCounter)
                cout << pGrid[iCounter][jCounter];

            cout << endl;
        }
    }

    return 0;
}
