// Color Rectangular.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{
    int nRectCount = 0;
    cin >> nRectCount;

    unordered_map<int, int> rect_map;
    int max_x = 0;
    for (int iCounter = 0; iCounter < nRectCount; ++iCounter)
    {
        int width, height;
        cin >> width >> height;

        if (rect_map.find(width / 2) != rect_map.end())
        {
            rect_map[width / 2] = max(height, rect_map[width/2]);
        }
        else
            rect_map[width / 2] = height;

        max_x = max(max_x, width / 2);
    }

    int curr_x = max_x;
    int last_max_height = 0;
    int total_area = 0;
    while (curr_x > 0)
    {
        if (rect_map.find(curr_x) != rect_map.end() && rect_map[curr_x] > last_max_height)
        {
            total_area += rect_map[curr_x];
            last_max_height = max(rect_map[curr_x], last_max_height);
        }
        else
            total_area += last_max_height;

        --curr_x;
    }

    cout << (total_area << 1) << endl;

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
