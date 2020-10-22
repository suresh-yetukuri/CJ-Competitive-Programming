// Fibonacci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

/*
TC: 2^N
SC: N
*/
long long FibRecursive(long long n)
{
    if (n <= 1)
        return 1;

    return FibRecursive(n - 1) + FibRecursive(n - 2);
}

/*
TC: N
SC: N
Dynamic Programming
*/
long long FibRecursiveOptimized(long long  n, vector<long long>& pAux)
{
    if (n <= 1)
        return 1;

    if (pAux[n] == -1)
        pAux[n] = FibRecursiveOptimized(n - 1, pAux) + FibRecursiveOptimized(n - 2, pAux);

    return pAux[n];
}

/*
TC: N
SC: N
*/
long long FibIterative(long long n)
{
    vector<long long> pInput(n + 1, -1);
    pInput[0] = 1;
    pInput[1] = 1;

    for (int iCounter = 2; iCounter <= n; ++iCounter)
        pInput[iCounter] = pInput[iCounter - 1] + pInput[iCounter - 2];

    return pInput[n];
}

/*
TC: N
SC: 1
*/
long long FibIterativeOptimized(long long n)
{
    if (n <= 1)
        return 1;

    long long a = 1;
    long long b = 1;
    long long c = 0;
    while (n > 1)
    {
        c = a + b;
        a = b;
        b = c;
        --n;
    }

    return c;
}

int main()
{
    long long n = 50;
    cout << FibIterative(n) << endl;
    cout << FibIterativeOptimized(n) << endl;
    // cout << FibRecursive(n) << endl;
    vector<long long > pAux(n + 1, -1);
    cout << FibRecursiveOptimized(n, pAux) << endl;

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
