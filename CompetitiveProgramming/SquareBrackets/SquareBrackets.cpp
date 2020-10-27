// SquareBrackets.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using dp_type = vector<vector<int>>;

/*
TC: Exponential
SC: total_count(stackspace)
*/
namespace Bruteforce
{
    int getBalancedCount(int open_count
        , int close_count
        , int total_count
        , int curr_idx
        , vector<bool>& constraint)
    {

        if (open_count > total_count || close_count > total_count)
            return 0;

        if (open_count == total_count && close_count == total_count)
            return 1;

        if ((open_count == close_count) || constraint[curr_idx])
            return getBalancedCount(open_count + 1, close_count, total_count, curr_idx + 1, constraint);
        else if (open_count == total_count)
            return getBalancedCount(open_count, close_count + 1, total_count, curr_idx + 1, constraint);
        else
        {
            auto IfOpen = getBalancedCount(open_count + 1, close_count, total_count, curr_idx + 1, constraint);
            auto IfClose = getBalancedCount(open_count, close_count + 1, total_count, curr_idx + 1, constraint);
            return IfOpen + IfClose;
        }
    }
}

/*
TC: total_count*total_count
SC: total_count*total_count + total_count(stackspace)
*/
namespace RecursiveDP
{
    int getBalancedCount(int open_count
        , int close_count
        , int total_count
        , int curr_idx
        , vector<bool>& constraint
        , dp_type& pAux)
    {

        if (open_count > total_count || close_count > total_count)
            return 0;
         
        if (pAux[open_count][close_count] == -1)
        {
            if (open_count == total_count && close_count == total_count)
                pAux[open_count][close_count] = 1; 
            else if ((open_count == close_count) || constraint[curr_idx])
                pAux[open_count][close_count] = getBalancedCount(open_count + 1, close_count, total_count, curr_idx + 1, constraint, pAux);
            else if (open_count == total_count)
                pAux[open_count][close_count] = getBalancedCount(open_count, close_count + 1, total_count, curr_idx + 1, constraint, pAux);
            else
            {
                auto IfOpen = getBalancedCount(open_count + 1, close_count, total_count, curr_idx + 1, constraint, pAux);
                auto IfClose = getBalancedCount(open_count, close_count + 1, total_count, curr_idx + 1, constraint, pAux);
                pAux[open_count][close_count] = IfOpen + IfClose;
            }
        }

        return pAux[open_count][close_count];
    }
}

int main()
{
    int nTestCase = 0;
    cin >> nTestCase;

    while (nTestCase--)
    {
        int total_count = 0;
        int kconstraint = 0;
        cin >> total_count >> kconstraint;
        vector<bool> constraint(2 * total_count, false);
        constraint[0] = true;
        for (int iCounter = 0; iCounter < kconstraint; ++iCounter)
        {
            int constraint_idx = 0;
            cin >> constraint_idx;
            constraint[constraint_idx - 1] = true;
        }

        dp_type pAux(total_count + 1, vector<int>(total_count + 1, -1));
        auto result = RecursiveDP::getBalancedCount(0, 0, total_count, 0, constraint, pAux);
        cout << result << endl;
    }

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
