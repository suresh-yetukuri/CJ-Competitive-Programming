// RoyAndCoinBoxes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
//#define BruteForce
#define Optimized

#ifdef BruteForce
/*
TC: M + N + N + NLogN + QLogN
SC: N
*/
int main()
{
    long long nCoinBox = 0;
    long long nDay = 0;
    cin >> nCoinBox;
    cin >> nDay;
     
    vector<long long> pCoinBox(nCoinBox + 2, 0);

    for (int iCounter = 0; iCounter < nDay; ++iCounter)
    {
        long long lft_limit = 0;
        long long rght_limit = 0;
        cin >> lft_limit >> rght_limit;

        pCoinBox[lft_limit] += 1;
        pCoinBox[rght_limit + 1] -= 1;
    }

    // Calculate Prefix Sum, Will Give Final State of Boxes After M days
    for (int iCounter = 2; iCounter <= nCoinBox; ++iCounter)
        pCoinBox[iCounter] = pCoinBox[iCounter] + pCoinBox[iCounter - 1];

    // Actual Search Space
    auto search_begin_Itr = pCoinBox.begin() + 1;
    auto search_end_Itr = pCoinBox.end() - 1;

    sort(pCoinBox.begin() + 1, pCoinBox.end() - 1);

    long long nQuery = 0;
    cin >> nQuery;
    while (nQuery--)
    {
        long long nBox = 0;
        long long query = 0;
        cin >> query;
         
        auto lb_itr = upper_bound(search_begin_Itr, search_end_Itr, query - 1);
        if (lb_itr != search_end_Itr) 
            nBox = search_end_Itr - lb_itr; 

        cout << nBox << endl;
    }


    return 0;
}

#endif

#ifdef Optimized 
/*
TC: M + N + N + Q
SC: N
*/
int main()
{
    // For larger inputs, TLE can be avoided with below two lines
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long nCoinBox = 0;
    long long nDay = 0;
    cin >> nCoinBox;
    cin >> nDay;

    const long long max_possible_coins = nDay;
    vector<long long> pCoinBox(nCoinBox + 2, 0);
    vector<long long> pAux(max_possible_coins + 1, 0);

    for (int iCounter = 0; iCounter < nDay; ++iCounter)
    {
        long long lft_limit = 0;
        long long rght_limit = 0;
        cin >> lft_limit >> rght_limit;

        pCoinBox[lft_limit] += 1;
        pCoinBox[rght_limit + 1] -= 1;
    }

    // Calculate Prefix Sum, Will Give Final State of Boxes After M days
    // As well as compute aux array, defining the answer
    pAux[pCoinBox[1]] += 1;
    for (int iCounter = 2; iCounter <= nCoinBox; ++iCounter)
    {
        pCoinBox[iCounter] = pCoinBox[iCounter] + pCoinBox[iCounter - 1];
        pAux[pCoinBox[iCounter]] += 1;
    }

    // Calculate Suffix Sum for Aux array, will give us the answer
    for (int iCounter = max_possible_coins - 1; iCounter >= 0; --iCounter)
        pAux[iCounter] = pAux[iCounter] + pAux[iCounter + 1];
     
    long long nQuery = 0;
    cin >> nQuery;
    while (nQuery--)
    { 
        long long query = 0;
        cin >> query;
        if (query <= max_possible_coins)
            cout << pAux[query] << endl;
        else
            cout << 0 << endl;
    }
     
    return 0;
}

#endif // Optimized

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
