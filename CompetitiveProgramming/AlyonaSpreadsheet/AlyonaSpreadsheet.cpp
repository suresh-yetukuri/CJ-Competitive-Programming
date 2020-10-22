// AlyonaSpreadsheet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int nRow, nCol;
    cin >> nRow >> nCol;

    vector<vector<int>> pGrid(nRow, vector<int>(nCol));
    for (int iCounter = 0; iCounter < nRow; ++iCounter)
        for (int jCounter = 0; jCounter < nCol; ++jCounter)
            cin >> pGrid[iCounter][jCounter];

    vector<vector<int>> pAux(nRow, vector<int>(nCol + 1, 1));

    for (int iCounter = 0; iCounter < nCol; ++iCounter)
    {
        for (int jCounter = 1; jCounter < nRow; ++jCounter)
        {
            if (pGrid[jCounter - 1][iCounter] <= pGrid[jCounter][iCounter])
                pAux[jCounter][iCounter] = pAux[jCounter - 1][iCounter];
            else
                pAux[jCounter][iCounter] = jCounter + 1;
        }
    }

    for (int iCounter = 0; iCounter < nRow; ++iCounter)
        pAux[iCounter][nCol] = *min_element(pAux[iCounter].begin(), pAux[iCounter].end() - 1);


    int testcases;
    cin >> testcases;
    while (testcases--)
    {
        int l, r;
        cin >> l >> r;
        if (pAux[r - 1][nCol] <= l)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
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
