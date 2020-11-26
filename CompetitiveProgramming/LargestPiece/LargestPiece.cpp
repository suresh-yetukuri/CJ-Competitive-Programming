// LargestPiece.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define NMAX 55


int DFS(char cake[NMAX][NMAX]
    , int n
    , vector<vector<bool>>& pVisited
    , int rCounter
    , int cCounter)
{
    if (rCounter < 0 || cCounter < 0 || rCounter >= n || cCounter >= n)
        return 0;

    if ((cake[rCounter][cCounter] == '0') || pVisited[rCounter][cCounter])
        return 0;

    pVisited[rCounter][cCounter] = true; 
    auto option1 = DFS(cake, n, pVisited, rCounter - 1, cCounter);
    auto option2 = DFS(cake, n, pVisited, rCounter, cCounter - 1);
    auto option3 = DFS(cake, n, pVisited, rCounter, cCounter + 1);
    auto option4 = DFS(cake, n, pVisited, rCounter + 1, cCounter);
    return option1 + option2 + option3 + option4 + 1;
}

int solve(int n, char cake[NMAX][NMAX])
{
    int max_cake_size = 0;
    for(int iCounter = 0; iCounter < n; ++iCounter)
        for (int jCounter = 0; jCounter < n; ++jCounter)
        {
            if (cake[iCounter][jCounter] == '1')
            {
                vector<vector<bool>> pVisited(n, vector<bool>(n, false));
                auto curr_cake_size = DFS(cake, n, pVisited, iCounter, jCounter);
                max_cake_size = max(curr_cake_size, max_cake_size);
            }
        }
    
    return max_cake_size;
}

int main()
{
    int n = 0;
    cin >> n;
    char cake[NMAX][NMAX];
    for (int iCounter = 0; iCounter < n; ++iCounter)
        for (int jCounter = 0; jCounter < n; ++jCounter)
            cin >> cake[iCounter][jCounter];

    auto result = solve(n, cake);
    cout << result << endl;
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
