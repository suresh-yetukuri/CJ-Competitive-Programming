#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


long long find_turn(vector<long long>& pWindow, int window_count, int curr_idx)
{
    long long low = 0;
    long long high = 1e9;
    long long turn = 0;
    while (low <= high)
    {
        long long mid = low + ((high - low) >> 1);
        long long total_time = curr_idx + (mid * window_count);
        if (total_time >= pWindow[curr_idx])
        {
            turn = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    return turn;
}

int main()
{
    int window_count = 0;
    cin >> window_count;

    vector<long long> pWindow(window_count);
    for (int iCounter = 0; iCounter < window_count; ++iCounter)
        cin >> pWindow[iCounter];

    for (int iCounter = 0; iCounter < window_count; ++iCounter)
    {
        long long curr_queue = pWindow[iCounter];
        long long turn = find_turn(pWindow, window_count, iCounter);
        pWindow[iCounter] = iCounter + (turn * window_count);
    }

    auto min_idx = min_element(pWindow.begin(), pWindow.end()) - pWindow.begin();
    cout << (min_idx + 1) << endl;
    return 0;
}
