// COCI Lopov.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    long long nJewelery = 0;
    long long nBags = 0;
    cin >> nJewelery >> nBags;
    vector<pair<int, int>> pJeweleries(nJewelery);
    for (int iCounter = 0; iCounter < nJewelery; ++iCounter)
        cin >> pJeweleries[iCounter].second >> pJeweleries[iCounter].first;

    multiset<long long> pBags;
    for (int iCounter = 0; iCounter < nBags; ++iCounter)
    {
        long long max_weight_allowed = 0;
        cin >> max_weight_allowed;
        pBags.insert(max_weight_allowed);
    }

    sort(pJeweleries.begin(), pJeweleries.end(), greater<pair<long long, long long>>());
    
    long long max_jewelery_value = 0;
    for (auto& jewelery : pJeweleries)
    {
        // Find appropriate bag to carry this jewelery
        auto itr = pBags.lower_bound(jewelery.second);
        if (itr != pBags.end())
        {
            max_jewelery_value += jewelery.first;
            pBags.erase(itr);
        }
    }

    cout << max_jewelery_value << endl;
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
