// AngryChildren.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
TC: NLogN + N
SC: 1
*/
int main()
{
    int N = 0;
    int K = 0;
    cin >> N >> K;
    vector<long long> pInput(N);
    for (int iCounter = 0; iCounter < N; ++iCounter)
        cin >> pInput[iCounter];

    sort(pInput.begin(), pInput.end());

    // Unfairness till first two elements
    long long unfairness = pInput[1] - pInput[0];
    long long Sum = pInput[0] + pInput[1];

    for (int iCounter = 2; iCounter < K; ++iCounter)
    {
        unfairness = unfairness + ((iCounter * pInput[iCounter]) - Sum);
        Sum += pInput[iCounter];
    }

    // Till this point we have got unfairness for first K Consecutive elements
    long long min_unfairness = unfairness;

    // Now Slowly find unfairness for each k window
    for (int iCounter = K; iCounter < N; ++iCounter)
    {
        // First remove unfairness contribution from (iCounter - K) element i.e first element
        unfairness = unfairness - (Sum - (K * pInput[iCounter - K]));
        Sum -= pInput[iCounter - K];

        // Now add new element to last of window
        unfairness = unfairness + ((K - 1) * pInput[iCounter] - Sum);
        Sum += pInput[iCounter];

        min_unfairness = min(min_unfairness, unfairness);
    }

    cout << min_unfairness << endl;

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
