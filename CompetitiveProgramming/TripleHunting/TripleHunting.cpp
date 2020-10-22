// TripleHunting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	/*string oInputFile = "listin.txt";
	string oOutputFile = "listout.txt";

	freopen(oInputFile.data(), "r", stdin);
	freopen(oOutputFile.data(), "w", stdout);*/

	int nCount = 0;
	cin >> nCount;

	vector<int> oResult;
	for (int iCounter = 1; iCounter <= nCount; ++iCounter)
	{
		int oInput;
		cin >> oInput;
		if (0 == (oInput % 3))
			oResult.push_back(iCounter);
	}

	if (0 == oResult.size())
		cout << "Nothing here!" << endl;
	else
	{
		cout << oResult.size() << endl;
		for (auto& Idx : oResult)
			cout << Idx << " ";

		cout << endl;
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
