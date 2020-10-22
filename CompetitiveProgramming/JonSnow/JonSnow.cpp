// JonSnow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int Ceil(int x)
{
    auto val = (x + 1) / 2.0;
    return static_cast<int>(val);
}
 

int main()
{  
    int nRanger = 0;
    int kOperation = 0;
    int x = 0;

    cin >> nRanger >> kOperation >> x;
    vector<int> pStrength(nRanger);
    for (int iCounter = 0; iCounter < nRanger; ++iCounter)
        cin >> pStrength[iCounter];
       
    vector<int> pAux(1024, 0);
    for (auto& val : pStrength)
        pAux[val]++;

    vector<int> pAuxTemp(1024, 0);
    int min_strength = INT_MAX;
    int max_strength = INT_MIN;
      
    while (kOperation--)
    { 
        int scannedRangers = 0;
        for (int iCounter = 0; iCounter < 1024; ++iCounter)
        {
            if (pAux[iCounter])
            {
                auto val = (iCounter ^ x);
                if ((pAux[iCounter] % 2) == 0)
                {
                    pAuxTemp[iCounter] += pAux[iCounter] / 2;
                    pAuxTemp[val] += pAux[iCounter] / 2;
                }
                else
                {
                    if ((scannedRangers % 2) == 0)
                    {
                        pAuxTemp[iCounter] += Ceil(pAux[iCounter]) - 1;
                        pAuxTemp[val] += Ceil(pAux[iCounter]);
                    }
                    else
                    {
                        pAuxTemp[iCounter] += Ceil(pAux[iCounter]);
                        pAuxTemp[val] += Ceil(pAux[iCounter]) - 1;
                    }
                } 
                scannedRangers += pAux[iCounter]; 
            }
        }

        swap(pAux, pAuxTemp);
        fill(pAuxTemp.begin(), pAuxTemp.end(), 0);
    }

    for (int iCounter = 0; iCounter < 1024; ++iCounter)
    {
        if (pAux[iCounter] > 0 && min_strength == INT_MAX) 
            min_strength = iCounter;  

        if (pAux[iCounter] > 0) 
            max_strength = iCounter;
    }
     
    cout << max_strength << " " << min_strength << endl;
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
