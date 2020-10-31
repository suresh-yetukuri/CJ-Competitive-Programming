// WinningLottery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
TC: Exponential
SC: D
*/
namespace Bruteforce
{
	bool Utility(int Place, int D, int curr_sum, int target, vector<int>& oResult)
	{
		if (D < Place)
		{
			if (curr_sum == target)
				return true;
			else
				return false;
		}

		int iCounter = Place == 1 ? 1 : 0;
		for (; iCounter <= 9; ++iCounter)
		{
			if (Utility(Place + 1, D, curr_sum + iCounter, target, oResult))
			{
				oResult[Place] = iCounter;
				return true;
			}
		}

		return false;
	}
}

/*
TC: D
SC: 1
*/
namespace Greedy
{
	void Utility(int nDigits, int nSum, vector<int>& oResult)
	{
		int fill_Idx = nDigits; 
		while (fill_Idx > 0 && (nSum > 0))
		{
			if (nSum > 9)
			{
				oResult[fill_Idx] = 9;
				nSum -= 9;
			}
			else if (nSum <= 9)
			{
				if (fill_Idx > 1) {
					oResult[fill_Idx] = nSum - 1;
					oResult[1] = 1;
				}
				else {
					oResult[fill_Idx] = nSum;
					nSum = 0;
				}
				break;
			}

			--fill_Idx;
		}
	}
}

int main()
{
	int nSum = 0;
	int nDigits = 0;
	cin >> nSum >> nDigits;
	vector<int> oResult(nDigits + 1, 0);
	//auto result = Bruteforce::Utility(1, nDigits, 0, nSum, oResult);
	Greedy::Utility(nDigits, nSum, oResult); 

	for (int iCounter = 1; iCounter <= nDigits; ++iCounter)
		cout << oResult[iCounter];

	cout << endl; 
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
