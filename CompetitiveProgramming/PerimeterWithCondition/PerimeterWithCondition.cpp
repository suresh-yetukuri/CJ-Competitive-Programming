// PerimeterWithCondition.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

bool IsTrianglePossible(ll a, ll b, ll c)
{
    return ((a + b) > c)
        && ((b + c) > a)
        && ((c + a) > b);
}

ll Perimeter(ll a, ll b, ll c)
{
    return a + b + c;
}

struct MaxTrianglePerimeter
{
    int a;
    int b;
    int c;
};

/*
BruteForce
TC: N^3
SC: 1
*/
namespace BruteForce
{
    void Utility(vector<ll>& pInput, int nSize)
    {
        long long max_perimeter = -1;
        MaxTrianglePerimeter oResult{ 0,0,0 };
        for (int iCounter = 0; iCounter < (nSize - 2); ++iCounter)
        {
            for (int jCounter = iCounter + 1; jCounter < (nSize - 1); ++jCounter)
            {
                for (int kCounter = jCounter + 1; kCounter < nSize; ++kCounter)
                {
                    if (IsTrianglePossible(pInput[iCounter], pInput[jCounter], pInput[kCounter]))
                    {
                        auto curr_perimeter = Perimeter(pInput[iCounter], pInput[jCounter], pInput[kCounter]);
                        if (max_perimeter < curr_perimeter)
                        {
                            oResult.a = pInput[iCounter];
                            oResult.b = pInput[jCounter];
                            oResult.c = pInput[kCounter];
                            max_perimeter = curr_perimeter;
                        }
                    }
                }
            }
        }

        if (max_perimeter == -1)
            cout << max_perimeter << endl;
        else
            cout << oResult.a << " " << oResult.b << " " << oResult.c << endl;
    }
}

/*
TC: NLogN + N^2LogN
*/
namespace BinarySearch
{
    int GetJustLesser(vector<ll>& pInput, int low, int high, ll target)
    {
        int ans = -1;
        while (low <= high)
        {
            int mid = low + ((high - low) >> 1);
            if (target > pInput[mid])
            {
                ans = mid;
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return -1;
    }

    void Utility(vector<ll>& pInput, int nSize)
    {
        long long max_perimeter = -1;
        MaxTrianglePerimeter oResult{ 0,0,0 };
        sort(pInput.begin(), pInput.end());
        for (int iCounter = 0; iCounter < (nSize - 2); ++iCounter)
        {
            for (int jCounter = iCounter + 1; jCounter < (nSize - 1); ++jCounter)
            {
                auto Idx = GetJustLesser(pInput, jCounter + 1, nSize - 1, pInput[iCounter] + pInput[jCounter]);
                if (Idx != -1)
                {
                    auto curr_perimeter = Perimeter(pInput[iCounter], pInput[jCounter], pInput[Idx]);
                    if (max_perimeter < curr_perimeter)
                    {
                        oResult.a = pInput[iCounter];
                        oResult.b = pInput[jCounter];
                        oResult.c = pInput[Idx];
                        max_perimeter = curr_perimeter;
                    }
                }
            }
        }

        if (max_perimeter == -1)
            cout << max_perimeter << endl;
        else
            cout << oResult.a << " " << oResult.b << " " << oResult.c << endl;
    }
}

/*
TC: N
SC: 1
*/
namespace OptimizedGreedy
{
    void Utility(vector<ll>& pInput, int nSize)
    {
        long long max_perimeter = -1;
        MaxTrianglePerimeter oResult{ 0,0,0 };
        sort(pInput.begin(), pInput.end(), greater<ll>());
        int iCounter = 0;
        while (iCounter < (nSize - 2))
        {
            if (pInput[iCounter] < (pInput[iCounter + 1] + pInput[iCounter + 2])) {
                max_perimeter = pInput[iCounter] + pInput[iCounter + 1] + pInput[iCounter + 2];
                oResult.c = iCounter;
                oResult.b = iCounter + 1;
                oResult.a = iCounter + 2;
                break;
            }
        }

        if (max_perimeter == -1)
            cout << max_perimeter << endl;
        else
            cout << oResult.a << " " << oResult.b << " " << oResult.c << endl;
    }
}

int main()
{
    int nSize = 0;
    cin >> nSize;
    vector<long long> pInput(nSize);
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cin >> pInput[iCounter];
    
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
