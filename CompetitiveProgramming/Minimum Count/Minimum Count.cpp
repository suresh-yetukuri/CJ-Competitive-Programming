// Minimum Count.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

bool IsPerfectSquare(int n)
{
    return (sqrt(n) - floor(sqrt(n)) == 0);
}

namespace BruteForce
{
    int minCount(int n)
    {
        if (n <= 3)
            return n;

        if (IsPerfectSquare(n))
            return 1;

        int min_result = n;
        for (int iCounter = 1; iCounter < n; ++iCounter)
        {
            int curr_square = (iCounter * iCounter);
            if (curr_square > n)
                break;

            min_result = min(min_result, 1 + minCount(n - curr_square));
        }

        return min_result;
    }
}

namespace UsingDP
{ 
    int minCount(int target)
    {
        if (target <= 3)
            return target;

        if (IsPerfectSquare(target))
            return 1;

        vector<int> pAux(target + 1ll);
        for (int iCounter = 0; iCounter <= 3; ++iCounter)
            pAux[iCounter] = iCounter;
        
        for (int jCounter = 4; jCounter <= target; ++jCounter)
        {
            pAux[jCounter] = jCounter;
            for (int iCounter = 1; iCounter < jCounter; ++iCounter)
            {
                int curr_square = (iCounter * iCounter);
                if (curr_square > jCounter)
                    break;

                pAux[jCounter] = min(pAux[jCounter], 1 + pAux[jCounter - curr_square]);
            }
        }
         
        return pAux[target];
    }
}

int main()
{
    cout << UsingDP::minCount(4) << endl;
    cout << UsingDP::minCount(12) << endl;
    cout << UsingDP::minCount(60) << endl;

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
